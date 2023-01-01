/*
This file servers as an example of how to use Pipe.h file.
It is recommended to use the following code in your project, 
in order to read and write information from and to the Backend
*/

#include "Headers/pipe.h"
#include <iostream>
#include <thread>
#include "Headers/BoardManager.h"

using std::cout;
using std::endl;
using std::string;


void main()
{
	srand(time_t(NULL));
	
	Pipe p;
	string ans;
	bool isConnectedPipe = p.connectToPipe();

	while (!isConnectedPipe)
	{
		cout << "cant connect to graphics" << endl;
		cout << "Do you try to connect again or exit? (0-try again, 1-exit)" << endl;
		std::cin >> ans;

		if (ans == "0" && !isConnectedPipe)
		{
			cout << "trying to connect again to pipe.." << endl;
			Sleep(5000);
			isConnectedPipe = p.connectToPipe();
		}
		else
		{
			p.close();

			return;
		}
	}
	

	char msgToGraphics[1024];
	// msgToGraphics should contain the board string accord the protocol
	// YOUR CODE

	strcpy_s(msgToGraphics, "rnbkqbnrpppppppp################################PPPPPPPPRNBKQBNR0"); // just example...
	// copy to vector
	BoardManager board = BoardManager(msgToGraphics);
	GameLogic algorithm = GameLogic(msgToGraphics);
	p.sendMessageToGraphics(msgToGraphics);   // send the board string

	// get message from graphics
	string msgFromGraphics = p.getMessageFromGraphics();
	string msgFromServer = "";

	//p.sendMessageToServer(msgFromGraphics, serverSocket);

	while (msgFromGraphics != "quit")
	{
		// should handle the string the sent from graphics
		// according the protocol. Ex: e2e4           (move e2 to e4)
		
		// YOUR CODE
		strcpy_s(msgToGraphics, board.movePieces(msgFromGraphics, algorithm).c_str()); // msgToGraphics should contain the result of the operation

		// return result to graphics		
		p.sendMessageToGraphics(msgToGraphics);

		// get message from graphics
		msgFromGraphics = p.getMessageFromGraphics();
		//p.sendMessageToServer(msgFromGraphics, serverSocket);

		//msgFromServer = p.getMessageFromServer(serverSocket);
		//cout << msgFromServer << endl;
	}

	p.close();
}