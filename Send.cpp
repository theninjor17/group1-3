/* Send.cpp - Client for the Tx Program */

#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>    
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "RS232Comm.h"

void testsend(){

	//Variables
	char COMValue[5];											//Var to get COM value from file
	FILE* COMFile;												//FP to get COM Value from
	static const int BUFSIZE = 140;								// Buffer size
	wchar_t COMPORT_Tx[5];										// COM port used for Rx
	static HANDLE hComTx;										// Pointer to the selected COM port (Receiver)
	int nComRate = 9600;										// Baud (Bit) rate in bits/second 
	int nComBits = 8;											// Number of bits per frame
	COMMTIMEOUTS timeout{};								// A commtimeout struct variable


	COMFile = fopen("test.txt", "r");							//Open file to hold value

	if (COMFile) {

		fseek(COMFile, 0, 0);									//Go to begin of file
		fread(&COMValue, sizeof(char), 3, COMFile);				//Get first 3 chars
		fseek(COMFile, 3, 0);									//Go to after 3 chars
		fread(&COMValue[3], sizeof(int), 1, COMFile);			//Get first int
		COMValue[4] = '\0';										//Add a null temrinator b/s string

		printf("Your COM Port is %s", COMValue);
		Sleep(500);
		fclose(COMFile);										//Close file
	}
	
	mbstowcs(COMPORT_Tx, COMValue, 5);							//Convert char array to wchar_t array

	initPort(&hComTx, COMPORT_Tx, nComRate, nComBits, timeout);	// Initialize the Tx port
	printf("COM Port: %ws has been initialized", COMPORT_Tx);
	Sleep(1000);

	// Transmit side 
	char msgOut[] = "Hi there person";							// Sent message	
	outputToPort(&hComTx, msgOut, strlen(msgOut)+1);			// Send string to port - include space for '\0' termination
	Sleep(500);													// Allow time for signal propagation on cable 
	
	// Tear down both sides of the comm link
	purgePort(&hComTx);											// Purge the Tx port
	CloseHandle(hComTx);										// Close the handle to Tx port 
	
	system("pause");
}