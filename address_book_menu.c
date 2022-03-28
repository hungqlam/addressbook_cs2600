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
			case 0: 
				return e_back;
				break;
			case 1:
			
				printf("Enter the name: ");
				fflush(stdin);
				scanf("%[^\n]s", str);
				
				search(str, address_book, address_book->count, opt, "", e_search);
			break;
			case 2:
			
				printf("Enter a phone number: ");
				fflush(stdin);
				scanf("%[^\n]s", str);
					search(str, address_book, address_book->count, opt, "", e_search);
				break;
			
			case 3:
			
				printf("Enter an email address: ");
				fflush(stdin);
				scanf("%[^\n]s", str);
				search(str, address_book, address_book->count, opt, "", e_search);
			
				break;
			
			case 4:
			
				printf("Enter a serial number: ");
				fflush(stdin);
				scanf("%[^\n]s", str);			
				search(str, address_book, address_book->count, opt, "", e_search);
				break;
			
			default:
			
				return e_no_match;
				break;
			

		}

		char option = get_option(CHAR, "Press: [s] = Select, Press: [q] | Cancel: ");
		if(option == 's')
		{
			
			
			person = get_option(NUM, "Select a Serial Number (S.No) to Edit: ");
			person = person - 1; // Shift back

			do
			{
				//Print out the information
				contact_confirmation(person, "Edit Contact:\n", address_book);
				opt = get_option(NUM, "Please select an option: ");
								
				
				switch (opt)
				{
				case e_first_opt:
					break;
		
				case e_second_opt:
						printf("Enter Name index to be changed [Max %d]: ", NAME_COUNT);
						index = get_option(NUM, "");
						index = index - 1;

						// check if the the index is negative or over the NAME_COUNT
						if (index < -1 || index > NAME_COUNT)
							break;

						// Prompt the user to enter the name to change
						printf("Enter Name %d: [Just enter removes the entry]: ", index);

						fgets(str, NAME_LEN, stdin);

						string_len = strlen(str) - 1;
						if (str[string_len] == '\n')
							str[string_len] = '\0'; // set the end of userInput to null

						strcpy(address_book->list[person].name[index], str);
						break;

				case e_third_opt:
					//Promt the user to enter the phone number index to change
					printf("Enter Phone Number index to be changed [Max %d]: ", PHONE_NUMBER_COUNT);
					index = get_option(NUM, "");
					index = index - 1;

					//check if the the index is negative or over the PHONE_NUMBER_COUNT
					if (index < 1 || index > PHONE_NUMBER_COUNT)
						break;

					//Prompt the user to enter the phone number to change
					printf("Enter Phone Number %d: [Just enter removes the entry]: ", index);
					fgets(str, NUMBER_LEN, stdin);
					string_len = strlen(str) - 1;

					if (str[string_len] == '\n')
						str[string_len] = '\0'; //set the end of userInput to null
					strcpy(address_book->list[person].phone_numbers[index], str);
					break;

				case e_fourth_opt:
					//Promt the user to enter the email index to change
					printf("Enter Email ID index to be changed [Max %d]: ", EMAIL_ID_COUNT);	
					index = get_option(NUM, "");
					index = index - 1;

				//check if the the index is negative or over the EMAIL_ID_COUNT
					if (index < 1 || index > EMAIL_ID_COUNT)
						break;

				//Prompt the user to enter the email id to change
					printf("Enter Email ID %d: [Just enter removes the entry]: ", index);
					fgets(str, EMAIL_ID_LEN, stdin);
					string_len = strlen(userInput) - 1;

				if (str[string_len] == '\n')
					str[string_len] = '\0'; //set the end of userInput to null

				strcpy(address_book->list[person].email_addresses[index], str);

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
