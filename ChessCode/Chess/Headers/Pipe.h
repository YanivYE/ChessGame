/****************************** Module Header ******************************\
* Module Name:	CppNamedPipeClient.cpp
* Project:		CppNamedPipeClient
* Copyright (c) Microsoft Corporation.
*
* Named pipe is a mechanism for one-way or bi-directional inter-process
* communication between the pipe server and one or more pipe clients in the
* local machine or across the computers in the intranet:
*
* PIPE_ACCESS_INBOUND:
* Client (GENERIC_WRITE) ---> Server (GENERIC_READ)
*
* PIPE_ACCESS_OUTBOUND:
* Client (GENERIC_READ) <--- Server (GENERIC_WRITE)
*
* PIPE_ACCESS_DUPLEX:
* Client (GENERIC_READ or GENERIC_WRITE, or both) <-->
* Server (GENERIC_READ and GENERIC_WRITE)
*
* This sample demonstrates a named pipe client that attempts to connect to
* the pipe server, \\.\pipe\HelloWorld, with the GENERIC_READ and
* GENERIC_WRITE permissions. The client writes a message to the pipe server
* and receive its response.
*
* This source is subject to the Microsoft Public License.
* See http://www.microsoft.com/opensource/licenses.mspx#Ms-PL.
* All other rights reserved.
*
* History:
* * 1/11/2009 11:20 PM Jialiang Ge Created
\***************************************************************************/

#pragma once
#pragma region Includes
#include "stdafx.h"
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <string>
#include <stdio.h>
#include <conio.h>
#include <tchar.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <iostream>

#pragma endregion

#define BUFFER_SIZE		1024 // 1K

// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")


class Pipe
{
private:
	HANDLE hPipe;
	LPTSTR  strPipeName;

public:

	Pipe()
	{
		// Prepare the pipe name
		strPipeName = (LPTSTR)TEXT("\\\\.\\pipe\\chessPipe");

	}

	bool connectToPipe()
	{
		hPipe = CreateFile(
			strPipeName,			// Pipe name 
			GENERIC_READ |			// Read and write access 
			GENERIC_WRITE,
			0,						// No sharing 
			NULL,					// Default security attributes
			OPEN_EXISTING,			// Opens existing pipe 
			0,						// Default attributes 
			NULL);					// No template file 

		// Break if the pipe handle is valid. 
		if (hPipe != INVALID_HANDLE_VALUE)
			return true;

		if (// Exit if an error other than ERROR_PIPE_BUSY occurs
			GetLastError() != ERROR_PIPE_BUSY
			||
			// All pipe instances are busy, so wait for 5 seconds
			!WaitNamedPipe(strPipeName, 5000))
		{
			_tprintf(_T("Unable to open named pipe %s w/err 0x%08lx\n"),
				strPipeName, GetLastError());
			return false;
		}

		_tprintf(_T("The named pipe, %s, is connected.\n"), strPipeName);
		return true;

	}

	bool connectToLAN(SOCKET& server)
	{
		// Create a new socket
		SOCKET ConnectSocket = INVALID_SOCKET;
		struct addrinfo* result = NULL,
			* ptr = NULL,
			hints;
		int iResult = 0;
		WSADATA wsaData;

		// Initialize Winsock
		iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
		if (iResult != 0) {
			std::cout << "WSAStartup failed with error: " << iResult << std::endl;
			return false;
		}

		ZeroMemory(&hints, sizeof(hints));
		hints.ai_family = AF_UNSPEC;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;

		// Resolve the server address and port
		iResult = getaddrinfo(LAN, DEFAULT_PORT, &hints, &result);
		if (iResult != 0) {
			printf("getaddrinfo failed with error: %d\n", iResult);
			WSACleanup();
			return false;
		}

		// Attempt to connect to an address until one succeeds
		for (ptr = result; ptr != NULL; ptr = ptr->ai_next) 
		{

			// Create a SOCKET for connecting to server
			ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
				ptr->ai_protocol);
			if (ConnectSocket == INVALID_SOCKET) {
				printf("socket failed with error: %ld\n", WSAGetLastError());
				WSACleanup();
				return false;
			}

			// Connect to server.
			iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
			if (iResult == SOCKET_ERROR) {
				closesocket(ConnectSocket);
				ConnectSocket = INVALID_SOCKET;
				continue;
			}
			break;
		}

		freeaddrinfo(result);

		if (ConnectSocket == INVALID_SOCKET) {
			printf("Unable to connect to server!\n");
			WSACleanup();
			return false;
		}

		server = ConnectSocket;

		return true;
	}

	bool sendMessageToGraphics(char* msg)
	{
		//char ea[] = "SSS";
		char* chRequest = msg;	// Client -> Server
		DWORD cbBytesWritten, cbRequestBytes;

		// Send one message to the pipe.
		cbRequestBytes = sizeof(TCHAR) * (lstrlen((chRequest)) + 1);

		BOOL bResult = WriteFile(			// Write to the pipe.
			hPipe,						// Handle of the pipe
			chRequest,					// Message to be written
			cbRequestBytes,				// Number of bytes to write
			&cbBytesWritten,			// Number of bytes written
			NULL);						// Not overlapped 

		if (!bResult/*Failed*/ || cbRequestBytes != cbBytesWritten/*Failed*/)
		{
			_tprintf(_T("WriteFile failed w/err 0x%08lx\n"), GetLastError());
			return false;
		}

		_tprintf(_T("Sends %ld bytes; Message: \"%s\"\n"),
			cbBytesWritten, chRequest);

		return true;

	}

	bool sendMessageToServer(const std::string msg, SOCKET server)
	{
		int iResult = send(server, msg.c_str(), (int)strlen(msg.c_str()), 0);

		if (iResult == SOCKET_ERROR) {
			printf("send failed with error: %d\n", WSAGetLastError());
			closesocket(server);
			WSACleanup();
			return false;
		}

		return true;
	}

	std::string getMessageFromServer(SOCKET server)
	{
		char recvbuf[BUFFER_SIZE];

		int iResult = recv(server, recvbuf, BUFFER_SIZE, 0);

		if (iResult == SOCKET_ERROR) {
			printf("recieving failed with error: %d\n", WSAGetLastError());
			closesocket(server);
			WSACleanup();
			return "";
		}
		
		return recvbuf;
	}

	std::string getMessageFromGraphics()
	{
		DWORD cbBytesRead;
		DWORD cbReplyBytes;
		TCHAR chReply[BUFFER_SIZE];		// Server -> Client

		cbReplyBytes = sizeof(TCHAR) * BUFFER_SIZE;
		BOOL bResult = ReadFile(			// Read from the pipe.
			hPipe,					// Handle of the pipe
			chReply,				// Buffer to receive the reply
			cbReplyBytes,			// Size of buffer 
			&cbBytesRead,			// Number of bytes read 
			NULL);					// Not overlapped 

		if (!bResult && GetLastError() != ERROR_MORE_DATA)
		{
			_tprintf(_T("ReadFile failed w/err 0x%08lx\n"), GetLastError());
			return "";
		}

		_tprintf(_T("Receives %ld bytes; Message: \"%s\"\n"),
			cbBytesRead, chReply);
		std::string s = chReply;
		return s;

	}

	void close()
	{
		CloseHandle(hPipe);
	}

};
