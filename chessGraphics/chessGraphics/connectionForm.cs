using System;
using System.Drawing;
using System.Linq;
using System.Net.Sockets;
using System.Net;
using System.Threading;
using System.Windows.Forms;
using System.Text;
using System.ComponentModel;

namespace chessGraphics
{
    public partial class connectionForm : Form
    {
        bool _validIP = false;
        Server _server;

        public connectionForm()
        {
            InitializeComponent();
            // create new server object, sending this connection form as parameter
            _server = new Server(this);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            byte tempForParsing;
            String ip = this.ipBox.Text; // get ip from ip box
            string[] splitValues;

            // check if empty / or only space characters
            if (String.IsNullOrWhiteSpace(ip))
            {
                // bad ip
                _validIP = false;

                // show error message
                _server.connectToServer(_validIP);

                return;
            }

            // if there is an acatual text, try to split from .
            splitValues = ip.Split('.');

            // if there isn't 4 values from that split, bad ip
            if (splitValues.Length != 4)
            {
                _validIP = false;

                // show error message
                _server.connectToServer(_validIP);

                return;
            }

            // if there is, try to create the ip, if worked so retruns true, if not false
            _validIP = splitValues.All(r => byte.TryParse(r, out tempForParsing));

            // connect and see if established connection
            if (_server.connectToServer(_validIP))
            {
                // if so disable buttons
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
