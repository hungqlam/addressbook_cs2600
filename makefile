#Build the addressbook program
CC=gcc
DEBUGFLAGS=-g

all: addressbook

addressbook: address_book_fops.c address_book_fops.h address_book_menu.c address_book_menu.h address_book.h main.c
	$(CC) address_book_fops.c address_book_fops.h address_book_menu.c address_book_menu.h address_book.h main.c -o addressbook

debug:
	$(CC) $(DEBUGFLAGS) address_book_fops.c address_book_fops.h address_book_menu.c address_book_menu.h address_book.h main.c -o d_addressbook

clean:
	del address_book_fops.h.gch address_book_menu.h.gch address_book.h.gch addressbook.exe d_addressbook.exe