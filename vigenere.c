#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*
vigenere.c
Johnny Huang
CS448
Simple C program that takes in a text and key to encrypt/decrypt. -e switch for encryption, -d for decryption. Usage example: ./vigenere <-SWITCH> <TEXT> <KEY>
*/

int main(int argc, char* argv[])
{	
	int option = 0;

	//error and option-checking
	if(argv[1] == NULL)
	{
		printf("%s\n","Usages:");
		printf("%s\n","Encryption: ./vigenere -e [TEXTTOENCODE] [KEY]");
		printf("%s\n","Decryption: ./vigenere -d [TEXTTODECODE] [KEY]");
		return 1;
	}
	else if(argv[2] == NULL)
	{
		printf("%s\n","ERROR: No text supplied; exiting...");
		return 1;
	}
	else if(argv[3] == NULL)
	{
		printf("%s\n","ERROR: No key supplied; exiting...");
		return 1;
	}
	else if(strcmp(argv[1], "-e")==0)
	{
		printf("%s\n\n","Encryption selected");
	}
	else if(strcmp(argv[1], "-d")==0)
	{
		printf("%s\n\n","Decryption selected");
		option = 1;
	}
	else
	{
		printf("%s\n","ERROR: Unknown error; exiting...");
		return 1;
	}
	
	//initial memory alloc. for vigenere table
	char** vigtable = malloc(26 * sizeof(char*));
	
	//construct vigenere table
	for(int i = 0 ; i < 26; i++)
	{
		vigtable[i] = malloc(26 * sizeof(char));
		for(int j = 0 ; j < 26; j++)
		{
			if(97+i+j > 122)
			{
				vigtable[i][j] = ((97+i+j)%123) + 97;
			}
			else
			{
				vigtable[i][j] = (97+i+j)%123;
			}
			//printf("%c",vigtable[i][j]);
		}
		//printf("\n");
	}
	
	//check if all characters are alphabet
	for(int i = 0 ; i < strlen(argv[2]) ; i++)
	{
		//DEBUG: print out alphabet value in decimal
		//printf("%d\n",argv[2][i]);
		if(!(argv[2][i] >= 65 || argv[2][i] <= 90 || argv[2][i] >= 97 || argv[2][i] <= 122))
		{
		printf("%s\n","Text not fully alphabetic; exiting...");
		return 1;
		}
	}
	for(int i = 0 ; i < strlen(argv[3]) ; i++)
	{
		//DEBUG: print out alphabet value in decimal
		//printf("%d\n",argv[3][i]);
		if(!(argv[3][i] >= 65 || argv[3][i] <= 90 || argv[3][i] >= 97 || argv[3][i] <= 122))
		{
		printf("%s\n","Key not fully alphabetic; exiting...");
		return 1;
		}
	}
	
	//encrypting:
	if(option == 0)
	{
		//prepare skeleton for string to return
		char* toReturn = malloc(strlen(argv[2]) * sizeof(char));
		
		//keeps track of position of key
		int keypos = 0;
		
		//goes thru entire length of plaintext
		for(int x = 0 ; x < strlen(argv[2]) ; x++)
		{
			//if character is upper: do extra work
			if(argv[2][x] <= 90)
			{
				toReturn[x] = toupper(vigtable[tolower(argv[2][x])-97][tolower(argv[3][keypos])-97]);
			}
			else
			{
				toReturn[x] = vigtable[(argv[2][x])-97][tolower(argv[3][keypos])-97];
			}
			
			//checks if key is null-terminated at this point. if not, advance. else, reset
			if(argv[3][keypos+1] == '\0')
			{
				keypos = 0;
			}
			else
			{
				keypos++;
			}
		}
		
		toReturn[strlen(argv[2])] = '\0';
		printf("%s\n","Results:");
		printf("Plaintext: %s\n",argv[2]);
		printf("Key: %s\n",argv[3]);
		printf("Ciphertext: %s\n",toReturn);
		
		//DEBUG: free vigenere table
	for(int i = 0 ; i < 26; i++)
	{
		free(vigtable[i]);
	}
	free(vigtable);
	
		return 0;
	}
	
	//decrypting:
	else
	{
		//skeleton
		char* toReturn = malloc(strlen(argv[2]) * sizeof(char));
		
		//key position
		int keypos = 0;
		
		//for entire length of ciphertext
		for(int y = 0 ; y < strlen(argv[2]) ; y++)
		{
			//if character is upper: do extra work
			if(argv[2][y] <= 90)
			{
				//use row by key, search entire column for matching with ciphertext, get index
				for(int j = 0 ; j < 26 ; j++)
				{
					if(vigtable[tolower(argv[3][keypos])-97][j] == tolower(argv[2][y]))
					{
						toReturn[y] = toupper(vigtable[0][j]);
						break;
					}
				}
			}
			else
			{
				for(int j = 0 ; j < 26 ; j++)
				{
					if(vigtable[tolower(argv[3][keypos])-97][j] == argv[2][y])
					{
						toReturn[y] = vigtable[0][j];
						break;
					}
				}
			}
			
			//null-termination check
			if(argv[3][keypos+1] == '\0')
			{
				keypos = 0;
			}
			else
			{
				keypos++;
			}
		}
		
		toReturn[strlen(argv[2])] = '\0';
		printf("%s\n","Results:");
		printf("Ciphertext: %s\n",argv[2]);
		printf("Key: %s\n",argv[3]);
		printf("Plaintext: %s\n",toReturn);
		
		//DEBUG: free vigenere table
	for(int i = 0 ; i < 26; i++)
	{
		free(vigtable[i]);
	}
	free(vigtable);
		
		return 0;
	}
	
	//should never occur
	return 1;
}