#include <stdio.h>
#include <stdlib.h>
#include <string.h>




//#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <ctype.h>
#include <stdbool.h>


#include "address_book.h"

Status load_file(AddressBook *address_book)
{
	int ret;


	const int SIZE = 50;

	/*
	 * Check for file existance
	 */
	// ret = access(DEFAULT_FILE, F_OK);  // <unistd.h> on UNIX
	struct stat buffer;
	ret = stat(DEFAULT_FILE, &buffer);
	;
	if (ret == 0) // File has been detected
	{
		/*
		 * Do the neccessary step to open the file
		 * Do error handling
		 */
		address_book->fp = fopen(DEFAULT_FILE, "a+");
		if (address_book->fp == NULL) // Handle file open error
		{
			fprintf(stderr, "File open error(%d): %s\n", errno, strerror(errno));
			fclose(address_book->fp);
			return e_fail;
		}
		else
		{
			address_book->list = (ContactInfo *)calloc(SIZE, sizeof(ContactInfo));
			FILE *ptr = fopen(DEFAULT_FILE, "r");
			char buffer[400]; // Line size is 352 + delimiters
			int count = 0;
			const int FIELDS = NAME_COUNT + PHONE_NUMBER_COUNT + EMAIL_ID_COUNT;

			while (fgets(buffer, sizeof(buffer), ptr))
			{
				int number_count = 0;
				int email_count = 0;
				char *line = strtok(buffer, NEXT_ENTRY);	// Line
				char *info = strtok(line, FIELD_DELIMITER); // Info

				ContactInfo contact;
				for (int i = 0; i < FIELDS; i++)
				{
					if (i == 0)
					{
						strcpy(contact.name[0], info);
					}
					else if (i > 0 && i <= 5)
					{
						strcpy(contact.phone_numbers[number_count], info);
						number_count++;
					}
					else
					{
						strcpy(contact.email_addresses[email_count], info);
						email_count++;
					}
					info = strtok(NULL, FIELD_DELIMITER); // delimiter
				}
				contact.si_no = count;
				address_book->list[count] = contact;
				count++;
			}
			// Close file pointer
			address_book->count = count;
			fclose(ptr);
			fclose(address_book->fp);
		}


	}
	else
	{
		/* Create a file for adding entries */

		address_book->fp = fopen(DEFAULT_FILE, "a");
		address_book->count = 0;
		address_book->list = (ContactInfo *)calloc(SIZE, sizeof(ContactInfo));

		fclose(address_book->fp);
	}

	return e_success;
}

Status save_file(AddressBook *address_book)
{
	/*
	 * Write contacts back to file.
	 * Re write the complete file currently


	 */
  


	address_book->fp = fopen(DEFAULT_FILE, "w");

	if (address_book->fp == NULL)
	{
		return e_fail;
	}


	int count = 0;
	int number_count = 0;
	int email_count = 0;
	while (count < address_book->count)
	{
		fprintf(address_book->fp, "%s,", address_book->list[count].name[0]);
		number_count = 0;
		email_count = 0;
		while (number_count < PHONE_NUMBER_COUNT)
		{
			fprintf(address_book->fp, "%s,", address_book->list[count].phone_numbers[number_count]);
			number_count++;
		}
		while (email_count < (EMAIL_ID_COUNT - 1))
		{
			fprintf(address_book->fp, "%s,", address_book->list[count].email_addresses[email_count]);
			email_count++;
		}
		fprintf(address_book->fp, "%s\n", address_book->list[count].email_addresses[EMAIL_ID_COUNT - 1]);
		count++;
	}



	fclose(address_book->fp);

	return e_success;
}
