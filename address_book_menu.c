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
	 * Read an number
	 * Read a charcter
	 */ 

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

	system("cls"); //changed clear to cls

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

		//option = get_option(NUM, "");
		scanf("%i", &option);
		
		if ((address_book-> count == 0) && (option != e_add_contact))
		{
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
}

Status search_contact(AddressBook *address_book)
{
	/* Add the functionality for search contacts here */
}

Status edit_information(ContactInfo *person, MenuOptions option)
{
	int index;
	int string_len;
	char *userInput;
	switch(option)
	{
	case e_first_opt:
			userInput = malloc(sizeof(char) * NAME_LEN);

			//Promt the user to enter the name index to change
			printf("Enter Name index to be changed [Max %d]: ", NAME_COUNT);
			fgets(userInput, NAME_LEN, stdin);
			index = atoi(userInput);

			//check if the the index is negative or over the NAME_COUNT
			if (index < 1 || index > NAME_COUNT)
				break;

			//Prompt the user to enter the name to change
			printf("Enter Name %d: [Just enter removes the entry]: ", index);

			fgets(userInput, NAME_LEN, stdin);
			string_len = strlen(userInput) - 1;
			if (userInput[string_len] == '\n')
				userInput[string_len] = '\0'; //set the end of userInput to null

			strcpy(person->name[index - 1], userInput);
			free(userInput);
			break;
	case e_second_opt:
		userInput = malloc(sizeof(char) * NAME_LEN);

		//Promt the user to enter the phone number index to change
		printf("Enter Phone Number index to be changed [Max %d]: ", PHONE_NUMBER_COUNT);
		fgets(userInput, NUMBER_LEN, stdin);
		index = atoi(userInput);

		//check if the the index is negative or over the PHONE_NUMBER_COUNT
		if (index < 1 || index > PHONE_NUMBER_COUNT)
			break;

		//Prompt the user to enter the phone number to change
		printf("Enter Phone Number %d: [Just enter removes the entry]: ", index);
		fgets(userInput, NUMBER_LEN, stdin);
		string_len = strlen(userInput) - 1;

		if (userInput[string_len] == '\n')
			userInput[string_len] = '\0'; //set the end of userInput to null
		strcpy(person->phone_numbers[index - 1], userInput);

		free(userInput);
		break;
		
	case e_third_opt:
		
		userInput = malloc(sizeof(char) * NAME_LEN);
		//Promt the user to enter the email index to change
		printf("Enter Email ID index to be changed [Max %d]: ", EMAIL_ID_COUNT);
			fgets(userInput, EMAIL_ID_LEN, stdin);
			index = atoi(userInput);

		//check if the the index is negative or over the EMAIL_ID_COUNT
			if (index < 1 || index > EMAIL_ID_COUNT)
				break;

		//Prompt the user to enter the email id to change
			printf("Enter Email ID %d: [Just enter removes the entry]: ", index);
			fgets(userInput, EMAIL_ID_LEN, stdin);
		string_len = strlen(userInput) - 1;

		if (userInput[string_len] == '\n')
			userInput[string_len] = '\0'; //set the end of userInput to null

		strcpy(person->email_addresses[index - 1], userInput);
		free(userInput);
		break;
	
	}
	return e_success;
}
Status edit_contact(AddressBook *address_book)
{
	/* Add the functionality for edit contacts here */ 
	//char userInput[50];
	//char input;
	MenuOptions opt;
	char *nam;
	char *phon;
	char *ema; 
	int se_no;
	char input;
	do
	{
		ContactInfo *person;
		printf("#######   Search contact to edit by: ");
		printf("\n\n");
		printf("0. Back");
		printf("\n1. Name");
		printf("\n2. Phone No  ");
		printf("\n3. Email ID  ");
		printf("\n4. Serial No ");
		printf("\n\nPlease select an option: ");

		opt = get_option(NUM, "");
		
		//Start searching to edit
		switch (opt)
		{
		case e_first_opt: //name option
			printf("Enter the Name: ");
			scanf("%c",&nam);
			//search function
			printf("Press: [s] = Select, Press: [q] | Cancel:");
			scanf("%c",&input);
			if(input == 's')
			{
				printf("Select a Serial Number (S.No) to Edit: ");
				//prompt the user to enter the serial no to edit
				// print all the information of the person to edit

				opt = get_option(NUM, "");
				edit_information(person, opt)	;	

			}
			
			
			break;

		case e_second_opt: //phone number option
			printf("Enter the Phone Number: ");
			scanf("%c",&phon);

			//search function
			printf("Press: [s] = Select, Press: [q] | Cancel:");
			scanf("%c",&input);
			if(input == 's')
			{
				printf("Select a Serial Number (S.No) to Edit: ");
				//prompt the user to enter the serial no to edit
				// print all the information of the person to edit

				opt = get_option(NUM, "");
				edit_information(person, opt)	;	

			}		
			
			break;

		case e_third_opt: //email ID option
			printf("Enter the Email ID: ");
			scanf("%c",&ema);

			//search function
			printf("Press: [s] = Select, Press: [q] | Cancel:");
			scanf("%c",&input);
			if(input == 's')
			{
				printf("Select a Serial Number (S.No) to Edit: ");
				//prompt the user to enter the serial no to edit
				// print all the information of the person to edit

				opt = get_option(NUM, "");
				edit_information(person, opt)	;	

			}		

			break;

		case e_fourth_opt: //serial number option
			printf("Enter the Serial Number: ");
			scanf("%d",&se_no);

			//search function
			printf("Press: [s] = Select, Press: [q] | Cancel:");
			scanf("%c",&input);
			if(input == 's')
			{
				printf("Select a Serial Number (S.No) to Edit: ");
				//prompt the user to enter the serial no to edit
				// print all the information of the person to edit

				opt = get_option(NUM, "");
				edit_information(person, opt)	;	

			}		
			break;

		case e_no_opt: //back option
			break;
		}
		
	} while (opt != 0);

	return e_success;
	

}


Status delete_contact(AddressBook *address_book)
{
	/* Add the functionality for delete contacts here */
}
