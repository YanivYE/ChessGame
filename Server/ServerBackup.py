import socket
import threading
import time

# This variable will keep track of the number of connected clients
num_connected_clients = 0

# Create a dictionary to store the sockets for each player
player_sockets = {}


def handle_client(client_soc, client_address, color):
    global num_connected_clients

    while True:
        # Receive a message from the client
        try:
            message_bytes = client_soc.recv(1024)
            message = message_bytes.decode("ascii")
            print("Received message from {} ({}): {}".format(client_address, color, message))

            # Send the message to the opposite player
            opposite_color = "Black" if color == "White" else "White"
            opposite_player_socket = player_sockets[opposite_color]
            opposite_player_socket.send(message.encode("ascii"))

            print("Send message to {} ({}): {}".format(opposite_player_socket.getsockname(), opposite_color, message))
        except (ConnectionResetError, ConnectionAbortedError):
            print("Lost connection to {} ({})".format(client_address, color))
            num_connected_clients -= 1
            break


def create_listening_sock():
    """
    Function creates a listening socket and returns it.
    :return: a listening socket
    """
    # Create a TCP/IP socket
    listening_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    # Bind the socket to the server's address and port
    server_address = ('127.0.0.1', 8200)
    listening_sock.bind(server_address)

    # Listen for incoming connections
    listening_sock.listen(5)

    return listening_sock


def main():
    print("Status: Waiting For Connections...")
    global num_connected_clients

    listening_sock = create_listening_sock()

    # Accept incoming connections and start a new thread for each client
    while True:
        client_soc, client_address = listening_sock.accept()

        num_connected_clients += 1

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

            t = threading.Thread(target=handle_client, args=(client_soc, client_address, color))
            t.start()
        else:
            print("Cannot accept more than 2 connections at once. Disconnecting {}".format(client_address))
            client_soc.close()
            num_connected_clients -= 1


if __name__ == '__main__':
    main()
