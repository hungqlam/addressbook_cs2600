#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "address_book_fops.h"
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
		fflush(stdin);
		return option;
	}

	if (type == NUM){
		int option;
		printf("%s", msg);
		scanf("%i", &option);
		fflush(stdin);
		return option;
	}

	//Just print message
	if (type == NONE){ 	
		printf("%s", msg);
		return -1;
	}

	return -1;
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

/*(search term, pointer to book, number of contacts in list, searching name/phone/email/si_no, unused, unused)
field: 1 = name, 2 = phone, 3 = email, 4 = serial number*/
Status search(const char *str, AddressBook *address_book, int loop_count, int field, const char *msg, Modes mode)
{	
	int match;
	char search[32];	//The search term
	char *searchPtr = (char *)address_book->list; // Start ptr at beginning of list/first contactinfo
	//Cache frequently used sizes of arrays inside of contactinfo
	int nameSize = sizeof(address_book->list->name);
	int phoneArraySize = sizeof(address_book->list->phone_numbers);
	int emailArraySize = sizeof(address_book->list->email_addresses);

	//Store array for index i where the matching contactinfo is found.
	//Initialized to -1 as list_contact stops printing when it sees -1 in foundMatch
	int foundMatch[MAX_SEARCH_RESULTS] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
	int numFound = 0;

	strcpy(search, str);
	for (int i=0; i<=loop_count-1; i++){
		match = -1;
		switch (field){
			case 1:{ //By name
				match = strcmp(search, searchPtr); //We are already looking at first name in list, so we compare right away
				if (match == 0) {
					foundMatch[numFound] = i; //Store index we are currently at as match was found
					numFound++;
				}
				searchPtr += sizeof(ContactInfo); //Jump to next contact
				break;
			}
			case 2:{ //By phone number
				searchPtr += nameSize; //Goto 1st phone number in contact
				for (int phoneNum=0; phoneNum < PHONE_NUMBER_COUNT; phoneNum++){ //This loop searches all of contact n's phone numbers
					match = strcmp(str, searchPtr);
					if (match == 0) {
						foundMatch[numFound] = i;
						numFound++;
					}
					searchPtr += sizeof(address_book->list->phone_numbers[0]); //Jump to next phone number
				}
				//searchPtr is now at emailaddress 1
				searchPtr -= phoneArraySize + nameSize; //Go back to beginning of contact
				searchPtr += sizeof(ContactInfo); //Jump forward one contact
				break;
			}
			case 3:{ //By email address
				//Jump to beginning of email addresses
				searchPtr += nameSize + phoneArraySize;

				for (int emailAdd=0; emailAdd < EMAIL_ID_COUNT; emailAdd++){
					match = strcmp(str, searchPtr);
					if (match == 0) {
						foundMatch[numFound] = i;
						numFound++;
					}
					searchPtr += sizeof(address_book->list->email_addresses[0]);
				}
				//Same as above. Return to beginning of contact
				searchPtr -= emailArraySize + phoneArraySize + nameSize;
				searchPtr += sizeof(ContactInfo);
				break;
			}
			case 4:{ //By serial number
				//Jump to beginning of serial number
				searchPtr += nameSize + phoneArraySize + emailArraySize;
				int si_no = strtol(str, NULL, 10);
				if (*searchPtr - si_no == 0) match = 0;
				if (match == 0) {
					foundMatch[numFound] = i;
					numFound++;
				}
				searchPtr += sizeof(address_book->list->si_no);
				break;
			}
		}

		
	}
	if (foundMatch[0] != -1) {
		list_contacts(address_book, "Search Result:\n", foundMatch, "", e_search);
		return e_success;
	}
	else {
		//Failed to find something, spit out error maybe here or for each case
		printf("No result found for \"%s\"\n ",str);
		return e_fail;
	}

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
	Status ret;
	do {
		printf("####### Address Book #######\n");
		printf("####### Search Contact by:\n");
		printf("0. Back\n");
		printf("1. Name\n");
		printf("2. Phone number\n");
		printf("3. Email ID\n");
		printf("4. Serial number\n\n");
		option = get_option(NUM, "Please select an option: ");
		fflush(stdin);
		switch (option){
			case 0: 
				return e_exit;
			case 1:{
				printf("Enter the name: ");
				scanf("%[^\n]s", str);
				ret = search(str, address_book, address_book->count, option, "", e_search);
				break;
			}
			case 2:{
				printf("Enter a phone number: ");
				scanf("%[^\n]s", str);
				ret = search(str, address_book, address_book->count, option, "", e_search);
				break;
			}
			case 3:{
				printf("Enter an email address: ");
				scanf("%[^\n]s", str);
				ret = search(str, address_book, address_book->count, option, "", e_search);
				break;
			}
			case 4:{
				printf("Enter a serial number: ");
				scanf("%[^\n]s", str);
				ret = search(str, address_book, address_book->count, option, "", e_search);
				break;
			}
			default:{
				option = -1;
			}
		}
	}while (option != 0);
	
	return ret;
}

Status edit_contact(AddressBook *address_book)
{
	/* Add the functionality for edit contacts here */
}

Status delete_contact(AddressBook *address_book)
{
	/* Add the functionality for delete contacts here */
}
