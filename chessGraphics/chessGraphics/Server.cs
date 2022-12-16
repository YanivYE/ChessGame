using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Net;
using System.Text;

namespace chessGraphics
{
    internal class Server
    {
        // Create a new socket
        Socket socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);

        // Connect to the Python server at the specified IP address and port
        IPAddress serverAddr = IPAddress.Parse("127.0.0.1");

        Server()
        {
            IPEndPoint endPoint = new IPEndPoint(serverAddr, 8080);

            socket.Connect(endPoint);

            // Send a message to the Python server
            string message = "Hello from C#!";
            byte[] messageBytes = Encoding.ASCII.GetBytes(message);
            socket.Send(messageBytes);

            // Receive a response from the Python server
            byte[] buffer = new byte[1024];
            int bytesReceived = socket.Receive(buffer);
            string response = Encoding.ASCII.GetString(buffer, 0, bytesReceived);
            Console.WriteLine("Response from Python server: " + response);

            // Close the socket when finished
            socket.Close();
        }
        
    }
}
