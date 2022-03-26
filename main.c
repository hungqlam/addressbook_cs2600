#include <stdio.h>
//#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>

#include "address_book.h"
#include "address_book_fops.h"
#include "address_book_menu.h"

int main(void)
{
	AddressBook address_book;
	ContactInfo clist[2];
	char *cptr = clist[0].name[0];
	char name[32] = "Nick Parsley";
	char phone[32] = "909-512-1213";
	char email[32] = "nparsley@adi.uk";
	strcpy(cptr, name);
	cptr = cptr + sizeof(clist[0].name[0]);
	//printf("Size of name array: %i\n", (char)sizeof(clist[0].name));
	strcpy(cptr, phone);
	cptr += sizeof(clist[0].phone_numbers);
	//printf("Size of phone array: %i\n", sizeof(clist[0].phone_numbers));
	strcpy(cptr, email);
	cptr += sizeof(clist[0].email_addresses);
	*cptr = 65;
	cptr += sizeof(clist[0].si_no);
	char name2[32] = "Jack Timothy";
	char phone2[32] = "909-112-1234";
	char email2[32] = "jtimothy@adi.uk";
	strcpy(cptr, name2);
	cptr += sizeof(clist[0].name);
	strcpy(cptr, phone2);
	cptr += sizeof(clist[0].phone_numbers);
	strcpy(cptr, email2);
	cptr += sizeof(clist[0].email_addresses);
	*cptr = 71;
	address_book.count = 2;
	address_book.list = clist;
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
