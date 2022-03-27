#include <stdio.h>
//#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <errno.h>

#include "address_book_fops.h"
//#include "abk_log.h"
#include "address_book_menu.h"
#include "address_book.h"


int valid_int(const char *msg, int low, int high)
{
	int input;
	while (1)
	{
		printf("%s", msg);
		fflush(stdout);
		scanf("%i", &input);
		if (input >= low && input <= high)
		{
			break;
		}
		else
		{
			printf("Please enter valid a option between %d-%d !\n", low, high);
		}

		while (getchar() != '\n')
			;

		// clear input
	}

	return input;
}

void contact_confirmation(int target, char *msg, AddressBook *address_book)
{
	printf("Called confirmation\n");
	int count = 0;
	char condition[32] = "";

	menu_header(msg);
	printf("0. Exit\n");
	printf("1. Name       : %s\n", address_book->list[target].name[count]);
	printf("2. Phone No %d : %s\n", count + 1, address_book->list[target].phone_numbers[count]);

	for (int phone = 1; phone < PHONE_NUMBER_COUNT; phone++)
	{
		if ((int)address_book->list[target].phone_numbers[phone][0] != 32) // Condition error
		{
			printf("            %d : %s\n", phone + 1, address_book->list[target].phone_numbers[phone]);
		}
	}

	printf("3. Email ID 1 : %s\n", address_book->list[target].email_addresses[count]);

	for (int email = 1; email < EMAIL_ID_COUNT; email++)
	{

		if ((int)address_book->list[target].email_addresses[email][0] != 32)
		{
			printf("            %d : %s\n", email + 1, address_book->list[target].email_addresses[email]);
		}
	}

	printf("\n");
	fflush(stdout);
}
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
	int count = 0;
	char print_option;
	int line_size = -30;
	int si_size = -5;
	char line[] = "================================================================================================================================";
	// Default operation to list all the current contact
	if (index == NULL && mode == e_list_contacts)
	{
		do
		{
			menu_header(title);
			printf("%.*s\n", 107, line);
			printf(": %*s : %*s : %*s : %*s:\n", si_size, "S. No", line_size, "Name", line_size, "Phone No", line_size, "Email Id");
			printf("%.*s\n", 107, line);
			fflush(stdout);

			for (int i = count; i < WINDOW_SIZE + count; i++)
			{
				for (int j = 0; j < 5; j++)
				{
					if (j == 0)
					{
						printf(": %*d : %*s :", si_size, address_book->list[i].si_no, line_size, address_book->list[i].name[0]);
					}
					else
					{
						printf(": %*s : %*s :", si_size, "", line_size, "");
					}
					printf(" %*s : %*s:\n", line_size, address_book->list[i].phone_numbers[j], line_size, address_book->list[i].email_addresses[j]);
				}
				printf("%.*s\n", 107, line);
			}

			// while (getchar() != '\n')
			// 	;
			// printf("%s", msg);
			// fflush(stdout);
			// print_option = getchar();
			print_option = get_option(CHAR, msg);

			switch (print_option)
			{
			case 'n':
				count += WINDOW_SIZE;
				break;
			case 'p':
				if (count != 0)
					count -= WINDOW_SIZE;
				break;
			case 'q':
				break;
			default:
				printf("Please enter a valid option!\n");
			}

		} while (print_option != 'q');
	}
	else // when called by search() to print out all found indices (int* index)
	{
		int found = 0;
		menu_header(title);
		printf("%.*s\n", 107, line);
		printf(": %*s : %*s : %*s : %*s:\n", si_size, "S. No", line_size, "Name", line_size, "Phone No", line_size, "Email Id");
		printf("%.*s\n", 107, line);
		fflush(stdout);
		for (int i = 0; i < address_book->count; i++) // Loop through the entire AddressBook
		{

			if (i == index[found] && index[found] >= 0 && index[found] <= address_book->count) // Temporal condition
			{

				for (int j = 0; j < 5; j++)
				{
					if (j == 0)
					{
						printf(": %*d : %*s :", si_size, address_book->list[i].si_no, line_size, address_book->list[i].name[0]);
					}
					else
					{
						printf(": %*s : %*s :", si_size, "", line_size, "");
					}
					printf(" %*s : %*s:\n", line_size, address_book->list[i].phone_numbers[j], line_size, address_book->list[i].email_addresses[j]);
				}
				printf("%.*s\n", 107, line);
				found++;
			}
		}
		while (getchar() != '\n')
			;
		printf("%s\n", msg);
		fflush(stdout);
	}

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
				list_contacts(address_book, "Search Result:\n", NULL, "Press: [n] = Next Page, [p] = Previous Page, [q] | Cancel : ", e_list_contacts);
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
	char str[80];
	char delete_char, confirmation;
	int target;
	int count = 0;

	menu_header("Search Contact to Delete By:\n");

	printf("0. Back\n");
	printf("1. Name\n");
	printf("2. Phone No\n");
	printf("3. Email ID\n");
	printf("4. Serial No\n");

	int option = -1;
	option = get_option(NUM, "Please select an option: ");
	// printf("Please select an option: ");
	// scanf("%d", &option);

	switch (option)
	{
	case e_first_opt:
		return e_back;
		break;
	case e_second_opt:
		printf("Enter the name: ");
		fflush(stdin);
		scanf("%[^\n]s", str);
		if (search(str, address_book, address_book->count, option, "", e_delete) != e_success)
		{
			printf("---FAIL---\n");

			return e_no_match;
		}
		break;
	case e_third_opt:
		printf("Enter the Phone No: ");
		fflush(stdin);
		scanf("%[^\n]s", str);
		if (search(str, address_book, address_book->count, option, "", e_delete) != e_success)
		{
			printf("---FAIL---\n");

			return e_no_match;
		}
		break;
	case e_fourth_opt:
		printf("Enter the Email ID: ");
		fflush(stdin);
		scanf("%[^\n]s", str);
		if (search(str, address_book, address_book->count, option, "", e_delete) != e_success)
		{
			printf("---FAIL---\n");

			return e_no_match;
		}
		break;
	case e_fifth_opt:
		printf("Enter the Serial No: ");
		fflush(stdin);
		scanf("%[^\n]s", str);
		if (search(str, address_book, address_book->count, option, "", e_delete) != e_success)
		{
			printf("---FAIL---\n");
			return e_no_match;
		}
		break;
	default:
		return e_fail;
	}

	// printf("\nPress: [s] = Select, [q] | Cancel: ");
	// delete_char = getchar();
	delete_char = get_option(CHAR, "\nPress: [s] = Select, [q] | Cancel: ");

	if (delete_char == 's')
	{
		printf("Select a serial Number (S.No) to Delete: ");
		fflush(stdout);
		scanf("%d", &target);
		target = target - 1;
		contact_confirmation(target, "Delete Contact:\n", address_book);

		// printf("Enter 'Y' to delete. [Press any key to ignore]: ");
		// while (getchar() != '\n')
		// 	;
		// fflush(stdout);
		// confirmation = getchar();
		confirmation = get_option(CHAR, "Enter 'Y' to delete. [Press any key to ignore]: ");

		if (confirmation == 'Y')
		{
			count = target;

			while (count < address_book->count)
			{
				if (count == (address_book->count - 1))
				{ // last contact
					strcpy(address_book->list[count].name[0], "");
					address_book->list[count].si_no = 0;
				}
				strcpy(address_book->list[count].name[0], address_book->list[count + 1].name[0]);
				for (int i = 0; i < PHONE_NUMBER_COUNT; i++)
				{
					if (count == (address_book->count - 1))
					{ // last contact
						strcpy(address_book->list[count].phone_numbers[0], "");
						strcpy(address_book->list[count].email_addresses[0], "");
					}
					strcpy(address_book->list[count].phone_numbers[0], address_book->list[count + 1].phone_numbers[0]);
					strcpy(address_book->list[count].email_addresses[0], address_book->list[count + 1].email_addresses[0]);
				}
				count++;
			}
			address_book->count--;
		}
	}
	return e_success;
}