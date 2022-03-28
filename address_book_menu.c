#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "abk_fileops.h"
#include "abk_log.h"
#include "abk_menus.h"
#include "abk.h"
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

	system("clear");

	printf("#######  Address Book  #######\n");
	if (str != '\0')
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
	
	int opt;
	int condition = 0;
	do
	{
		/* code */
		// menu_header("Add Contact:");
		// printf("0. Back");
		// printf("\n1. Name");
		// printf("\n2. Phone No 1: ");
		// printf("\n3. Email ID 1: ");
		contact_confirmation(address_book->count, "Adding contact", address_book);

		opt = get_option(NUM, "\n\nPlease select an option: ");
		printf("Count is: %d\n", address_book->count);
		switch (opt)
		{
			case e_second_opt:
			{
				printf("Enter the name:");
				char str[32];
				fflush(stdin);
				scanf("%[^\n]s", str);
				fflush(stdin);
				strcpy(address_book->list[address_book->count].name[0], str);
				condition = 1;
				break;
			}
				
			case e_third_opt:
			{
				int index = 0;
				printf("Enter Phone Number index to be changed [Max %d]: ", PHONE_NUMBER_COUNT);
				index = get_option(NUM, "");
				index = index - 1;
				int string_len;
				char str[32];
				fflush(stdin);
				// check if the the index is negative or over the PHONE_NUMBER_COUNT
				if (index < -1 || index > PHONE_NUMBER_COUNT)
					break;

				// Prompt the user to enter the phone number to change
				printf("Enter Phone Number %d: ", index + 1);
				scanf("%[^\n]s", str);
				string_len = strlen(str) - 1;

				if (str[string_len] == '\n')
					str[string_len] = '\0'; // set the end of userInput to null
				strcpy(address_book->list[address_book->count].phone_numbers[index], str);
				condition = 1;
				break;
			}
				
			case e_fourth_opt:
			{
				int index = 0;
				printf("Enter Email Number index to be changed [Max %d]: ", EMAIL_ID_COUNT);
				index = get_option(NUM, "");
				index = index - 1;
				int string_len;
				char str[32];
				fflush(stdin);
				// check if the the index is negative or over the EMAIL_ID_COUNT
				if (index < -1 || index > EMAIL_ID_COUNT)
					break;
				// Prompt the user to enter the phone number to change
				printf("Enter Email Number %d: ", index + 1);
				scanf("%[^\n]s", str);
				string_len = strlen(str) - 1;
				if (str[string_len] == '\n')
					str[string_len] = '\0'; // set the end of userInput to null
				strcpy(address_book->list[address_book->count].email_addresses[index], str);
				condition = 1;
				break;
			}
				
		
			case e_first_opt:
			// case 0
				break;
			default:
				return e_fail;
		}
	} while (opt!=0);
	if (condition == 1) {
		address_book->list[address_book->count].si_no = address_book->count + 1;
		address_book->count++;
	}
	return e_success;
}

Status search(const char *str, AddressBook *address_book, int loop_count, int field, const char *msg, Modes mode)
{
	/* Add the functionality for adding contacts here */
}

Status search_contact(AddressBook *address_book)
{
	/* Add the functionality for search contacts here */
}

Status edit_contact(AddressBook *address_book)
{
	/* Add the functionality for edit contacts here */
}

Status delete_contact(AddressBook *address_book)
{
	/* Add the functionality for delete contacts here */
}
