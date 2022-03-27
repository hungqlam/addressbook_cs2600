#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <ctype.h>

#include "address_book.h"

Status load_file(AddressBook *address_book)
{
	int ret;

	/* 
	 * Check for file existance
	 */
	//At this point, we are assuming the address_book is empty and thus fp is NULL
	//So really we don't need to do this stuff with address_book->fp
	/*FILE *fileptr = fopen(DEFAULT_FILE, "r");
	if (fileptr == NULL){
		fclose(fileptr); //Close file, maybe return a status
	}*/

	address_book->fp = fopen(DEFAULT_FILE, "r"); //This works because we dont need to make a new ptr
	if (address_book->fp == NULL){ //Have we found the file?
		//throw error
		printf("FILE NOT FOUND");
		ret = e_fail;
		fclose(address_book->fp);
	}

	//alternatively
	/*if (!access(DEFAULT_FILE, F_OK))
		printf("FILE NOT FOUND");//perror("\nFILE NOT FOUND");*/

	if (ret == 0) // File has been detected, -10 would mean fail
	{
		/* 
		 * Do the neccessary step to open the file
		 * Do error handling
		 */ 
		int numberOfLines = 0;
		char buffer[353];
		//Because the file is still open we shall simply begin copying it into our list
		//Determine how large the file is while checking for errors
		while (fgets(buffer, 353, address_book->fp)){
			numberOfLines++;
		}
		printf("%i lines read from file.\n", numberOfLines);
		//Make an array to accomodate all lines
		ContactInfo contactinfo[numberOfLines];
		for (int line = 0; line < numberOfLines; line++){
			//Put all names
			//Put all phone numbers
			//Put all email addresses
			break; //DELETE ME
		}

		address_book->list = contactinfo;
		fclose(address_book->fp);
		
	}
	else
	{
		/* Create a file for adding entries */
		printf("Creating new address book file, %s\n", DEFAULT_FILE);
		address_book->fp = fopen(DEFAULT_FILE, "a");
		fclose(address_book->fp);
	}
	fclose(address_book->fp);
	return e_success;
}

Status save_file(AddressBook *address_book)
{
	/*
	 * Write contacts back to file.
	 * Re write the complete file currently
	 */ 
	address_book->fp = fopen(DEFAULT_FILE, "w");

	if (address_book->fp == NULL)
	{
		return e_fail;
	}

	/* 
	 * Add the logic to save the file
	 * Make sure to do error handling
	 */ 
	//Print names
	fprintf(address_book->fp, "%s,", address_book->list->name);
	//Print phone numbers upto max allowable phone numbers
	int numbers = sizeof(address_book->list->phone_numbers) / NUMBER_LEN;
	for (int i=0; i < numbers; i++){
		fprintf(address_book->fp, "%s ", address_book->list->phone_numbers[i]);
	}
	fprintf(address_book->fp, ",");
	//print emails upto max allowable emails
	int emails = sizeof(address_book->list->email_addresses) / EMAIL_ID_COUNT;
	for (int i=0; i < emails; i++){
		fprintf(address_book->fp, "%s ", address_book->list->email_addresses[i]);
	}
	fprintf(address_book->fp, ",");
	//print id?

	fclose(address_book->fp);

	return e_success;
}
