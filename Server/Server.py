import socket
import threading
import time

# This variable will keep track of the number of connected clients
num_connected_clients = 0

# Create a dictionary to store the sockets for each player
player_sockets = {}

# Set the IP address to listen on
IP = "192.168.1.178"
print("Server listening on IP address: " + IP)


def handle_client(client_soc, client_address, color):
    global num_connected_clients

    # Define the opposite color before the try block
    opposite_color = "Black" if color == "White" else "White"

    while True:
        try:
            # Receive a message from the client
            message_bytes = client_soc.recv(1024)
            message = message_bytes.decode("ascii")

            if not message:
                # If the message is empty, assume that the client has disconnected
                print("Lost connection to {} ({})".format(client_address, color))
                num_connected_clients -= 1
                del player_sockets[color]
                if opposite_color in player_sockets:
                    opposite_player_socket = player_sockets[opposite_color]
                    send_message(opposite_player_socket, "quit", opposite_color)
                    print("One Player has disconnected. Exiting the game")
                    opposite_player_socket.close()
                break

            print("Received message from {} ({}): {}".format(client_address, color, message))

            # Send the message to the opposite player if it is connected
            if opposite_color in player_sockets:
                opposite_player_socket = player_sockets[opposite_color]
                send_message(opposite_player_socket, message, opposite_color)
        except (ConnectionResetError, ConnectionAbortedError):
            print("Lost connection to {} ({})".format(client_address, color))
            num_connected_clients -= 1
            del player_sockets[color]
            if opposite_color in player_sockets:
                opposite_player_socket = player_sockets[opposite_color]
                send_message(opposite_player_socket, "quit", opposite_color)
                print("One Player has disconnected. Exiting the game")
                opposite_player_socket.close()
            break


def create_listening_sock():
    """
    Function creates a listening socket and returns it.
    :return: a listening socket
    """
    # Create a TCP/IP socket
    listening_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    # Bind the socket to the server's address and port
    server_address = (IP, 8200)
    listening_sock.bind(server_address)

    # Listen for incoming connections
    listening_sock.listen(5)

    return listening_sock


def send_message(sock, msg, color):
    sock.send(msg.encode("ascii"))
    print("Sent message to {} ({}): {}".format(sock.getsockname(), color, msg))


def main():
    print("Status: Waiting For Connections...")
    global num_connected_clients

    listening_sock = create_listening_sock()

    # Accept incoming connections and start a new thread for each client
    while True:
        if listening_sock.fileno() != -1:
            client_soc, client_address = listening_sock.accept()
        else:
            break

        num_connected_clients += 1

        if num_connected_clients == 2:
            # If the number of connected clients has reached 2, stop accepting new connections
            listening_sock.close()

        if num_connected_clients <= 2:
            if num_connected_clients == 1:
                color = "Black"
            elif num_connected_clients == 2:
                color = "White"
            else:
                color = ""
            # Start a new thread to handle the client
            client_thread = threading.Thread(target=handle_client, args=(client_soc, client_address, color))
            client_thread.start()

            # Save the client socket in the dictionary
            player_sockets[color] = client_soc

            print("Connected to {}, with the color: {}".format(client_address, color))

            send_message(client_soc, str(num_connected_clients), color)

            if num_connected_clients == 2:
                print("2 Players Connected. Starting Game.")
                break
        else:
            # If there are already two clients connected, send a message to the new client telling it to try again later
            send_message(client_soc, "Server is full. Please try again later.", "")
            client_soc.close()
            num_connected_clients -= 1

    time.sleep(3)

    for color, sock in player_sockets.items():
        send_message(sock, color, color)


if __name__ == '__main__':
    main()
