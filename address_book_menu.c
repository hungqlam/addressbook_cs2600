#include <stdio.h>
//#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

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

Status edit_contact(AddressBook *address_book)
{
	/* Add the functionality for delete contacts here */
}

Status delete_contact(AddressBook *address_book)
{
	/* Add the functionality for delete contacts here */
	/* Add the functionality for delete contacts here */
	char str[80];
	char delete_char;

	menu_header("Search Contact to Delete By:\n");

	printf("0. Back\n");
	printf("1. Name\n");
	printf("2. Phone No\n");
	printf("3. Email ID\n");
	printf("4. Serial No\n");

	int option = -1;
	// option = valid_int("Please select an option: ", 0, 4);
	printf("Please select an option: ");

	scanf("%d", &option);

	printf("Delete Option = %d\n", option);

	switch (option)
	{
	case e_first_opt:
		break;
	case e_second_opt:
		printf("Enter the name: ");
		fflush(stdin);
		scanf("%[^\n]s", str);
		if (search(str, address_book, address_book->count, option, "", e_delete) != e_success)
		{
			printf("---FAIL---\n");

			return e_fail;
		}
		break;
	case e_third_opt:
		printf("Enter the Phone No: ");
		fflush(stdin);
		scanf("%[^\n]s", str);
		if (search(str, address_book, address_book->count, option, "", e_delete) != e_success)
		{
			printf("---FAIL---\n");

			return e_fail;
		}
		break;
	case e_fourth_opt:
		printf("Enter the Email ID: ");
		fflush(stdin);
		scanf("%[^\n]s", str);
		if (search(str, address_book, address_book->count, option, "", e_delete) != e_success)
		{
			printf("---FAIL---\n");

			return e_fail;
		}
		break;
	case e_fifth_opt:
		printf("Enter the Serial No: ");
		fflush(stdin);
		scanf("%[^\n]s", str);
		if (search(str, address_book, address_book->count, option, "", e_delete) != e_success)
		{
			printf("---FAIL---\n");

			return e_fail;
		}
		break;
	default:
		printf("Default case\n");
	}
	fflush(stdin);
	printf("\nPress: [s] = Select, [q] | Cancel: ");

	scanf("%c", delete_char);
	printf("%c\n", delete_char);

	if (true)
	{
		int delete_line;
		fflush(stdin);
		printf("Select a Serial Number (S.No) to Delete: ");
		scanf("%d", &delete_line);

		FILE *fileptr1, *fileptr2;
		char filename[40] = DEFAULT_FILE;
		char ch;
		int temp = 1;

		fileptr1 = fopen(filename, "r");

		fileptr2 = fopen("temp.csv", "w");
		ch = 'A';
		while (ch != EOF)
		{
			ch = getc(fileptr1);
			
			if (temp != delete_line)
			{
				
				putc(ch, fileptr2);
			}
			if (ch == '\n')
			{
				temp++;
			}
		}
		fclose(fileptr1);
		fclose(fileptr2);
		remove("address_book.csv");

		rename("temp.csv", DEFAULT_FILE);
	}

}
