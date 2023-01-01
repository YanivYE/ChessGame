import socket
import threading
import time

# num of connected clients
num_connected_clients = 0

# sockets for each player
player_sockets = {}

# port to listen on
PORT = 3389

# IP address to listen on
hostname = socket.gethostname()
IP = socket.gethostbyname(hostname)


def handle_client(client_soc, client_address, color):
    """
    Function gets a client socket, address, color and handles it's messages
    :param client_soc: the client socket
    :param client_address: the client adress
    :param color: the client color
    :return: none
    """
    global num_connected_clients

    # get opposite color
    opposite_color = "Black" if color == "White" else "White"

    while True:
        try:
            # Receive a message from the client
            message_bytes = client_soc.recv(1024)
            message = message_bytes.decode("ascii")

            if not message:
                # if the message is empty, so client disconnected
                print("Lost connection to {} ({})".format(client_address, color))
                num_connected_clients -= 1

                del player_sockets[color]

                # check if we had opposite player, if so disconnect him
                if opposite_color in player_sockets:
                    opposite_player_socket = player_sockets[opposite_color]
                    send_message(opposite_player_socket, "quit", opposite_color)
                    print("One Player has disconnected. Exiting the game")
                    opposite_player_socket.close()
                break

            print("Received message from {} ({}): {}".format(client_address, color, message))

            # send the message to the opposite player if it is connected
            if opposite_color in player_sockets:
                opposite_player_socket = player_sockets[opposite_color]
                send_message(opposite_player_socket, message, opposite_color)
        except (ConnectionResetError, ConnectionAbortedError, BrokenPipeError, OSError):
            print("Lost connection to {} ({})".format(client_address, color))
            num_connected_clients -= 1

            # disconnect opposite player in error
            try:
                if opposite_color in player_sockets:
                    opposite_player_socket = player_sockets[opposite_color]
                    send_message(opposite_player_socket, "quit", opposite_color)
                    print("One Player has disconnected. Exiting the game")
                    opposite_player_socket.close()
            except OSError:
                print("Couldn't send message. Player hasn't moved to game form")
            break


def create_listening_sock():
    """
    Function creates a listening socket and returns it.
    :return: a listening socket
    """
    # Create a TCP/IP socket
    listening_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    # Bind the socket to the server's address and port
    server_address = (IP, PORT)
    listening_sock.bind(server_address)

    # Listen for incoming connections
    listening_sock.listen(5)

    return listening_sock


def send_message(sock, msg, color):
    """
    Function gets a socket, a message to send, a color, sends the message to the socket, and prints the sent message
    and what color player was it sent to.
    :param sock: the socket to send to
    :param msg: the message to send
    :param color: the socket player color
    :return: none
    """
    sock.send(msg.encode("ascii"))
    print("Sent message to {} ({}): {}".format(sock.getsockname(), color, msg))


def main():
    global num_connected_clients

    # print ip
    print("Server listening on IP address: " + IP)
    print("Status: Waiting For Connections...")

    # get new listening socket
    listening_sock = create_listening_sock()

    while True:
        # set new client properties to listening socket accepted client
        if listening_sock.fileno() != -1:
            client_soc, client_address = listening_sock.accept()
        else:
            break

        # add new client
        num_connected_clients += 1

        if num_connected_clients == 2:
            # If the number of connected clients is 2, stop accepting new connections
            listening_sock.close()

        if num_connected_clients <= 2:
            # assign client color
            if num_connected_clients == 1:
                color = "White"
            elif num_connected_clients == 2:
                color = "Black"
            else:
                color = ""

            # add a new thread to handle the new client
            client_thread = threading.Thread(target=handle_client, args=(client_soc, client_address, color))
            client_thread.start()

            # add the client socket in the dictionary
            player_sockets[color] = client_soc

            print("Connected to {}, with the color: {}".format(client_address, color))

            # send client num of connected clients
            send_message(client_soc, str(num_connected_clients), color)

            # if there are 2 clients, start game
            if num_connected_clients == 2:
                print("2 Players Connected. Starting game.")
                break
        else:
            # If there are already two clients connected, send a message to the new client telling it to try again later
            send_message(client_soc, "Server is full. Please try again later.", "")
            client_soc.close()
            num_connected_clients -= 1

    # add 1 sec delay
    time.sleep(1)

    try:
        for color, sock in player_sockets.items():
            # try to send colors
            send_message(sock, color, color)
    except OSError:
        print("Couldn't Send Colors. One or more player disconnected.")


if __name__ == '__main__':
    main()
