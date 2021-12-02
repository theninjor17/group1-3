/*	Filename: main.cpp
Author: Nickolas Raghunath, Carter Folkes, Guneet Matharu
Date: 12:47am Nov 19 2021 ;-;
Details: Messaging system
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <windows.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "sound.h"
#include "Queues.h"
#include "Send.h"
#include "Assn1.h"
#include "RS232Comm.h"
#include "Header.h"


int main(int argc, char* argv[])
{
	extern short iBigBuf[];												// buffer
	extern long  lBigBufSize;											// total number of samples
	short* iBigBufNew = (short*)malloc(lBigBufSize * sizeof(short));		// buffer used for reading recorded sound from file
	

	char save{};
	char replay{};
	char c;			// used to flush extra input
	char mainmenu{}; //main menu
	char smenu{}; //audio menu
	char rmenu{}; //record menu
	char opmenu{};//options menu
	char amenu{};//txt menu
	char sendmenu{};// audio send menu
	char color{}; // color menu
	char die{}; // Diagnostic menu
	char tr{}; //text recive menu
	char ts{}; //text send menu
	char ar{}; //audio recive menu
	char COMValue[5];
	int recordingtime = RECORD_TIME * SAMPLES_SEC * 2;
	FILE* f;
	FILE* COMFile;
	char userBuffer[140];
	srand(time(0));
	int randomVal;
	randomVal = rand() % 1140;
	char selection;													// Tx or Rx (can run two instances of this program - double click the exe file)
	Header txHeader;												// Header transmitted 
	Header rxHeader;												// Header received
	void* rxPayload = NULL;											// Received payload (buffer) - void so it can be any data type
	DWORD bytesRead;												// Number of bytes received

	while (mainmenu != 'q')
	{
		system("cls");
		printf("\n _________________________________");
		printf("\n| Welcome. What can I do for you? |\n|                                 |");
		printf("\n|_________________________________|\n|                                 |");
		printf("\n| Audio Message menu ...........r |\n|                                 |");
		printf("\n| Text Message menu.............t |\n|                                 |");
		printf("\n| Options ......................o |\n|                                 |");
		printf("\n| quit .........................q |\n|                                 |");
		printf("\n|_________________________________|\n\n");
		if (scanf("%c", &mainmenu)) {};

		if (mainmenu == 'r')
		{
			while (smenu != 'b')
			{
				system("cls");
				printf("\n _________________________________");
				printf("\n|          Audio Message          |\n|                                 |");
				printf("\n|_________________________________|\n|                                 |");
				printf("\n| Send Message..................s |\n|                                 |");
				printf("\n| Back .........................b |\n|                                 |");
				printf("\n|_________________________________|\n\n");
				if (scanf("%c", &smenu)) {};

				if (smenu == 's')
				{
					while (sendmenu != 'b')
					{
						system("cls");
						printf("\n _________________________________");
						printf("\n|           Sending Menu          |\n|                                 |");
						printf("\n|_________________________________|\n|                                 |");
						printf("\n| Record new sound .............r |\n|                                 |");
						printf("\n| Send Recored sound ...........w |\n|                                 |");
						printf("\n| Show saved recording .........s |\n|                                 |");
						printf("\n| Back .........................b |\n|                                 |");
						printf("\n|_________________________________|\n\n");
						if (scanf("%c", &sendmenu)) {};

						if (sendmenu == 'r')
						{
							while (save != 'n')
							{
								
	
									
									Audio();
									break;
								

			

								// save audio recording  
								/*system("cls");
								printf("\n __________________________________________________");
								printf("\n|                                                  |");
								printf("\n|Would you like to save your audio recording? (y/n)|");
								printf("\n|__________________________________________________|\n");
								scanf_s("%c", &save, 1);
								while ((c = getchar()) != '\n' && c != EOF) {} // Flush other input
								Sleep(1000);

								if ((save == 'y') || (save == 'Y')) {
									/* Open input file 
									fopen_s(&f, "F:\\myfiles\\recording.dat", "wb");
									if (!f) {
										printf("unable to open %s\n", "F:\\myfiles\\recording.dat");
										//return 0;
									}
									system("cls");
									printf("\n _________________________");
									printf("\n|                         |");
									printf("\n|Writing to sound file ...|");
									printf("\n|_________________________|");
									fwrite(iBigBuf, sizeof(short), lBigBufSize, f);
									fclose(f);
									Sleep(1000);
									break;
								}*/
							}
						}
						else if (sendmenu == 's') {


							//variable initialization
							link p;

							//counter
							int i;

							//number of messages to grab and print
							int N = 2;

							//call InitQueue
							InitQueue();

							//for loop that creates a node for each message receieved up to "N" SID and adds each node to queue
							for (i = 0; i < N; i++) {

								//create node for SID
								p = (link)malloc(sizeof(Node));

								//number of node 
								p->Data.sid = i;

								//add node to queue
								AddToQueue(p);
								printf("sid added to Queue");
								Sleep(1000);
							}

							while (replay != 'n')
							{

								system("cls");
								printf("\n ________________________________________________________________________");
								printf("\n|                                                                        |");
								printf("\n|Would you like to replay the saved audio recording from the file? (y/n):| ");
								printf("\n|________________________________________________________________________|\n");
								scanf_s("%c", &replay, 1);
								while ((c = getchar()) != '\n' && c != EOF) {}								// Flush other input
								if ((replay == 'y') || (replay == 'Y')) {
									/* Open input file */
									fopen_s(&f, "F:\\myfiles\\recording.dat", "rb");
									if (!f) {
										printf("unable to open %s\n", "F:\\myfiles\\recording.dat");
										//return 0;
									}
									printf("Reading from sound file ...\n");
									fread(iBigBufNew, sizeof(short), lBigBufSize, f);				// Record to new buffer iBigBufNew
									fclose(f);
									InitializePlayback();
									printf("\n _____________________________________");
									printf("\n|                                     |");
									printf("\n|Playing recording from saved file ...|");
									printf("\n|_____________________________________|");
									PlayBuffer(iBigBufNew, lBigBufSize);
									ClosePlayback();
									break;
								}
							}
						}
						else if (sendmenu == 'w') {
							while (smenu != 'b') {
								system("cls");
								printf("\n _________________________________");
								printf("\n|           Sending Menu          |\n|                                 |");
								printf("\n|_________________________________|\n|                                 |");
								printf("\n| Veiw Contacts ................r |\n|                                 |");
								printf("\n| reply to last message ........s |\n|                                 |");
								printf("\n| Back .........................b |\n|                                 |");
								printf("\n|_________________________________|\n\n");
								if (scanf("%c", &smenu)) {};


							}
						}
					}
				}
			}
			 
		}
		else if (mainmenu == 'o')
		{


			while (opmenu != 'b')
			{
				
				system("cls");
				printf("\n _________________________________");
				printf("\n|           Option Menu           |\n|                                 |");
				printf("\n|_________________________________|\n|                                 |");
				printf("\n| Colour .......................r |\n|                                 |");
				printf("\n| recording time................s |\n|                                 |");
				printf("\n| Clear Messages................c |\n|                                 |");
				printf("\n| Diagnostic....................d |\n|                                 |");
				printf("\n| Back .........................b |\n|                                 |");
				printf("\n|_________________________________|\n\n");
				if (scanf("%c", &opmenu)) {};

				if (opmenu == 'r')
				{


					while (color != 'b')
					{
						system("cls");
						printf("\n _________________________________");
						printf("\n|            Color Menu           |\n|                                 |");
						printf("\n|_________________________________|\n|                                 |");
						printf("\n| Option 1 .....................w |\n|                                 |");
						printf("\n| Option 2 .....................a |\n|                                 |");
						printf("\n| Option 3 .....................s |\n|                                 |");
						printf("\n| Option 4 ,....................d |\n|                                 |");
						printf("\n| Back .........................b |\n|                                 |");
						printf("\n|_________________________________|\n\n");
						if (scanf("%c", &color)) {};

						if (color == 'w')
						{
							HANDLE Con;
							Con = GetStdHandle(STD_OUTPUT_HANDLE);
							SetConsoleTextAttribute(Con, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);
						}

						else if (color == 'a')
						{
							HANDLE Con;
							Con = GetStdHandle(STD_OUTPUT_HANDLE);
							SetConsoleTextAttribute(Con, BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_INTENSITY);
						}
						else if (color == 's')
						{
							HANDLE Con;
							Con = GetStdHandle(STD_OUTPUT_HANDLE);
							SetConsoleTextAttribute(Con, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
						}
						else if (color == 'd')
						{
							HANDLE Con;
							Con = GetStdHandle(STD_OUTPUT_HANDLE);
							SetConsoleTextAttribute(Con, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
						}
							

						
					}
				}

				if (opmenu == 'd')
				{
					while (die != 'b') {
						system("cls");
						printf("\n _________________________________");
						printf("\n|         Diagnostic Menu         |\n|                                 |");
						printf("\n|_________________________________|\n|                                 |");
						printf("\n| Test send (text) .............r |\n|                                 |");
						printf("\n| Test Queue ...................s |\n|                                 |");
						printf("\n| Change COM ...................c |\n|                                 |");
						printf("\n| Test send receive (text) .....g |\n|                                 |");
						printf("\n| Test Fortune .................f |\n|                                 |");
						printf("\n| Back .........................b |\n|                                 |");
						printf("\n|_________________________________|\n\n");
						if (scanf("%c", &die)) {};

						if (die == 'r') {
							testsend();
						}

						else if (die == 'g') {

							TxRx();
						}

						else if (die == 'f') {
							GetMessageFromFile(userBuffer, randomVal);
						}
						
						else if (die == 's') {

							//variable initialization
							link x, y;

							//counter
							int count,num,buffer;
							
							printf("\nHow many SIDs would you like to put into the Queue?\n");

							//number of messages to grab and print
							while (scanf("%d", &num) != 1) {
								printf("\nPlease enter an integer!");
								while (getchar() != '\n');
							}

							//call InitQueue
							InitQueue();
							printf("\nFilling Queue, please enter integers when prompted.");

							//for loop that creates a node for each message receieved up to count SID and adds each node to queue
							for (count = 0; count < num; count++) {

								//create node for SID
								x = (link)malloc(sizeof(Node));
								printf("\nItem %d: ", count);
								if (scanf("%d", &buffer)) {};

								//number of node 
								x->Data.sid = buffer;

								//add node to queue
								AddToQueue(x);
								printf("sid added to Queue");
								Sleep(1000);
							}
							system("cls");
							printf("\nDequeing queue");
							while (!IsQueueEmpty())
							{
								y = DeQueue();
								printf("\n The message of Node is: %d", y->Data.sid);
								Sleep(1000);
							}

							system("cls");
						}

						else if (die == 'c') {
							COMFile = fopen("test.txt", "w");
							if (COMFile == NULL) {
								printf("Can't find file\n");
							}
							else {
								printf("What would you like your COM Port to be?");
								scanf("%s", &COMValue);
								printf("Your COM Port is now %s", COMValue);
								fwrite(COMValue, 1, strlen(COMValue), COMFile);
								Sleep(500);
								fclose(COMFile);
							}
						}
					}
				}

			}


		}
		else if (mainmenu == 't')
			{


				while (amenu != 'b')
				{
					
					system("cls");
					printf("\n _________________________________");
					printf("\n|           Text Message          |\n|                                 |");
					printf("\n|_________________________________|\n|                                 |");
					printf("\n| Send Message..................s |\n|                                 |");
					printf("\n| Show Received messages........r |\n|                                 |");
					printf("\n| Back .........................b |\n|                                 |");
					printf("\n|_________________________________|\n\n");
					if (scanf("%c", &amenu)) {};

					if (amenu == 's')
					{
						while (ts != 'b')
						{
							system("cls");
							printf("\n _________________________________");
							printf("\n|         Sending Message         |\n|                                 |");
							printf("\n|_________________________________|\n|                                 |");
							printf("\n| Contact list .................s |\n|                                 |");
							printf("\n| Reply to last messages .......r |\n|                                 |");
							printf("\n| Send a FortuneCookie .........p |\n|                                 |");
							printf("\n| Back .........................b |\n|                                 |");
							printf("\n|_________________________________|\n\n");
							if (scanf("%c", &ts)) {};

							if (ts == 'p') {
								//TRANSMIT FORTUNE COOKIE
								//system("cls");
								printf("\nCall transmit");
								transmittype();
								printf("\nTransmit call success");
							}
						}
					}

					else if (amenu == 'r')
					{
						while (tr != 'b')
						{
							system("cls");
							printf("\n _________________________________");
							printf("\n|          Received Message       |\n|                                 |");
							printf("\n|_________________________________|\n|                                 |");
							printf("\n| By contact ...................s |\n|                                 |");
							printf("\n| By Time ......................r |\n|                                 |");
							printf("\n| Favorite .....................r |\n|                                 |");
							printf("\n| latest Received messages......r |\n|                                 |");
							printf("\n| Back .........................b |\n|                                 |");
							printf("\n|_________________________________|\n\n");
							if (scanf("%c", &tr)) {};

						}
					}

				}


		}
	
	}
}
