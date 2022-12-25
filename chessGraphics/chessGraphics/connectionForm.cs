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
        Server _server;
        public connectionForm()
        {
            InitializeComponent();
            _server = new Server(this);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            byte tempForParsing;

            if (String.IsNullOrWhiteSpace(this.ipBox.Text))
            {
                validIP = false;

                // for printing bad nessage
                _server.connectToServer(validIP);

                return;
            }

            string[] splitValues = this.ipBox.Text.Split('.');
            if (splitValues.Length != 4)
            {
                validIP = false;

                // for printing bad nessage
                _server.connectToServer(validIP);

                return;
            }

            validIP = splitValues.All(r => byte.TryParse(r, out tempForParsing));
            _server.connectToServer(validIP);

            if (validIP)
            {
                this.button1.Enabled = false;
                this.ipBox.Enabled = false;
            }
        }

        private void connectionForm_FormClosed(object sender, FormClosedEventArgs e)
        {
            Application.Exit();
        }
    }
}
