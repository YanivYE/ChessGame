using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace chessGraphics
{
    public partial class mainForm : Form
    {
        public mainForm()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            offlineForm offlineGameForm = new offlineForm();
            offlineGameForm.Show();

            this.Hide();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            onlineForm onlineGameForm = new onlineForm();
            onlineGameForm.Show();

            this.Hide();
        }

        private void OnMouseEnterButton1(object sender, EventArgs e)
        {
            Color col = button1.BackColor;
            button1.BackColor = Color.FromArgb(110, col.R, col.G, col.B);
        }
        private void OnMouseLeaveButton1(object sender, EventArgs e)
        {
            Color col = button1.BackColor;
            button1.BackColor = Color.FromArgb(80, col.R, col.G, col.B);
        }

        private void OnMouseEnterButton2(object sender, EventArgs e)
        {
            Color col = button2.BackColor;
            button2.BackColor = Color.FromArgb(110, col.R, col.G, col.B);
        }
        private void OnMouseLeaveButton2(object sender, EventArgs e)
        {
            Color col = button2.BackColor;
            button2.BackColor = Color.FromArgb(80, col.R, col.G, col.B);
        }
    }
}
