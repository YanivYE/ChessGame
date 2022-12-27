import socket
import threading
import time

# This variable will keep track of the number of connected clients
num_connected_clients = 0

# Create a dictionary to store the sockets for each player
player_sockets = {}

hostname = socket.gethostname()
IP = socket.gethostbyname(hostname)
IP = "172.20.10.4"
print("Your Local Computer IP Address Is: " + IP)


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
                    opposite_player_socket.send("quit".encode("ascii"))
                    print("One Player has disconnected. Exiting the game")
                    opposite_player_socket.close()
                break

            print("Received message from {} ({}): {}".format(client_address, color, message))

            # Send the message to the opposite player if it is connected
            if opposite_color in player_sockets:
                opposite_player_socket = player_sockets[opposite_color]
                opposite_player_socket.send(message.encode("ascii"))
                print("Sent message to {} ({}): {}".format(opposite_player_socket.getsockname(), color, message))
        except (ConnectionResetError, ConnectionAbortedError):
            print("Lost connection to {} ({})".format(client_address, color))
            num_connected_clients -= 1
            del player_sockets[color]
            if opposite_color in player_sockets:
                opposite_player_socket = player_sockets[opposite_color]
                opposite_player_socket.send("quit".encode("ascii"))
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


def receive_message(client_socket):
    try:
        data = client_socket.recv(1024)
        print('Received message: ', data)
    except (ConnectionResetError, ConnectionAbortedError):
        print(end="")


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
                color = "Invalid"

            # Store the socket for this player in the dictionary
            player_sockets[color] = client_soc

            print("Connected to {}, with the color: {}".format(client_address, color))

            client_soc.send(str(num_connected_clients).encode("ascii"))
            print("Sent message to {} ({}): {}".format(client_soc.getsockname(), color, str(num_connected_clients)))

            t = threading.Thread(target=handle_client, args=(client_soc, client_address, color))
            t.start()
        else:
            print("Cannot accept more than 2 connections at once. Disconnecting {}".format(client_address))
            client_soc.close()
            num_connected_clients -= 1

    for sock in player_sockets.values():
        receive_thread = threading.Thread(target=receive_message, args=(sock,))
        receive_thread.start()

    while True:
        if num_connected_clients == 2:

            print("Sent message to {} ({}): {}".format(player_sockets["Black"].getsockname(), "Black", str(num_connected_clients)))

        time.sleep(1)


if __name__ == '__main__':
    main()
