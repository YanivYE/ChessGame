using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Net;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.CompilerServices;
using System.Drawing;
using System.Windows.Forms;
using System.ComponentModel;
using System.Threading;

namespace chessGraphics
{
    public class Server
    {
        public static TcpClient _client;
        NetworkStream _nwStream;
        string response;
        public string _player;

        private connectionForm _connectionForm;
        public Server(connectionForm connectionForm) 
        {
            _connectionForm = connectionForm;
        }

        // In the Server class
        public bool connectToServer(bool validIP)
        {
            try
            {
                const int PORT = 3389;

                if (validIP)
                {
                    // Connect to the server
                    _client = new TcpClient();
                    _client.Connect(IPAddress.Parse(_connectionForm.ipBox.Text), PORT);
                    _nwStream = _client.GetStream();

                    if (_client.Connected)
                    {
                        _connectionForm.isConnected.Text = "CONNECTED";
                        _connectionForm.isConnected.ForeColor = Color.Green;
                    }

                    response = getMessageFromServer();

                    // If the server sends a message indicating that there are 2 clients connected,
                    // transfer both clients to the gameForm form
                    if (response.Equals("2") || response.Equals("1"))
                    {
                        //if(response.Equals("2"))
                        //{
                        //    // Send a message to the server indicating that this client is ready to start the game
                        //    sendMessageToServer("startgame");
                        //}

                        lobbyForm lobby = new lobbyForm(this);
                        lobby.Show();
                        //onlineForm gameForm = new onlineForm(this);
                        //gameForm.Show();
                        this._connectionForm.Hide();
                    }
                    else if(response.Equals("quit"))
                    {
                        MessageBox.Show("Connection to server has lost. Bye bye.");
                        this._connectionForm.Close();
                        return false;
                    }
                }
                else
                {
                    MessageBox.Show("Illegail IPV4 Adress. Pleae enter in this format: X.X.X.X, thank you.", "Invalid IP",
                        MessageBoxButtons.OK, MessageBoxIcon.Error);

                    _connectionForm.ipBox.Clear();

                    return false;
                }
            }
            catch (System.Net.Sockets.SocketException e)
            {
                MessageBox.Show("Couldn't Connect. Please try agaian later", "Connection not established.",
                    MessageBoxButtons.OK, MessageBoxIcon.Error);

                _connectionForm.ipBox.Clear();

                _connectionForm.button1.Enabled = true;
                _connectionForm.ipBox.Enabled = true;

                return false;
            }

            return true;
        }

        public string getMessageFromServer()
        {
            if(isConnected())
            {
                try
                {
                    var buffer = new byte[1024];
                    int bytesReceived = _client.GetStream().Read(buffer, 0, 1024);
                    return Encoding.ASCII.GetString(buffer, 0, bytesReceived);
                }
                catch
                {

                }
            }

            return "";
        }

        public bool sendMessageToServer(string message)
        {
            try
            {
                byte[] messageBytes = Encoding.ASCII.GetBytes(message);
                int messageByteLength = Buffer.ByteLength(messageBytes);
                _nwStream.Write(messageBytes, 0, messageByteLength);

                return true;
            }
            catch
            {
            }
            return false;
        }

        public bool isConnected()
        {
            try
            {
                Thread t = new Thread(() => sendMessageToServer(""));
                t.Start();

                if (_client.GetStream() == null)
                {
                    return false;
                }

                t.Abort();
                return true;
            }
            catch
            {

            }
            return false;
        }
    }
}
