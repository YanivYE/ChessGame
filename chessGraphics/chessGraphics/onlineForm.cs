using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Threading;

namespace chessGraphics
{
    public partial class onlineForm : Form
    {
        private Square srcSquare;
        private Square dstSquare;

        private pipe enginePipe;
        Button[,] matBoard;

        bool isCurPlWhite = true;
        bool isGameOver = false;
        
        const int BOARD_SIZE = 8;
        static Server _server;
        String _currentColor = "White";

        public onlineForm(Server server)
        {
            InitializeComponent();
            _server = server;
            this.Text = "You Are Player Color: " + server._player;

            backgroundWorker1.DoWork += new DoWorkEventHandler(backgroundWorker1_DoWork);
        }

        private void backgroundWorker1_DoWork(object sender, DoWorkEventArgs e)
        {
            if (!_server._player.Equals(lblCurrentPlayer.Text))
            {
                String move = _server.getMessageFromServer();

                if (move != "quit" && move != "pong")
                {
                    receiveMove(move);
                }
                else if(move != "quit")
                {
                    MessageBox.Show("Connection to server has lost. Bye bye.");
                    this.Close();
                    return;
                }
            }

            if(!_server.isConnected())
            {
                MessageBox.Show("Connection to server has lost. Bye bye.");
                this.Close();
                return;
            }
        }
        
        private void initForm()
        {
            enginePipe.connect();

            Invoke((MethodInvoker)delegate {  

                lblWaiting.Visible = false;
                lblCurrentPlayer.Visible = true;
                label1.Visible = true;

                string s = enginePipe.getEngineMessage();

                if (s.Length != (BOARD_SIZE * BOARD_SIZE + 1))
                {
                    MessageBox.Show("The length of the board's string is not according the PROTOCOL");
                    this.Close();

                }
                else
                {
                    isCurPlWhite = (s[s.Length - 1] == '0');
                    paintBoard(s);

                }
            });

            if(!backgroundWorker1.IsBusy)
            {
                backgroundWorker1.RunWorkerAsync();
            }
        }

        Thread connectionThread;
        private void Form1_Load(object sender, EventArgs e)
        {
            //System.Diagnostics.Process.Start("C:\\Users\\user\\Desktop\\C++\\week7+8\\chess_project\\Chess\\x64\\Debug\\Chess.exe");

            enginePipe = new pipe();
            //this.Show();
            
            //MessageBox.Show("Press OK to start waiting for engine to connect...");
            connectionThread = new Thread(initForm);
            connectionThread.Start();
            connectionThread.IsBackground = true;

            if (!backgroundWorker1.IsBusy)
            {
                backgroundWorker1.RunWorkerAsync();
            }
            //initForm();
        }

        Image getImageBySign(char sign)
        {
            switch (sign)
            {
                case 'q':
                    return Properties.Resources.q_black;
                case 'Q':
                    return Properties.Resources.q_white;
                case 'k':
                    return Properties.Resources.k_black;
                case 'K':
                    return Properties.Resources.k_white;
                case 'p':
                    return Properties.Resources.p_black;
                case 'P':
                    return Properties.Resources.p_white;
                case 'r':
                    return Properties.Resources.r_black;
                case 'R':
                    return Properties.Resources.r_white;
                case 'n':
                    return Properties.Resources.n_black;
                case 'N':
                    return Properties.Resources.n_white;
                case 'b':
                    return Properties.Resources.b_black;
                case 'B':
                    return Properties.Resources.b_white;
                case '#':
                    return null;
                default:
                    return Properties.Resources.x;

            }
        }

        private void paintBoard(string board)
        {
            int i, j, z=0;

            matBoard = new Button[BOARD_SIZE, BOARD_SIZE];

            btnBoard.FlatAppearance.MouseOverBackColor = Color.LightGray;
            
            Button newBtn;
            Point pnt;

            int currentWidth = btnBoard.Location.X;
            int currentHeight = btnBoard.Location.Y;
            
            bool isColBlack = true;
            bool isRowBlack = true ;
            
            this.SuspendLayout();

            lblCurrentPlayer.Text = isCurPlWhite ? "White" : "Black";

            for (i = 0; i < BOARD_SIZE; i++)
            {
                currentWidth = btnBoard.Location.X;
                isColBlack = isRowBlack;

                for (j = 0; j < BOARD_SIZE; j++)
                {
                    newBtn = new Button();
                    matBoard[i, j] = newBtn;

                    newBtn.FlatAppearance.MouseOverBackColor = btnBoard.FlatAppearance.MouseOverBackColor ;
                    newBtn.BackColor = isColBlack ? Color.Gray : Color.White;
                    newBtn.FlatAppearance.BorderColor = btnBoard.FlatAppearance.BorderColor;
                    newBtn.FlatAppearance.BorderSize = btnBoard.FlatAppearance.BorderSize;
                    newBtn.FlatStyle = btnBoard.FlatStyle;

                    newBtn.Size = new System.Drawing.Size(btnBoard.Width, btnBoard.Height);
                    newBtn.Tag = new Square(i, j);
                    pnt = new Point(currentWidth, currentHeight );
                    newBtn.Location = pnt;
                    newBtn.BackgroundImageLayout = ImageLayout.Stretch;

                    newBtn.BackgroundImage  = getImageBySign(board[z]);
                    
                    newBtn.Click += lastlbl_Click;

                    Controls.Add(newBtn);


                    currentWidth += btnBoard.Width;
                    isColBlack = !isColBlack;
                    z++;

                }

                isRowBlack = !isRowBlack;
                currentHeight += btnBoard.Height;

            }

            Controls.Remove(btnBoard);
            this.ResumeLayout(false);
        }

        void lastlbl_Click(object sender, EventArgs e)
        {

            if (!enginePipe.isConnected())
            {
                MessageBox.Show("Connection to engine has lost. Bye bye.");
                this.Close();
                return;
            }

            if (!_server.isConnected())
            {
                MessageBox.Show("Connection to server has lost. Bye bye.");
                this.Close();
                return;
            }

            if (_server._player == lblCurrentPlayer.Text)
            {
                Button b = (Button)sender;
                if (srcSquare != null)
                {
                    // unselected
                    if (matBoard[srcSquare.Row, srcSquare.Col] == b)
                    {

                        matBoard[srcSquare.Row, srcSquare.Col].FlatAppearance.BorderColor = Color.Blue;
                        srcSquare = null;
                    }
                    else
                    {
                        dstSquare = (Square)b.Tag;
                        matBoard[dstSquare.Row, dstSquare.Col].FlatAppearance.BorderColor = Color.DarkGreen;

                        if (_currentColor.Equals(this.lblCurrentPlayer.Text))
                        {
                            if(_server.isConnected())
                            {
                                if(!_server.sendMessageToServer(srcSquare.ToString() + dstSquare.ToString()))
                                {
                                    MessageBox.Show("Connection to engine has lost. Bye bye.");
                                    this.Close();
                                    return;
                                }
                            }
                        }

                        Thread t = new Thread(playMove);
                        t.Start();
                        //   t.IsBackground = true;
                        //playMove();
                    }
                }
                else
                {
                    srcSquare = (Square)b.Tag;
                    matBoard[srcSquare.Row, srcSquare.Col].FlatAppearance.BorderColor = Color.DarkGreen;
                }
            }  
            else
            {
                MessageBox.Show("Not Your Turn!", "Error");
            }

        }

        // messages should be according the protocol.
        // index is the message number in the protocol
        string[] messages =  {
            "Valid move",
            "Valid move - you made chess",
            "Invalid move - not your player",
            "Invalid move - destination is not free",
            "Invalid move - chess wil occure",
            "Invalid move - out of bounds",
            "Invalid move - illegeal movement with piece",
            "Invalid move - source and dest are equal",
            "Game over - check mate",
            "Valid move - you made castling",
            "Unknown message"
            };

        string convertEngineToText(string m)
        {
            // TODO: check what does try parse do, and see if works not only with string with 1 tav
            int res;
            bool b = int.TryParse(new string(m[0], 1), out res);

            if (!b || res < 0 || res >= messages.Length)
                return messages[messages.Length - 1];

            return messages[res];
        }

        void playMove()
        {
            if (isGameOver)
                return;

            try
            {
                 Invoke((MethodInvoker)delegate {

                     lblEngineCalc.Visible = true;
            
                     lblMove.Text = string.Format("Move from {0} to {1}", srcSquare, dstSquare);
                    lblMove.Visible = true;
                    //lblEngineCalc.Invalidate();
            
                    label2.Visible = false;
                    lblResult.Visible = false;

                    this.Refresh();
            

                    // should send pipe to engine
                    enginePipe.sendEngineMove(srcSquare.ToString() + dstSquare.ToString());
                     // should get pipe from engine
                     string m = enginePipe.getEngineMessage();

                    if (!enginePipe.isConnected())
                    {
                        MessageBox.Show("Connection to engine has lost. Bye bye.");
                        this.Close();
                        return;
                    }

                     if (!_server.isConnected())
                     {
                         MessageBox.Show("Connection to server has lost. Bye bye.");
                         this.Close();
                         return;
                     }

                     string res = convertEngineToText(m);

                     if (res.ToLower().StartsWith("game over"))
                    {
                        isGameOver = true;
                    }
                    else if (res.ToLower().StartsWith("valid"))
                    {
                        isCurPlWhite = !isCurPlWhite;
                        lblCurrentPlayer.Text = isCurPlWhite ? "White" : "Black";

                         matBoard[dstSquare.Row, dstSquare.Col].BackgroundImage = matBoard[srcSquare.Row, srcSquare.Col].BackgroundImage;
                        matBoard[srcSquare.Row, srcSquare.Col].BackgroundImage = null;

                        matBoard[srcSquare.Row, srcSquare.Col].FlatAppearance.BorderColor = Color.Blue;
                        matBoard[dstSquare.Row, dstSquare.Col].FlatAppearance.BorderColor = Color.Blue;

                        lblEngineCalc.Visible = false;
                        lblResult.Text = string.Format("{0}", res);
                        lblResult.Visible = true;
                        label2.Visible = true;
                        this.Refresh();

                        //Square srcRook = new Square(1, 2);
                        // TODO: code 9 - CASTLING check if contains made castling move
                        // from messages array
                        if (!(Int32.Parse(m.ToLower()) > 1 && Int32.Parse(m.ToLower()) < 8))
                        {
                            _currentColor = lblCurrentPlayer.Text;
                        }

                        if (m.ToLower().Contains("9"))
                        {
                            lblEngineCalc.Visible = false;
                            lblResult.Text = string.Format("{0}", res);
                            lblResult.Visible = true;
                            label2.Visible = true;
                            this.Refresh();

                            string[] rookPlacements = m.Split(',');
                            int srcRow = rookPlacements[1][0] - '0';
                            int dstRow = rookPlacements[3][0] - '0';
                            int srcCol = rookPlacements[2][0] - '0';
                            int dstCol = rookPlacements[4][0] - '0';
                            Square srcRook = new Square(srcRow, srcCol);
                            Square dstRook = new Square(dstRow, dstCol);

                            matBoard[dstRook.Row, dstRook.Col].BackgroundImage = matBoard[srcRook.Row, srcRook.Col].BackgroundImage;
                            matBoard[srcRook.Row, srcRook.Col].BackgroundImage = null;

                            matBoard[srcRook.Row, srcRook.Col].FlatAppearance.BorderColor = Color.Blue;
                            matBoard[dstRook.Row, dstRook.Col].FlatAppearance.BorderColor = Color.Blue;

                            Invoke((MethodInvoker)delegate
                            {
                                if (srcRook != null)
                                    matBoard[srcRook.Row, srcRook.Col].FlatAppearance.BorderColor = Color.Blue;

                                if (dstRook != null)
                                    matBoard[dstRook.Row, dstRook.Col].FlatAppearance.BorderColor = Color.Blue;

                                dstRook = null;
                                srcRook = null;

                            });

                            lblEngineCalc.Visible = false;
                            lblResult.Text = string.Format("{0}", res);
                            lblResult.Visible = true;
                            label2.Visible = true;
                            this.Refresh();
                        }
                    }

                    lblEngineCalc.Visible = false;
                    lblResult.Text = string.Format("{0}", res);
                    lblResult.Visible = true;
                    label2.Visible = true;
                    this.Refresh();
                 });

                if (!backgroundWorker1.IsBusy)
                {
                    backgroundWorker1.RunWorkerAsync();
                }
            }
                catch
                {

                }
                finally
                {
                try
                {
                    Invoke((MethodInvoker)delegate
                    {
                        if (srcSquare != null)
                            matBoard[srcSquare.Row, srcSquare.Col].FlatAppearance.BorderColor = Color.Blue;

                        if (dstSquare != null)
                            matBoard[dstSquare.Row, dstSquare.Col].FlatAppearance.BorderColor = Color.Blue;

                        dstSquare = null;
                        srcSquare = null;

                    });

                    if (!backgroundWorker1.IsBusy)
                    {
                        backgroundWorker1.RunWorkerAsync();
                    }
                }
                catch
                {

                }
            }
        }

        // This method will be called when the other player makes a move
        void receiveMove(string move)
        {
            String src = move.Substring(0, 2);
            String dst = move.Substring(2, 2);

            for(int i = 0; i < BOARD_SIZE; i++)
            {
                for(int j = 0; j < BOARD_SIZE; j++)
                {
                    if (matBoard[i, j].Tag.ToString().Equals(src))
                    {
                        srcSquare = (Square)matBoard[i, j].Tag;
                    }
                    else if (matBoard[i, j].Tag.ToString().Equals(dst))
                    {
                        dstSquare = (Square)matBoard[i, j].Tag;
                    }
                }
            }

            Thread t = new Thread(playMove);
            t.Start();

        }

        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            enginePipe.sendEngineMove("quit");
            enginePipe.close();

            Application.Exit();
        }

        private void backgroundWorker1_RunWorkerCompleted(object sender, RunWorkerCompletedEventArgs e)
        {
            if (e.Cancelled == true)
            {
                Console.WriteLine("Canceled!");
            }
            else if (e.Error != null)
            {
                Console.WriteLine("Error: " + e.Error.Message);
            }
            else
            {
                Console.WriteLine("Done!");
            }
        }

    }
}
