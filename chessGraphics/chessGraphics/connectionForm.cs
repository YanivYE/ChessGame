using System;
using System.Drawing;
using System.Linq;
using System.Net.Sockets;
using System.Net;
using System.Threading;
using System.Windows.Forms;
using System.Text;

namespace chessGraphics
{
    public partial class connectionForm : Form
    {
        bool validIP = false;

        public connectionForm()
        {
            InitializeComponent();
        }

        private void connectToServer()
        {
            try
            {
                const int PORT = 8200;

                if (validIP)
                {
                    // Connect to the server
                    var client = new TcpClient();
                    client.Connect(IPAddress.Parse(this.textBox1.Text), PORT);

                    if (client.Connected)
                    {
                        this.isConnected.Text = "CONNECTED";
                        this.isConnected.ForeColor = Color.Green;
                    }

                    var buffer = new byte[1024];
                    int bytesReceived = client.GetStream().Read(buffer, 0, 1024);
                    var response = Encoding.ASCII.GetString(buffer, 0, bytesReceived);
                    this.numClients.Text = response;
                }
                else
                {
                    MessageBox.Show("Illegail IPV4 Adress. Pleae enter in this format: X.X.X.X, thank you.", "Invalid IP",
                        MessageBoxButtons.OK, MessageBoxIcon.Error);

                    this.textBox1.Clear();
                }
            }
            catch(System.Net.Sockets.SocketException e)
            {
                MessageBox.Show("Couldn't Connect. Please try agaian later", "Connection not established.",
                    MessageBoxButtons.OK, MessageBoxIcon.Error);

                this.textBox1.Clear();

                validIP = false;

                this.button1.Enabled = true;
                this.textBox1.Enabled = true;
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            byte tempForParsing;

            if (String.IsNullOrWhiteSpace(this.textBox1.Text))
            {
                validIP = false;

                // for printing bad nessage
                connectToServer();

                return;
            }

            string[] splitValues = this.textBox1.Text.Split('.');
            if (splitValues.Length != 4)
            {
                validIP = false;

                // for printing bad nessage
                connectToServer();

                return;
            }

            validIP = splitValues.All(r => byte.TryParse(r, out tempForParsing));
            connectToServer();

            if (validIP)
            {
                this.button1.Enabled = false;
                this.textBox1.Enabled = false;
            }
        }

        private void connectionForm_FormClosed(object sender, FormClosedEventArgs e)
        {
            Application.Exit();
        }
    }
}
