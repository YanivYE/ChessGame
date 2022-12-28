using System;
using System.Net;
using System.Net.Sockets;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;

namespace chessGraphics
{
    public class engine
    {
        Socket _listener;
        IPEndPoint _localEndPoint;
        Socket _handler;

        public engine()
        {
            

        }

        public bool connect()
        {
            _localEndPoint = new IPEndPoint(IPAddress.Any, 8200);

            _listener = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);

            _listener.Bind(_localEndPoint);

            _listener.Listen(1);

            _handler = _listener.Accept();

            return _handler.Connected;
        }

        public bool isConnected()
        {
            if(_handler != null )
            {
                return _handler.Connected;
            }

            return false;
        }

        public string getEngineMessage()
        {
            byte[] buffer = new byte[1024];

            int bytesReceived = _handler.Receive(buffer);

            string data = Encoding.ASCII.GetString(buffer, 0, bytesReceived);

            return data;
        }

        public void sendEngineMove(string move)
        {
            if (!isConnected())
                return;

            // Send a response to the client
            byte[] response = Encoding.ASCII.GetBytes(move);
            _handler.Send(response);
        }

        public void close()
        {
            // Close the socket
            _handler.Shutdown(SocketShutdown.Both);
            _handler.Close();
        }
    }

    public class EngineStreamString
    {
        engine myEngine = new engine();

        public EngineStreamString()
        {
            
        }

        public string getStringFromEngine()
        {
            // protocol:
            // 0 - valid move
            // 1 - valid move (you made chess)
            // 2 - invalid move (not your player)
            // 3 - invalid move (destination is not free)
            // 4 - invalid move (chess will occur)
            // 5 - invalid move (out of bounds)
            // 6 - invalid move (illegal movement with piece)
            // 7 - Invalid move - source and dest are equal
            // 8 - check mate

            byte[] buffer = Encoding.ASCII.GetBytes(myEngine.getEngineMessage());

            String MyString = Encoding.ASCII.GetString(buffer).TrimEnd((Char)0);
            return Encoding.ASCII.GetString(buffer).TrimEnd((Char)0);
        }

        public void sendMoveToEngine(string outString)
        {
            // protocol:
            // e2e4
            // move e2 to e4

            byte[] t = Encoding.ASCII.GetBytes(outString);
            byte[] inBuffer = new byte[t.Length + 1];

            for (int i = 0; i < t.Length; i++)
            {
                inBuffer[i] = t[i];
            }
            inBuffer[inBuffer.Length - 1] = 0;

            try
            {
                myEngine.sendEngineMove(Encoding.ASCII.GetString(inBuffer));
            }
            catch
            {

            }
        }
    }

}
