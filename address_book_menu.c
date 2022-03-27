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
ContactInfo *getSerialNo(AddressBook *address_book, int si_no)
{
	for (int person = 0; person < address_book->count; person++)
	{
		
		if (((address_book->list) + person)->si_no == si_no)
		{
			return ((address_book->list) + person);
		}
	}
	return NULL;
}
Status edit_contact(AddressBook *address_book)
{
	int string_len;
	char str[50];
	MenuOptions opt;
	do
	{
		ContactInfo *person;
		
		printf("#######   Search contact to edit by: ");
		printf("\n\n");
		printf("0. Back");
		printf("\n1. Name");
		printf("\n2. Phone No  ");
		printf("\n3. Email ID  ");
		printf("\n4. Serial No \n\n");
		opt = get_option(NUM, "Please select an option: ");

		switch(opt)
		{
			case 0: return e_exit;
			case 1:
			{
				printf("Enter the name: ");
				scanf("%[^\n]s", str);
				//fgets(str, NAME_LEN, stdin);
				search(str, address_book, address_book->count, opt, "", e_search);
				break;
			}
			case 2:
			{
				printf("Enter a phone number: ");
				scanf("%[^\n]s", str);
				search(str, address_book, address_book->count, opt, "", e_search);
				break;
			}
			case 3:
			{
				printf("Enter an email address: ");
				scanf("%[^\n]s", str);
				search(str, address_book, address_book->count, opt, "", e_search);
				break;
			}
			case 4:
			{
				printf("Enter a serial number: ");
				scanf("%[^\n]s", str);
				search(str, address_book, address_book->count, opt, "", e_search);
				break;
			}
			default:
			{
				return e_no_match;
				break;
			}

		}

		char option = get_option(CHAR, "Press: [s] = Select, Press: [q] | Cancel: ");
		if(option == 's')
		{
			do
			{
			printf("Select a Serial Number (S.No) to Edit: ");
			person = getSerialNo(address_book, get_option(NUM,""));
			}while (person == NULL);

			do
			{
				//Print out the information
				printf("\n0. Back");
				printf("\n1. Name       : %s", person->name[0]);
				for (int name = 1; name < NAME_COUNT; name++)
				{
					if (strcmp(person->name[name], ""))
					{
						printf("\n%13d : %s", name + 1, person->name[name]);
					}
				}
				printf("\n2. Phone No 1 : %s", person->phone_numbers[0]); 
				for (int phone = 1; phone < PHONE_NUMBER_COUNT; phone++)
				{
					if (strcmp(person->phone_numbers[phone], ""))
					{
						printf("\n%13d : %s", phone + 1, person->phone_numbers[phone]);
					}
				}
				printf("\n3. Email ID 1 : %s", person->email_addresses[0]);
				for (int email = 1; email < EMAIL_ID_COUNT; email++)
				{
					if (strcmp(person->email_addresses[email], ""))
					{
						printf("\n%13d : %s", email + 1, person->email_addresses[email]);
					}
				}

				opt = get_option(NUM,"Please select an option: ");
				switch (opt)
				{
				case e_first_opt:
				case e_second_opt:
				case e_third_opt:
					edit_information(person, opt);
					break;
				default:
					break;
				}


			}while(opt != 0);

		}

		else
		opt = 0;

		
	}while (opt != 0);
	      
	return e_success;
	

}


Status delete_contact(AddressBook *address_book)
{
	/* Add the functionality for delete contacts here */
}
