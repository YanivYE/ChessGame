using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
using System.Threading;
using System.Diagnostics;

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
        static Server _server; // server
        String _currentColor = "White"; // current player 

        public onlineForm(Server server)
        {
            InitializeComponent();
            // set server member
            _server = server;

            // set form title, text to color
            this.Text = "You Are Player Color: " + server._player;
            this.playerColor.Text = server._player;

            /// add background worker and let it check if it should recieve message
            backgroundWorker1.DoWork += new DoWorkEventHandler(backgroundWorker1_DoWork);
        }

        private void backgroundWorker1_DoWork(object sender, DoWorkEventArgs e)
        {
            // check if this player color isn't the current player text(not his turn)
            if (!_server._player.Equals(lblCurrentPlayer.Text))
            {
                // if so, get message from server for the current move
                String move = _server.getMessageFromServer();

                // if the move isn't to quit game
                if (move != "quit")
                {
                    // do move to board
                    receiveMove(move);
                }
                // if the move is quit
                else if(move == "quit")
                {
                    // send message to pipe to quit
                    enginePipe.sendEngineMove("quit");
                    enginePipe.close();

                    // close client and show message
                    MessageBox.Show("Connection to server has lost. Bye bye.");
                    Application.Exit();
                    
                    return;
                }
            }

            // check if at anytime server isn't connected, so exit
            if(!_server.isConnected())
            {
                MessageBox.Show("Connection to server has lost. Bye bye.");
                this.Close();
                return;
            }
        }
        
        private void initForm()
        {
            // start chess exe(engine)
            ProcessStartInfo startInfo = new ProcessStartInfo();
            startInfo.FileName = "Chess.exe";
            startInfo.WindowStyle = ProcessWindowStyle.Minimized;

            Process.Start(startInfo);

            enginePipe.connect();

            Invoke((MethodInvoker)delegate {  

                lblWaiting.Visible = false;
                lblCurrentPlayer.Visible = true;
                playerColor.Visible = true;
                thisPlayer.Visible = true;
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

            // if worker is asleep (idk why he likes to sleep and turn off)
            if(!backgroundWorker1.IsBusy)
            {
                // wake him up
                backgroundWorker1.RunWorkerAsync();
            }
        }

        Thread connectionThread;
        Thread checkServerThread;
        private void Form1_Load(object sender, EventArgs e)
        {
            enginePipe = new pipe();
            //this.Show();
            
            //MessageBox.Show("Press OK to start waiting for engine to connect...");
            connectionThread = new Thread(initForm);
            connectionThread.Start();
            connectionThread.IsBackground = true;

            // check if server is connected to a different thread
            checkServerThread = new Thread(checkServerConnection);
            checkServerThread.Start();
            checkServerThread.IsBackground = true;

            // if worker is asleep (idk why he likes to sleep and turn off)
            if (!backgroundWorker1.IsBusy)
            {
                // wake him up
                backgroundWorker1.RunWorkerAsync();
            }
            //initForm();
        }

        void checkServerConnection()
        {
            // while thread is open
            while(1 == 1)
            {
                // if isn't connected, exit
                if (!_server.isConnected())
                {
                    MessageBox.Show("Connection to server has lost. Bye bye.");
                    Application.Exit();
                    return;
                }
            }
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

            // check for server connection
            if (!_server.isConnected())
            {
                MessageBox.Show("Connection to server has lost. Bye bye.");
                this.Close();
                return;
            }

            // check if it's his turn
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

                        // if we are on this turn, and server is connected
                        if (_currentColor.Equals(this.lblCurrentPlayer.Text) && _server.isConnected())
                        {
                            // send the current message to server, if sending was invalid exit.
                            if (!_server.sendMessageToServer(srcSquare.ToString() + dstSquare.ToString()))
                            {
                                MessageBox.Show("Connection to engine has lost. Bye bye.");
                                this.Close();
                                return;
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
                // if not, bad player!!!
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
            "Valid move - you made castling", // castling move
            "Unknown message"
            };

        string convertEngineToText(string m)
        {
            // because of the castling move, we needed to change the convert function a bit
            int res;
            bool b = int.TryParse(new string(m[0], 1), out res); // get only first tav of returned code

            if (!b || res < 0 || res >= messages.Length)
                // return without the last tav(null)
                return messages[messages.Length - 1];

            // if the code is game over, add a pretty text and not just check mate...
            if (res == 8)
                return messages[res] + "\n" + lblCurrentPlayer.Text + "Wins!";

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

                    // check if server still connected
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

                        // if move was valid, change color of current player
                        if (!((int.Parse(m[0].ToString())) > 1 && (int.Parse(m[0].ToString())) < 8))
                        {
                            _currentColor = lblCurrentPlayer.Text;
                        }

                         // check if we code code 9 - castling move
                        if (m.ToLower().Contains("9"))
                        {
                            // refresh form poperties
                            lblEngineCalc.Visible = false;
                            lblResult.Text = string.Format("{0}", res);
                            lblResult.Visible = true;
                            label2.Visible = true;
                            this.Refresh();

                            // get the rook placement(src, dst) from the code
                            string[] rookPlacements = m.Split(',');
                            int srcRow = rookPlacements[1][0] - '0';
                            int dstRow = rookPlacements[3][0] - '0';
                            int srcCol = rookPlacements[2][0] - '0';
                            int dstCol = rookPlacements[4][0] - '0';

                            // create 2 square that represnets there placements
                            Square srcRook = new Square(srcRow, srcCol);
                            Square dstRook = new Square(dstRow, dstCol);

                            // move the rooks
                            matBoard[dstRook.Row, dstRook.Col].BackgroundImage = matBoard[srcRook.Row, srcRook.Col].BackgroundImage;
                            matBoard[srcRook.Row, srcRook.Col].BackgroundImage = null;
                            matBoard[srcRook.Row, srcRook.Col].FlatAppearance.BorderColor = Color.Blue;
                            matBoard[dstRook.Row, dstRook.Col].FlatAppearance.BorderColor = Color.Blue;

                            // idk what does this do but magshimim put it in playmove
                            Invoke((MethodInvoker)delegate
                            {
                                if (srcRook != null)
                                    matBoard[srcRook.Row, srcRook.Col].FlatAppearance.BorderColor = Color.Blue;

                                if (dstRook != null)
                                    matBoard[dstRook.Row, dstRook.Col].FlatAppearance.BorderColor = Color.Blue;

                                dstRook = null;
                                srcRook = null;

                            });

                            // refresh form poperties
                            lblEngineCalc.Visible = false;
                            lblResult.Text = string.Format("{0}", res);
                            lblResult.Visible = true;
                            label2.Visible = true;
                            this.Refresh();
                        }
                    }

                    // refresh form poperties
                    lblEngineCalc.Visible = false;
                    lblResult.Text = string.Format("{0}", res);
                    lblResult.Visible = true;
                    label2.Visible = true;
                    this.Refresh();
                 });

                // if worker is asleep (idk why he likes to sleep and turn off)
                if (!backgroundWorker1.IsBusy)
                {
                    // wake him up
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

                    // if worker is asleep (idk why he likes to sleep and turn off)
                    if (!backgroundWorker1.IsBusy)
                    {
                        // wake him up
                        backgroundWorker1.RunWorkerAsync();
                    }
                }
                catch
                {

                }
            }
        }

        /*
         * Function gets a move, and plays the move on the board
         */
        void receiveMove(string move)
        {
            // get src, dst
            String src = move.Substring(0, 2);
            String dst = move.Substring(2, 2);

            // check each cube on board
            for(int i = 0; i < BOARD_SIZE; i++)
            {
                for(int j = 0; j < BOARD_SIZE; j++)
                {
                    // check if it's the src/dst square
                    if (matBoard[i, j].Tag.ToString().Equals(src))
                    {
                        // if so set src sqaure to current square
                        srcSquare = (Square)matBoard[i, j].Tag;
                    }
                    else if (matBoard[i, j].Tag.ToString().Equals(dst))
                    {
                        // if so set dst sqaure to current square
                        dstSquare = (Square)matBoard[i, j].Tag;
                    }
                }
            }

            // play move on board
            Thread t = new Thread(playMove);
            t.Start();
        }

        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            enginePipe.sendEngineMove("quit");
            enginePipe.close();

            Application.Exit();
        }

    }
}
