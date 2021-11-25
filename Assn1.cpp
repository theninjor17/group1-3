/*  Data Structures and Algorithms Assignment 1
    By: Nickolas Raghunath, Carter Folkes and Guneet Matharu

    We hope you enjoy your (possibly cut off at 140 chars)
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <Windows.h>

//GetMessage Function
int GetMessageFromFile (char szBuff[], int randomVal){

    //Variables
    FILE *fp;
    szBuff[140];
    char FileName[] = "FortuneCookies.txt";
    int filePosition=0, numOfQuotes=0, ftellVar=0, i=0, j=0, k=0;
    int quoteStartLoc[1141] = { 0 };
    char tempBuf[140];
    char firstChar=tempBuf[0];
    randomVal;

    //Open file
    fp = fopen(FileName, "r");
    printf("Your randomVal = %d\n",randomVal);
    Sleep(1000);

    //If file doesn't exist, print error
    if (fp == NULL){
        printf("Could not find and open file named %s :'(\n", FileName);
        return (-1);
    }

    //Go to location of first quote
    //fseek(fp, 4, 0);

    //While not end of quotes
    while (ftellVar!=251001){

        //Get line
        fgets(szBuff, 140, fp);
            
        //If a delimiter line, +4 is the beginning of a quote.
        if ((strcmp(szBuff,"%%\n")==0|| strcmp(szBuff, "%% \n") == 0)) {

            //Put that position in the indexing array
            quoteStartLoc[i] = filePosition+4;
            i++;
        }

        //If not a delimiter line, go to next line
        else{
            filePosition = ftell(fp);
        }
        

        //Go to next quote (end of last quote but not delim line)
        ftellVar = ftell(fp);
        fseek(fp, ftellVar,0);
    }

    //^That's all back end, this is front end v
    fseek(fp, quoteStartLoc[randomVal], 0); //<- At beginning of "random" quote via index value
    printf("QuoteStartLoc=%d\n",quoteStartLoc[randomVal]);
    Sleep(1000);

    //Get line
    while (fgets(szBuff, 140, fp)) {

        //If end of quote, break
        if ((strcmp(szBuff, "%%\n") == 0 || strcmp(szBuff, "%% \n") == 0)) {
            break;
        }
        //If not end of quote, print the line as a string
        else {
            printf("%s", szBuff);
        }
    }
    Sleep(2000);

    //Close file
    fclose(fp); 

    return 0;
}