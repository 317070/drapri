CC		= gcc
DEBUG		= -g
CFLAGS		= -Wall -lopensc -I/usr/include/beid/ -I/usr/include/beid/opensc
SHARED		= -shared 
DESTDIR 	= /
prefix  	= /usr
bindir  	= $(prefix)/bin
sysconfdir	= /etc

all: pkcs15dump

eidshow: eidshow.c

pkcs15dump: pkcs15dump.c


clean:
	rm -f eidshow pkcs15dump*.o

