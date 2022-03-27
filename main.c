#include <stdio.h>
//#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>

#include "address_book.h"
#include "address_book_fops.h"
#include "address_book_menu.h"

int main(void)
{
	AddressBook *address_book; 
	address_book = (AddressBook*) malloc(sizeof(AddressBook));
	address_book->list = (ContactInfo*) malloc(sizeof(ContactInfo));
	Status ret;

	/* Load the file from .csv file if any */
	ret = load_file(&address_book);

	if (ret == e_success)
	{
		/* Show all the available menu */
		ret = menu(&address_book);

		if (ret == e_success)
		{
			/* Save the entries */
			(&address_book);
		}
	}

	return 0;
}
