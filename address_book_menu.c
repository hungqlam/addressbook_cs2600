#include <stdio.h>
//#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "address_book_fops.h"
//#include "abk_log.h"
#include "address_book_menu.h"
#include "address_book.h"

int get_option(int type, const char *msg)
{
	/*
	 * Mutilfuction user intractions like
	 * Just an enter key detection
	 * Read an number OR
	 * Read a charcter
	 */ 
	if (type == CHAR){
		char option;
		printf("%s", msg); 		//First print the message passed to us
		scanf("%c", &option);	//Then capture a character
		return option;
	}

	if (type == NUM){
		int option;
		printf("%s", msg);
		scanf("%i", &option);
		return option;
	}

	if (type == NONE){ 			//Not sure how to interpret a NONE option
		printf("%s", msg);
		return -1;
	}

	return -1;

	/* Fill the code to add above functionality */
}

Status save_prompt(AddressBook *address_book)
{
	char option;

	do
	{
		main_menu();

		option = get_option(CHAR, "\rEnter 'N' to Ignore and 'Y' to Save: ");

		if (option == 'Y')
		{	
			save_file(address_book);
			printf("Exiting. Data saved in %s\n", DEFAULT_FILE);

			break;
		}
	} while (option != 'N');

	free(address_book->list);

	return e_success;
}

Status list_contacts(AddressBook *address_book, const char *title, int *index, const char *msg, Modes mode)
{
	/* 
	 * Add code to list all the contacts availabe in address_book.csv file
	 * Should be menu based
	 * The menu provide navigation option if the entries increase the page size
	 */ 

	return e_success;
}

void menu_header(const char *str)
{
	fflush(stdout);

	//system("cls"); //changed clear to cls

	printf("#######  Address Book  #######\n");
	if (!strcmp(str, "\0"))	// if(str != '\0')
	{
		printf("#######  %s\n", str);
	}
}

void main_menu(void)
{
	menu_header("Features:\n");

	printf("0. Exit\n");
	printf("1. Add Contact\n");
	printf("2. Search Contact\n");
	printf("3. Edit Contact\n");
	printf("4. Delete Contact\n");
	printf("5. List Contacts\n");
	printf("6. Save\n");
	printf("\n");
	printf("Please select an option: ");
}

Status menu(AddressBook *address_book)
{
	ContactInfo backup;
	Status ret;
	int option;

	do
	{
		main_menu();

		option = get_option(NUM, "");

		if ((address_book-> count == 0) && (option != e_add_contact))
		{
			//This doesn't appear to be functioning with just search function implemented
			get_option(NONE, "No entries found!!. Would you like to add? Use Add Contacts");

			continue;
		}

		switch (option)
		{
			case e_add_contact:
				/* Add your implementation to call add_contacts function here */
				break;
			case e_search_contact:
				search_contact(address_book);
				break;
			case e_edit_contact:
				edit_contact(address_book);
				break;
			case e_delete_contact:
				delete_contact(address_book);
				break;
			case e_list_contacts:
				break;
				/* Add your implementation to call list_contacts function here */
			case e_save:
				save_file(address_book);
				break;
			case e_exit:
				break;
		}
	} while (option != e_exit);

	return e_success;
}

Status add_contacts(AddressBook *address_book)
{
	/* Add the functionality for adding contacts here */
}

Status search(const char *str, AddressBook *address_book, int loop_count, int field, const char *msg, Modes mode)
{
	/* Add the functionality for adding contacts here */
	//This will be the generic search type. We take in a string, ptr to address_book, how far to search,
			//what we are searching for (as in name, email, phone), a message to print to console, and mode

	//First we should determine what we are searching for, name, phone number, or email address
	
	//Second we should call the appropriate search function

	//Finally we should iterate through the search function 
	//Smart search
	
	//Dumb search
	int strdifference = -1;
	char search[32];
	char *searchPtr = (char *)address_book->list; // Start ptr at beginning of list
	int nameSize = sizeof(address_book->list->name);
	int phoneArraySize = sizeof(address_book->list->phone_numbers);
	int emailArraySize = sizeof(address_book->list->email_addresses);

	strcpy(search, str);
	for (int i=0; i<=loop_count; i++){
		

		switch (field){
			case 1:{ //By name
				strdifference = strcmp(search, searchPtr); //We are already looking at first name in list
				if (strdifference == 0) {
					printf("NAME FOUND!\n");
					break;
				}
				searchPtr += sizeof(ContactInfo); //Jump to next contact
				break;
			}
			case 2:{ //By phone number
				searchPtr += sizeof(address_book->list->name); //Goto 1st phone number in contact
				for (int phoneNum=0; phoneNum < PHONE_NUMBER_COUNT; phoneNum++){ //This loop searches all of contact n's phone numbers
					strdifference = strcmp(str, searchPtr); //Remember strcmp compares up to null character, so we wont go over entire array
					if (strdifference == 0) {
						printf("PHONE FOUND!\n");
						break;
					}
					searchPtr += sizeof(address_book->list->phone_numbers[0]); //Jump to next phone number
				}
				//searchPtr is now at emailaddress 1, we should go back a few
				searchPtr -= phoneArraySize + nameSize; //Go back to beginning of phone numbers
				searchPtr += sizeof(ContactInfo); //Jump forward one contact
				break;
			}
			case 3:{ //By email address
				//Jump to beginning of email addresses
				searchPtr += nameSize + phoneArraySize;

				for (int emailAdd=0; emailAdd < EMAIL_ID_COUNT; emailAdd++){
					strdifference = strcmp(str, searchPtr);
					if (strdifference == 0) {
						printf("EMAIL FOUND!\n");
						break;
					}
					searchPtr += sizeof(address_book->list->email_addresses[0]);
				}
				searchPtr -= emailArraySize + phoneArraySize + nameSize;
				searchPtr += sizeof(ContactInfo);
				break;
			}
			case 4:{ //By serial number
				//Jump to beginning of serial number
				searchPtr += nameSize + phoneArraySize + emailArraySize;
				int si_no = strtol(str, NULL, 10);
				if (si_no - *searchPtr == 0) strdifference = 0;
				//strdifference = *searchPtr == strtol(str, NULL, 10); //This is really hacky (sorry)
				if (strdifference == 0) {
					printf("Serial Number Found!\n");
					break;
				}
				searchPtr += sizeof(address_book->list->si_no);
				break;
			}
		}
		//Search names
		//searchPtr += sizeof(address_book->list->name); //Move ptr to beginning of phone_numbers
		//Search phone numbers
		//searchPtr += sizeof(address_book->list->phone_numbers[0]); // Move ahead one phone number
		//Search email addresses
		//Search serial number
		//searchPtr += sizeof(address_book->list->si_no); //Jump to next thing
		if (strdifference == 0){ //If we found a match
			//print out contact
			searchPtr = (char *)address_book->list; //Goto beginning of list
			if (i >= 1){
				searchPtr += i * (sizeof(ContactInfo));
			}
			printf("###### Address Book ######\n");
			printf("###### Search Result:\n\n");
			printf("==========================================================================\n");
			printf(": S.No : Name                           : Phone Number                   : Email Address				:\n");
			printf("==========================================================================\n");
			printf(": %i    : %s                             : %s                             : %s                           :\n",
				*(searchPtr + nameSize + phoneArraySize + emailArraySize), 
				searchPtr, 
				searchPtr + nameSize,
				searchPtr + nameSize + phoneArraySize);
			for (int j=1; j < PHONE_NUMBER_COUNT; j++){
				printf(":      :                               : %s                             : %s                           :\n",
				searchPtr + nameSize + (j*sizeof(address_book->list->phone_numbers[0])),
				searchPtr + nameSize + phoneArraySize + (j*sizeof(address_book->list->email_addresses[0])));

			}
			printf("==========================================================================\n");
			return e_success;
		}
	}
	//Failed to find something, spit out error maybe here or for each case

}

Status search_contact(AddressBook *address_book)
{
	/* Add the functionality for search contacts here */
	//This is the menu function, and will call search above
	//Name
	//Number
	//email
	int option = -1;
	char str[31];
	do {
		printf("####### Address Book #######\n");
		printf("####### Search Contact by:\n");
		printf("0. Back\n");
		printf("1. Name\n");
		printf("2. Phone number\n");
		printf("3. Email ID\n");
		printf("4. Serial number\n\n");
		option = get_option(NUM, "Please select an option: ");
		}
		while (option == -1);
	
	fflush(stdin);
	switch (option){
		case 0: return e_exit;
		case 1:{
			printf("Enter the name: ");
			scanf("%[^\n]s", str);
			//fgets(str, NAME_LEN, stdin);
			Status ret = search(str, address_book, address_book->count, option, "", e_search);
			return ret;
		}
		case 2:{
			printf("Enter a phone number: ");
			scanf("%[^\n]s", str);
			Status ret = search(str, address_book, address_book->count, option, "", e_search);
			return ret;
		}
		case 3:{
			printf("Enter an email address: ");
			scanf("%[^\n]s", str);
			Status ret = search(str, address_book, address_book->count, option, "", e_search);
			return ret;
		}
		case 4:{
			printf("Enter a serial number: ");
			scanf("%[^\n]s", str);
			Status ret = search(str, address_book, address_book->count, option, "", e_search);
			return ret;
		}
		default:{
			return e_no_match;
		}
	}
}

Status edit_contact(AddressBook *address_book)
{
	/* Add the functionality for edit contacts here */
}

Status delete_contact(AddressBook *address_book)
{
	/* Add the functionality for delete contacts here */
}
