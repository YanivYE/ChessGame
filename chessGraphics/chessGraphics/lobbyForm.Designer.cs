namespace chessGraphics
{
    partial class lobbyForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.color = new System.Windows.Forms.Label();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.SuspendLayout();
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("Microsoft Sans Serif", 25.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(177)));
            this.label5.Location = new System.Drawing.Point(12, 55);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(632, 52);
            this.label5.TabIndex = 0;
            this.label5.Text = "Waiting for players to connect...";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Font = new System.Drawing.Font("Microsoft Sans Serif", 25.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(177)));
            this.label6.Location = new System.Drawing.Point(84, 201);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(243, 52);
            this.label6.TabIndex = 1;
            this.label6.Text = "Your Color:";
            // 
            // color
            // 
            this.color.AutoSize = true;
            this.color.Font = new System.Drawing.Font("Microsoft Sans Serif", 25.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(177)));
            this.color.Location = new System.Drawing.Point(351, 201);
            this.color.Name = "color";
            this.color.Size = new System.Drawing.Size(149, 52);
            this.color.TabIndex = 2;
            this.color.Text = "NONE";
            // 
            // timer1
            // 
            this.timer1.Interval = 3000;
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // lobbyForm
            // 
            this.ClientSize = new System.Drawing.Size(711, 360);
            this.Controls.Add(this.color);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.label5);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.Name = "lobbyForm";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        public System.Windows.Forms.Label isConnected;
        public System.Windows.Forms.TextBox ipBox;
        private System.Windows.Forms.Label label4;
        public System.Windows.Forms.Button button1;
        private System.Windows.Forms.Label label3;
        public System.Windows.Forms.Label numClients;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label color;
        private System.Windows.Forms.Timer timer1;
    }
}