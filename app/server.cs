using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Net;
using System.Text;

namespace app
{
    class Server
    {
        // Create a new socket
        static Socket socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);

            // Connect to the Python server at the specified IP address and port
        static IPAddress serverAddr = IPAddress.Parse("127.0.0.1");

        static void Main(string[] args)
        {
            IPEndPoint endPoint = new IPEndPoint(serverAddr, 8200);

            try
            {
                socket.Connect(endPoint);
            }
            catch(Exception e)
            {
                Console.WriteLine("Cannot connect. Please Try Again Later.");
                return;
            }

            // Send a message to the Python server
            string message = "";

            while(message != "QUIT")
            {   
                Console.WriteLine("Connected!");

                // Send a message to the Python server
                message = Console.ReadLine();
                byte[] messageBytes = Encoding.ASCII.GetBytes(message);
                socket.Send(messageBytes);

                // Receive a response from the Python server
                byte[] buffer = new byte[1024];
                int bytesReceived = socket.Receive(buffer);
                string response = Encoding.ASCII.GetString(buffer, 0, bytesReceived);
                Console.WriteLine("Response from Python server: " + response);
            }

            // Close the socket when finished
            socket.Close();

        }
        
    }
}
