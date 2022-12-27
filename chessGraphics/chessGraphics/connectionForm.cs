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
        private BackgroundWorker worker;
        bool validIP = false, firstClick = true;
        Server _server;
        public connectionForm()
        {
            InitializeComponent();
            _server = new Server(this);
            worker = new BackgroundWorker();
            worker.DoWork += worker_DoWork;
            worker.WorkerSupportsCancellation = true;
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

            if (_server.connectToServer(validIP))
            {
                this.button1.Enabled = false;
                this.ipBox.Enabled = false;
            }

            if(firstClick)
            {
                worker.RunWorkerAsync();
                firstClick = false;
            }

        }

        private void connectionForm_FormClosed(object sender, FormClosedEventArgs e)
        {
            Application.Exit();
        }

        private void worker_DoWork(object sender, DoWorkEventArgs e)
        {
            string wantedResult = "2";
            string result = "";
            
            while (!worker.CancellationPending || result != wantedResult)
            {
                result = _server.shouldStartGame();
                // Check for new messages here
                Thread.Sleep(1000); // wait for 1 second before checking again
            }
        }
    }
}
