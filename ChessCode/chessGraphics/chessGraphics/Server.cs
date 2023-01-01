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
        public static TcpClient _client; // the tcp client that will connect
        NetworkStream _nwStream; // the network stream
        string _response; // the response from server
        public string _player; // the player by response of server
        private connectionForm _connectionForm; // connection form object

        /*
         * Function is a constructor for Server, it gets a connection form and sets it to the
         * value of a member of the Server class.
         * Input: connectionForm - a connection form object
         * Output: none
         */
        public Server(connectionForm connectionForm) 
        {
            _connectionForm = connectionForm;
        }

        /*
         * Function gets a bool that represents if the ip is valid or not, and tries to connect to
         * the server if it't valid, if not it will show error message.
         * Input: validIP - if the ip is valid
         * Output: if connection was established
         */
        public bool connectToServer(bool validIP)
        {
            // port 3389 becasue google server in cloud is open for traffic in that port
            const int PORT = 3389;

            try
            {
                // check if ip is valid
                if (validIP)
                {
                    // if so, connect to the server
                    _client = new TcpClient();
                    _client.Connect(IPAddress.Parse(_connectionForm.ipBox.Text), PORT);
                    _nwStream = _client.GetStream();

                    // check if connected
                    if (_client.Connected)
                    {
                        // if so change form properties
                        _connectionForm.isConnected.Text = "CONNECTED";
                        _connectionForm.isConnected.ForeColor = Color.Green;
                    }
                    
                    // get message from server(should be the number client
                    _response = getMessageFromServer();

                    // if we get the correct response(number of client), transfer us to lobby form
                    if (_response.Equals("2") || _response.Equals("1"))
                    {
                        lobbyForm lobby = new lobbyForm(this);
                        lobby.Show();

                        this._connectionForm.Hide();
                    }
                    // else server wanted to quit, so close form
                    else if (_response.Equals("quit"))
                    {
                        MessageBox.Show("Connection to server has lost. Bye bye.");
                        this._connectionForm.Close();
                        return false;
                    }
                }
                else
                {
                    // bad ip message
                    MessageBox.Show("Illegail IPV4 Adress. Pleae enter in this format: X.X.X.X.", "Invalid IP",
                        MessageBoxButtons.OK, MessageBoxIcon.Error);

                    // clear ip box 
                    _connectionForm.ipBox.Clear();

                    return false;
                }

            }
            catch 
            {
                // error happened, couldn't connect
                MessageBox.Show("Couldn't Connect. Please check IP adress format, or if server is open.", "Connection not established.",
                    MessageBoxButtons.OK, MessageBoxIcon.Error);

                // reset properties of form
                _connectionForm.ipBox.Clear();

                _connectionForm.button1.Enabled = true;
                _connectionForm.ipBox.Enabled = true;

                return false;
            }

            return true;
        }

        /*
         * Function gets a message from the server and returns it
         * Input: none
         * Output: the message from the server
         */
        public string getMessageFromServer()
        {
            // check if connected
            if(isConnected())
            {
                try
                {
                    var buffer = new byte[1024];
                    int bytesReceived = _client.GetStream().Read(buffer, 0, 1024); // get message

                    // encode to ascii and return it
                    return Encoding.ASCII.GetString(buffer, 0, bytesReceived);
                }
                // if error happened so catch it, it means recieving message was bad and return ""
                catch
                {

                }
            }

            // if not connected, return nothing
            return "";
        }

        /*
         * Function gets a message to send to the server, sends it, and returns if the sending
         * was valid.
         * Input: message - the message to send to the server
         * Output: if the sending of the message was valid
         */
        public bool sendMessageToServer(string message)
        {
            // try to send message, if there was an error so the sending was invalid and return false.
            try
            {
                // get array of bytes to send from message
                byte[] messageBytes = Encoding.ASCII.GetBytes(message);
                int messageByteLength = Buffer.ByteLength(messageBytes); // get length

                // send message
                _nwStream.Write(messageBytes, 0, messageByteLength);

                return true;
            }
            catch
            {
            }
            return false;
        }

        /*
         * Function returns if the client is connected to the server. *****tcp.client is stupid,
         * it checks if the client is connected only from seeing the last interaction with
         * the client... so i had to think how to do it differently******
         * Input: none
         * Output: if the client is still connected to the server
         */
        public bool isConnected()
        {
            // try to check a connection, if there was an error so client isn't connected, return false.
            try
            {
                // just try to send a message
                Thread t = new Thread(() => sendMessageToServer(""));
                t.Start();

                // if client stream is null so server is not connected
                if (_client.GetStream() == null)
                {
                    return false;
                }

                // if everything till now was connected, so abort thread and return true
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
