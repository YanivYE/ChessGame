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
    public partial class lobbyForm : Form
    {
        Server _server;
        BackgroundWorker _worker;
        string _color;

        public lobbyForm(Server server)
        {
            InitializeComponent();
            _server = server;
            _worker = new BackgroundWorker();

            _worker.WorkerReportsProgress = true;
            _worker.WorkerSupportsCancellation = true;

            _worker.DoWork += Worker_DoWork;
            _worker.RunWorkerCompleted += Worker_RunWorkerCompleted;

            // Start the worker
            _worker.RunWorkerAsync();
        }

        void Worker_DoWork(object sender, DoWorkEventArgs e)
        {
            _color = _server.getMessageFromServer();

            // Check if the worker has been cancelled
            if ((sender as BackgroundWorker).CancellationPending)
            {
                e.Cancel = true;
                return;
            }

            if(_color.Equals("White") || _color.Equals("Black"))
            {
                _worker.CancelAsync();
                return;
            }
        }

        void Worker_RunWorkerCompleted(object sender, RunWorkerCompletedEventArgs e)
        {
            if (e.Error != null)
            {
                Console.WriteLine("Error: " + e.Error.Message);
            }
            else
            {
                this.color.Text = _color;

                timer1.Start();
            }
        }

        private void lobbyForm_FormClosed(object sender, FormClosedEventArgs e)
        {
            Application.Exit();
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            onlineForm gameForm = new onlineForm(_server);
            gameForm.Show();

            this.Hide();

            timer1.Stop();
        }
    }
}
