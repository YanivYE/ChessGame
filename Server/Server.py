import socket

# Create a new socket
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Bind the socket to the specified IP address and port
server_socket.bind(("127.0.0.1", 8200))

# Start listening for incoming connections
server_socket.listen()

# Accept an incoming connection
client_socket, client_addr = server_socket.accept()

while True:
    # Receive a message from the C# client
    message_bytes = client_socket.recv(1024)
    message = message_bytes.decode("ascii")

    message = message.split(',')

    if message[1] == "0":
        color = "White"
    else:
        color = "Black"

    print("Received message from C# engine: " + message[0] + " from engine color: " + color)

# Close the client socket when finished
client_socket.close()
