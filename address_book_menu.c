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
	int count = 0;
	char condition[32] = "";
	int character;

	menu_header(msg);
	printf("0. Exit\n");
	printf("1. Name       : %s\n", address_book->list[target].name[count]);
	printf("2. Phone No %d : %s\n", count + 1, address_book->list[target].phone_numbers[count]);

	for (int phone = 1; phone < PHONE_NUMBER_COUNT; phone++)
	{
		character = (int)address_book->list[target].phone_numbers[phone][0];
		if (character != 32 && character != 0) // Condition error
		{
			printf("            %d : %s\n", phone + 1, address_book->list[target].phone_numbers[phone]);
		}
	}

	printf("3. Email ID 1 : %s\n", address_book->list[target].email_addresses[count]);

	for (int email = 1; email < EMAIL_ID_COUNT; email++)
	{
		character = (int)address_book->list[target].email_addresses[email][0];
		if (character != 32 && character != 0)
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
	 * Read an number OR
	 * Read a charcter
	 */
	fflush(stdin);

	if (type == CHAR)
	{
		char option;
		printf("%s", msg);	// First print the message passed to us
		option = getchar(); // Then capture a character
		return option;
	}

	if (type == NONE)
	{ // Not sure how to interpret a NONE option
		printf("%s", msg);
		return -1;
	}
	if (type == NUM)
	{
		int option;
		printf("%s", msg);
		scanf("%i", &option);
		return option;
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

			for (int info = count; info < WINDOW_SIZE + count; info++)
			{
				for (int field = 0; field < PHONE_NUMBER_COUNT; field++)
				{
					if (field == 0)
					{
						printf(": %*d : %*s :", si_size, address_book->list[info].si_no, line_size, address_book->list[info].name[0]);
					}
					else
					{
						printf(": %*s : %*s :", si_size, "", line_size, "");
					}
					printf(" %*s : %*s:\n", line_size, address_book->list[info].phone_numbers[field], line_size, address_book->list[info].email_addresses[field]);
				}
				printf("%.*s\n", 107, line);
			}

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
		for (int info = 0; info < address_book->count; info++) // Loop through the entire AddressBook
		{

			if (info == index[found] && index[found] >= 0 && index[found] <= address_book->count) // Temporal condition
			{

				for (int field = 0; field < 5; field++)
				{
					if (field == 0)
					{
						printf(": %*d : %*s :", si_size, address_book->list[info].si_no, line_size, address_book->list[info].name[0]);
					}
					else
					{
						printf(": %*s : %*s :", si_size, "", line_size, "");
					}
					printf(" %*s : %*s:\n", line_size, address_book->list[info].phone_numbers[field], line_size, address_book->list[info].email_addresses[field]);
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

	system("cls"); // changed clear to cls

	printf("#######  Address Book  #######\n");
	if (str != '\0') // if (!strcmp(str, "\0"))
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

		if ((address_book->count == 0) && (option != e_add_contact))
		{
			// This doesn't appear to be functioning with just search function implemented
			get_option(NONE, "No entries found!!. Would you like to add? Use Add Contacts");

			continue;
		}

		switch (option)
		{
		case e_add_contact:
			add_contacts(address_book);
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

	fflush(stdout);

	return e_success;
}

Status add_contacts(AddressBook *address_book)
{
	// /* Add the functionality for adding contacts here */

	// int opt;
	// do
	// {
	// 	/* code */
	// 	menu_header("Add Contact");
	// 	printf("0. Back");
	// 	printf("\n1. Name");
	// 	printf("\n2. Phone No 1: ");
	// 	printf("\n3. Email ID 1: ");
	// 	printf("\n\nPlease select an option: ");

	// 	opt = get_option(% d, "\nPlease select an option: ");
	// 	scanf("%d", &opt);

	// 	if (address_book == NULL)
	// 	{
	// 		printf("Cannot Allocate Memory\n");

	// 		return -1;
	// 	}

	// 	address_book->count += 1;

	// 	address_book->list->si_no += 1;
	// 	if (address_book->list == NULL)
	// 	{
	// 		printf("Cannot Allocate Memory \n");
	// 		/* on failure free successfuly allocated book */
	// 		free(book);
	// 		return -1;
	// 	}

	// 	switch (opt)
	// 	{

	// 	case e_second_opt:
	// 		printf("Enter the name:");
	// 		if (scanf("%s", &adress_book->list->name[book->count]) != 1)
	// 		{
	// 			printf("Invalid, input\n");
	// 			free(address_book->list);
	// 			free(address_book);
	// 			return -1;
	// 		}
	// 		break;
	// 	case e_third_opt:
	// 		printf("Enter the phone number :");
	// 		if (scanf("%s", &address_book->list->phone_numbers[book->count]) != 1)
	// 		{
	// 			printf("Invalid, input\n");
	// 			free(address_book->list);
	// 			free(address_book);
	// 			return -1;
	// 		}
	// 		break;
	// 	case e_fourth_opt:
	// 		printf("Enter email:");
	// 		if (scanf("%s", &address_book->list->email_addresses[book->count]) != 1)
	// 		{
	// 			printf("Invalid, input\n");
	// 			free(address_book->list);
	// 			free(address_book);
	// 			return -1;
	// 		}

	// 		break;

	// 	case e_first_opt:
	// 		// case 0
	// 		break;
	// 	}
	// } while (opt != 0);
}

Status search(const char *str, AddressBook *address_book, int loop_count, int field, const char *msg, Modes mode)
{
	// Dumb search
	int match;
	char search[32];
	char *searchPtr = (char *)address_book->list; // Start ptr at beginning of list
	int nameSize = sizeof(address_book->list->name);
	int phoneArraySize = sizeof(address_book->list->phone_numbers);
	int emailArraySize = sizeof(address_book->list->email_addresses);
	int foundMatch[MAX_SEARCH_RESULTS] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
	int numFound = 0;

	strcpy(search, str);
	for (int i = 0; i <= loop_count - 1; i++)
	{
		match = -1;
		switch (field)
		{
		case 1:
		{									   // By name
			match = strcmp(search, searchPtr); // We are already looking at first name in list
			if (match == 0)
			{
				foundMatch[numFound] = i;
				numFound++;
			}
			searchPtr += sizeof(ContactInfo); // Jump to next contact
			break;
		}
		case 2:
		{												   // By phone number
			searchPtr += sizeof(address_book->list->name); // Goto 1st phone number in contact
			for (int phoneNum = 0; phoneNum < PHONE_NUMBER_COUNT; phoneNum++)
			{									// This loop searches all of contact n's phone numbers
				match = strcmp(str, searchPtr); // Remember strcmp compares up to null character, so we wont go over entire array
				if (match == 0)
				{
					foundMatch[numFound] = i;
					numFound++;
				}
				searchPtr += sizeof(address_book->list->phone_numbers[0]); // Jump to next phone number
			}
			// searchPtr is now at emailaddress 1, we should go back a few
			searchPtr -= phoneArraySize + nameSize; // Go back to beginning of contact
			searchPtr += sizeof(ContactInfo);		// Jump forward one contact
			break;
		}
		case 3:
		{ // By email address
			// Jump to beginning of email addresses
			searchPtr += nameSize + phoneArraySize;

			for (int emailAdd = 0; emailAdd < EMAIL_ID_COUNT; emailAdd++)
			{
				match = strcmp(str, searchPtr);
				if (match == 0)
				{
					foundMatch[numFound] = i;
					numFound++;
				}
				searchPtr += sizeof(address_book->list->email_addresses[0]);
			}
			searchPtr -= emailArraySize + phoneArraySize + nameSize;
			searchPtr += sizeof(ContactInfo);
			break;
		}
		case 4:
		{ // By serial number
			// Jump to beginning of serial number
			searchPtr += nameSize + phoneArraySize + emailArraySize;
			int si_no = strtol(str, NULL, 10);
			if (*searchPtr - si_no == 0)
				match = 0;
			if (match == 0)
			{
				foundMatch[numFound] = i;
				numFound++;
			}
			searchPtr += sizeof(address_book->list->si_no);
			break;
		}
		}
	}
	if (foundMatch[0] != -1)
	{
		list_contacts(address_book, "Search Result:\n", foundMatch, "", e_search);
		return e_success;
	}
	else
	{
		// Failed to find something, spit out error maybe here or for each case
		printf("No result found for \"%s\"\n ", str);
		return e_fail;
	}
}

Status search_contact(AddressBook *address_book)
{
	/* Add the functionality for search contacts here */
	// This is the menu function, and will call search above
	// Name
	// Number
	// email
	int option = -1;
	char str[31];
	Status ret;
	do
	{
		printf("####### Address Book #######\n");
		printf("####### Search Contact by:\n");
		printf("0. Back\n");
		printf("1. Name\n");
		printf("2. Phone number\n");
		printf("3. Email ID\n");
		printf("4. Serial number\n\n");
		option = get_option(NUM, "Please select an option: ");
		fflush(stdin);
		switch (option)
		{
		case 0:
			return e_exit;
		case 1:
		{
			printf("Enter the name: ");
			scanf("%[^\n]s", str);
			// fgets(str, NAME_LEN, stdin);
			ret = search(str, address_book, address_book->count, option, "", e_search);
			break;
		}
		case 2:
		{
			printf("Enter a phone number: ");
			scanf("%[^\n]s", str);
			ret = search(str, address_book, address_book->count, option, "", e_search);
			break;
		}
		case 3:
		{
			printf("Enter an email address: ");
			scanf("%[^\n]s", str);
			ret = search(str, address_book, address_book->count, option, "", e_search);
			break;
		}
		case 4:
		{
			printf("Enter a serial number: ");
			scanf("%[^\n]s", str);
			ret = search(str, address_book, address_book->count, option, "", e_search);
			break;
		}
		default:
		{
			option = -1;
		}
		}
	} while (option != 0);
	return ret;
}

// Status edit_contact(AddressBook *address_book)
// {
// 	/* Add the functionality for edit contacts here */
// }

Status edit_contact(AddressBook *address_book)
{
	int string_len;
	char str[50];
	MenuOptions opt;
	do
	{
		int person;

		printf("#######   Search contact to edit by: ");
		printf("\n\n");
		printf("0. Back");
		printf("\n1. Name");
		printf("\n2. Phone No  ");
		printf("\n3. Email ID  ");
		printf("\n4. Serial No \n\n");
		opt = get_option(NUM, "Please select an option: ");

		switch (opt)
		{
		case 0:
			return e_exit;
		case 1:
		{
			printf("Enter the name: ");
			fflush(stdin);
			scanf("%[^\n]s", str);
			// fgets(str, NAME_LEN, stdin);
			search(str, address_book, address_book->count, opt, "", e_search);
			break;
		}
		case 2:
		{
			printf("Enter a phone number: ");
			fflush(stdin);
			scanf("%[^\n]s", str);
			search(str, address_book, address_book->count, opt, "", e_search);
			break;
		}
		case 3:
		{
			printf("Enter an email address: ");
			fflush(stdin);
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
		if (option == 's')
		{

			person = get_option(NUM, "Select a Serial Number (S.No) to Edit: ");
			person = person - 1; // Shift back
			do
			{
				// Print out the information
				// person = get_option(NUM,"Select a Serial Number (S.No) to Edit: " );

				contact_confirmation(person, "Edit Contact:\n", address_book);
				opt = get_option(NUM, "Please select an option: ");
				fflush(stdin);
				int index;
				switch (opt)
				{
				case e_first_opt:
					break;
				case e_second_opt:

					// Promt the user to enter the name index to change
					printf("Enter Name index to be changed [Max %d]: ", NAME_COUNT);
					index = get_option(NUM, "");
					index = index - 1;

					// check if the the index is negative or over the NAME_COUNT
					if (index < -1 || index > NAME_COUNT)
						break;

					// Prompt the user to enter the name to change
					printf("Enter Name %d: [Just enter removes the entry]: ", index);
					fflush(stdin);
					fgets(str, NAME_LEN, stdin);

					string_len = strlen(str) - 1;
					if (str[string_len] == '\n')
						str[string_len] = '\0'; // set the end of userInput to null

					strcpy(address_book->list[person].name[index], str);
					break;
				case e_third_opt:
					printf("Enter Phone Number index to be changed [Max %d]: ", PHONE_NUMBER_COUNT);
					index = get_option(NUM, "");
					index = index - 1;
					fflush(stdin);
					// check if the the index is negative or over the PHONE_NUMBER_COUNT
					if (index < -1 || index > PHONE_NUMBER_COUNT)
						break;

					// Prompt the user to enter the phone number to change
					printf("Enter Phone Number %d: [Just enter removes the entry]: ", index);
					fgets(str, NUMBER_LEN, stdin);
					string_len = strlen(str) - 1;

					if (str[string_len] == '\n')
						str[string_len] = '\0'; // set the end of userInput to null
					strcpy(address_book->list[person].phone_numbers[index], str);
					break;

				case e_fourth_opt:
					printf("Enter Email Address index to be changed [Max %d]: ", PHONE_NUMBER_COUNT);
					index = get_option(NUM, "");
					index = index - 1;
					fflush(stdin);
					// check if the the index is negative or over the PHONE_NUMBER_COUNT
					if (index < -1 || index > PHONE_NUMBER_COUNT)
						break;

					// Prompt the user to enter the phone number to change
					printf("Enter Email Address %d: [Just enter removes the entry]: ", index);
					fgets(str, NUMBER_LEN, stdin);
					string_len = strlen(str) - 1;

					if (str[string_len] == '\n')
						str[string_len] = '\0'; // set the end of userInput to null
					strcpy(address_book->list[person].email_addresses[index], str);
					break;
				default:
					break;
				}

			} while (opt != 0);
		}

		else
			opt = 0;

	} while (opt != 0);

	return e_success;
}

Status delete_contact(AddressBook *address_book)
{
	/* Add the functionality for delete contacts here */
	char str[80];
	char delete_char, confirmation;
	int target;
	int count = 0;
	int condition = 1;

	do
	{

		menu_header("Search Contact to Delete By:\n");

		printf("0. Back\n");
		printf("1. Name\n");
		printf("2. Phone No\n");
		printf("3. Email ID\n");
		printf("4. Serial No\n");

		int option = -1;
		option = get_option(NUM, "Please select an option: ");

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
				return e_no_match;
			}
			break;
		case e_third_opt:
			printf("Enter the Phone No: ");
			fflush(stdin);
			scanf("%[^\n]s", str);
			if (search(str, address_book, address_book->count, option, "", e_delete) != e_success)
			{

				return e_no_match;
			}
			break;
		case e_fourth_opt:
			printf("Enter the Email ID: ");
			fflush(stdin);
			scanf("%[^\n]s", str);
			if (search(str, address_book, address_book->count, option, "", e_delete) != e_success)
			{

				return e_no_match;
			}
			break;
		case e_fifth_opt:
			printf("Enter the Serial No: ");
			fflush(stdin);
			scanf("%[^\n]s", str);
			if (search(str, address_book, address_book->count, option, "", e_delete) != e_success)
			{
				return e_no_match;
			}
			break;
		default:
			return e_fail;
		}

		delete_char = get_option(CHAR, "Press: [s] = Select, [q] | Cancel: ");

		if (delete_char == 's')
		{
			printf("Select a serial Number (S.No) to Delete: ");
			fflush(stdout);
			scanf("%d", &target);
			target = target - 1;

			if (target < 0 || target >= address_book->count)
				return e_no_match;

			contact_confirmation(target, "Delete Contact:\n", address_book);

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
				condition = 0;
			}
		}
	} while (condition == 1);
	return e_success;
}