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
	address_book->fp = fopen(DEFAULT_FILE, "r");
	if (address_book->fp == NULL){
		//throw error
		printf("FILE NOT FOUND");
		//perror("\nFILE NOT FOUND");
		fclose(address_book->fp);
		ret = -1;
		//return e_fail;
	}
	fclose(address_book->fp);

	//alternatively
	if (!access(DEFAULT_FILE, F_OK))
		printf("FILE NOT FOUND");//perror("\nFILE NOT FOUND");

	if (ret == 0) // <--- What is ret?
	{
		/* 
		 * Do the neccessary step to open the file
		 * Do error handling
		 */ 
	}
	else
	{
		/* Create a file for adding entries */
		printf("Creating new address book file, %s\n", DEFAULT_FILE);
		address_book->fp = fopen(DEFAULT_FILE, "a");
		fclose(address_book->fp);
	}

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
