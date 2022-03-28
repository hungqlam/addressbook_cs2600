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
	do
	{
		/* code */
		printf("#######   Add Contact:");
		printf("\n\n");
		printf("0. Back");
		printf("\n1. Name");
		printf("\n2. Phone No 1: ");
		printf("\n3. Email ID 1: ");
		printf("\n\nPlease select an option: ");

		scanf("%d",&opt);
		address_book = (AddressBook*) malloc(sizeof(AddressBook));
		address_book->list = (ContactInfo*) malloc(sizeof(ContactInfo));

		    if(address_book == NULL)
		    {
			printf("Cannot Allocate Memory\n");

			return -1;
		    }

		    address_book->count +=1;
		   
		    address_book->list->si_no +=1;
		    if(address_book->list == NULL)
		    {
			printf("Cannot Allocate Memory \n");
			 /* on failure free successfuly allocated book */
			 free(book);
			 return  -1;
		    }
		
		switch (opt)
		{
		
			case e_second_opt:
				printf("Enter the name:");
				if(scanf("%s", &adress_book->list->name[book->count])!=1)
				    {
					printf("Invalid, input\n");
					free(address_book->list);
					free(address_book);
					return -1;
				    }
				break;
			case e_third_opt:
				printf("Enter the phone number :");
				if(scanf("%s", &address_book->list->phone_numbers[book->count])!=1)
				    {
					printf("Invalid, input\n");
					free(address_book->list);
					free(address_book);
					return -1;
				    }
				break;
			case e_fourth_opt:
				printf("Enter email:");
				if(scanf("%s", &address_book->list->email_addresses[book->count])!=1)
				    {
					printf("Invalid, input\n");
					free(address_book->list);
					free(address_book);
					return -1;
				    }
    
				break;
		
			case e_first_opt:
			// case 0
				break;
		}
	} while (opt!=0);
	
	

	
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
