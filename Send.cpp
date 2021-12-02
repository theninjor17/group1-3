/* Send.cpp - Client for the Tx Program */

#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>    
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "RS232Comm.h"
#include "rle.h"
#include "Header.h"
#include "sound.h"
#include "Assn1.h"

const int BUFSIZE = 140;							// Buffer size
wchar_t COMPORT_Rx[] = L"COM7";						// COM port used for Rx 
wchar_t COMPORT_Tx[] = L"COM6";						// COM port used for Tx 
HANDLE hComRx;										// Pointer to the selected COM port (Receiver)
HANDLE hComTx;										// Pointer to the selected COM port (Transmitter)
int nComRate = 9600;								// Baud (Bit) rate in bits/second 
int nComBits = 8;									// Number of bits per frame
COMMTIMEOUTS timeout;
char selection;													// Tx or Rx (can run two instances of this program - double click the exe file)
Header txHeader;												// Header transmitted 
Header rxHeader;												// Header received
void* rxPayload = NULL;											// Received payload (buffer) - void so it can be any data type
DWORD bytesRead;												// Number of bytes received

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
	printf("COM Port: %ws has been initialized\n", COMPORT_Tx);
	Sleep(1000);

	// Transmit side 
	unsigned char msgOut[] = "Hi there person";							// Sent message	
	unsigned char compmsgOut[197];
	int size;

	printf("Message before compression: %s\n\n",msgOut);
	size = RLE_Compress(msgOut, compmsgOut, sizeof(msgOut));
	printf("Message after compression: %s\n\n",compmsgOut);
	printf("The size of your message is: %d",size);
	

	outputToPort(&hComTx, compmsgOut, size);			// Send string to port - include space for '\0' termination
	Sleep(500);													// Allow time for signal propagation on cable 
	
	// Tear down both sides of the comm link
	purgePort(&hComTx);											// Purge the Tx port
	CloseHandle(hComTx);										// Close the handle to Tx port 
	
	system("pause");
}

void transmittype() {


		//Variables
		static char COMValue[5];											//Var to get COM value from file
		static FILE* COMFile;												//FP to get COM Value from
		static const int BUFSIZE = 140;								// Buffer size
		wchar_t COMPORT_Tx[5];										// COM port used for Rx
		static HANDLE hComTx;										// Pointer to the selected COM port (Receiver)
		int nComRate = 9600;										// Baud (Bit) rate in bits/second 
		int nComBits = 8;											// Number of bits per frame
		static COMMTIMEOUTS timeout;									// A commtimeout struct variable
		
		Header txHeader;												// Header transmitted 
		int randVal;
		randVal = rand() % 1140;
		char userBuf[141];


		COMFile = fopen("test.txt", "r");							//Open file to hold value

		printf("\nGoing to check COMports");
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

		// Payload (sample type is text)
		char txPayload[] = "Hello from this side.";
		//GetMessageFromFile(userBuf, randVal); 	// Payload is a text message in this example but could be any data	
		//strcpy(txPayload, userBuf);
		// Header (sample data type is text but this should work with audio and images as well)
		txHeader.sid = 1;
		txHeader.rid = 2;
		txHeader.payloadSize = strlen(txPayload) + 1;				// Flexible payload size - Send size of payload inside header (payload can be anything) and enough memory will be malloc'd in the receive function
		txHeader.compression = 0;									// None
		txHeader.encryption = 0;									// None
		txHeader.payLoadType = 0;									// Text = 0, Audio = 1

		printf("\nMessage to be sent is:%s", txPayload);
		Sleep(2000);

		transmit(&txHeader, txPayload, &hComTx, COMPORT_Tx, nComRate, nComBits, timeout);  // Transmit header and payload
	




}