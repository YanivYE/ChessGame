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
        bool validIP = false, firstClick = true;
        String _ip = "";
        public connectionForm()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            byte tempForParsing;

            if (String.IsNullOrWhiteSpace(this.ipBox.Text))
            {
                validIP = false;

                badIp();

                return;
            }

            string[] splitValues = this.ipBox.Text.Split('.');
            if (splitValues.Length != 4)
            {
                validIP = false;

                badIp();

                return;
            }

            //validIP = splitValues.All(r => byte.TryParse(r, out tempForParsing));
            //
            //if (_server.connectToServer(validIP))
            //{
            //    this.button1.Enabled = false;
            //    this.ipBox.Enabled = false;
            //}


        }

        private void connectionForm_FormClosed(object sender, FormClosedEventArgs e)
        {
            Application.Exit();
        }

        void badIp()
        {
            MessageBox.Show("Illegail IPV4 Adress. Pleae enter in this format: X.X.X.X, thank you.", "Invalid IP",
                        MessageBoxButtons.OK, MessageBoxIcon.Error);

            ipBox.Clear();
        }

    }
}
