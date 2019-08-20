/*
Written by Daniel Keele
*/

#include <stdio.h>

int PrintNextSixteenHexBytes(FILE* file);
void PrintNextSixteenASCIIBytes(FILE* file);
void PrintCurrentAddress(int lineNumber);
void PrintNextSixteenBinaryBytes(FILE* file);

int main(int argumentCount, char** arguments)
{
        //variables
        int necessaryArguments = 2;

        //error handling
        if (argumentCount < necessaryArguments)
        {
                printf("Usage: %s <filename>\n", arguments[0]);
                return 1;
        }

        FILE* byteReaderFile = fopen(arguments[1], "r");
        FILE* asciiReaderFile = fopen(arguments[1], "r");

        if (byteReaderFile == 0 || asciiReaderFile == 0)
        {
                printf("Could not open %s!\n", arguments[1]);
                return 2; 
        }

        int lineNumber = 0;
        int finished = 0;

        while (finished == 0)
        {
                PrintCurrentAddress(lineNumber);

                finished = PrintNextSixteenHexBytes(byteReaderFile);

                PrintNextSixteenASCIIBytes(asciiReaderFile);
                printf("\n");

                lineNumber++;
        }

        fclose(byteReaderFile);
        fclose(asciiReaderFile);

        return 0;
}

int PrintNextSixteenHexBytes(FILE* file)
{
        int spaceCounter = 0;
        int counter = 0;
        unsigned char currentByte = 0;
        int finished = 0;

        while (counter < 16)
        {
                if (fscanf(file, "%c", &currentByte) == 1)
                {
                        if (spaceCounter == 1)
                        {
                                printf("%02x ", currentByte);
                                spaceCounter = 0;
                        }
                        else
                        {
                                printf("%02x", currentByte);
                                spaceCounter++;
                        }
                }
                else
                {
                        finished = 1;

                        if (spaceCounter == 1)
                        {
                                printf("   ");
                                spaceCounter = 0;
                        }
                        else
                        {
                                printf("  ");
                                spaceCounter++;
                        }   
                }
                
                counter++;
        }

        return finished;
}

void PrintNextSixteenASCIIBytes(FILE* file)
{
        int isEndOfFile = 0;
        char currentByte = 0;
        int counter = 0;

        while (isEndOfFile != 1 && counter < 16)
        {
                int result = fscanf(file, "%c", &currentByte);

                //it's printing the new line character. Check for valid character using ascii range
                if (result == 1)
                {
                        if (currentByte >= 32 && currentByte <= 126)
                        {
                                printf("%c", currentByte);
                        }
                        else 
                        {
                                printf(".");
                        }
                }
                else if (result == EOF)
                {
                        isEndOfFile = 1;
                }

                counter++;
        }
}

void PrintCurrentAddress(int lineNumber)
{
        //line numbers in hex
        printf("%07x0: ", lineNumber);
};