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

namespace chessGraphics
{
    internal class Server
    {
        public static TcpClient _client;
        NetworkStream _nwStream;

        private connectionForm _connectionForm;
        public Server(connectionForm connectionForm) 
        {
            _connectionForm = connectionForm;
        }

        public bool connectToServer(bool validIP, BackgroundWorker worker)
        {
            try
            {
                const int PORT = 8200;

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

                    string response = shouldStartGame(worker);

                    _connectionForm.numClients.Text = response;

                    return true;
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
        }

        public void sendMessageToServer(string message)
        {
            byte[] messageBytes = Encoding.ASCII.GetBytes(message);
            int messageByteLength = Buffer.ByteLength(messageBytes);
            _nwStream.Write(messageBytes, 0, messageByteLength);
        }

        public string shouldStartGame(BackgroundWorker worker)
        {
            try
            { 
                var buffer = new byte[1024];
                int bytesReceived = _client.GetStream().Read(buffer, 0, 1024);
                string response = Encoding.ASCII.GetString(buffer, 0, bytesReceived);

                if (response.Equals("startgame") || response.Equals("2"))
                {
                    worker.CancelAsync();

                    onlineForm onlineGameForm = new onlineForm();
                    onlineGameForm.Show();


                    this._connectionForm.Hide();

                    sendMessageToServer("startgame");

                    return response;
                }

                return response;
            }
            catch (System.IO.IOException e)
            {
                MessageBox.Show("Connection to server has lost. Bye bye.");
                Application.Exit();
                return "";
            }
            catch(System.InvalidOperationException e1)
            {
                return "";
            }
        }

    }
}
