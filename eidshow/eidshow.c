/*
 *	eidshow.c
 *
 *	Copyright 2005 Bert Vermeulen <bert@biot.com>
 *
 *	This program is free software; you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation; either version 2 of the License, or
 *	(at your option) any later version.
 *
 *	This program is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with this program; if not, write to the Free Software
 *	Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA	02111-1307	USA
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <opensc.h>

#include "eidshow.h"


#define APPLICATION	"eidshow"
#define SLOTNUM			0
#define MAX_BUFSIZE	65535


int get_picture(sc_card_t *card, unsigned char *buf)
{
	struct sc_path path;
	sc_file_t *ef;
	int res;

	sc_format_path("3f00df014035", &path);
	res = sc_select_file(card, &path, &ef);
	if (!res && ef->type == SC_FILE_TYPE_WORKING_EF && ef->ef_structure == SC_FILE_EF_TRANSPARENT) {
		printf("file id %.4x size %d\n", ef->id, ef->size);
		res = sc_read_binary(card, 0, buf, MAX_BUFSIZE, 0);
		if (res < 0) {
		 printf("read file failed: %s\n", sc_strerror(res));
		 return(0);
		}

	}

	sc_file_free(ef);

	return(res);
}


struct tlvfile *read_tlvfile(sc_card_t *card, char *fileid)
{
	struct tlvfile *tlvfile, *tf, *record;
	struct sc_path path;
	sc_file_t *ef;
	int res, size;
	unsigned char buf[MAX_BUFSIZE], *p, *sz, *next;

	sc_format_path(fileid, &path);
	res = sc_select_file(card, &path, &ef);
	if (res < 0) {
		printf("select file failed: %s\n", sc_strerror(res));
		return(NULL);
	}

	res = sc_read_binary(card, 0, buf, MAX_BUFSIZE, 0);
	if (res < 0) {
		printf("read file failed: %s\n", sc_strerror(res));
		return(NULL);
	}

	tlvfile = tf = NULL;
	p = buf;
	while (*p) {
		sz = p + 1;
		size = 0;
		while (*sz == 255) {
			size += *sz;
			sz++;
		}
		size += *sz;
		next = sz + 1 + size;

		record = malloc(sizeof(struct tlvfile));
		record->tag = *p;
		record->data = malloc(size+1);
		memcpy(record->data, sz+1, size);
		record->data[size] = 0;
		record->next = NULL;

		if (tf)
			tf->next = record;
		else
			tlvfile = record;

		tf = record;

		p = next;
	}

	sc_file_free(ef);

	return(tlvfile);
}


void dump_tlvfile(struct tlvfile *tf, char **labelset)
{
	struct tlvfile *r;

	r = tf;
	while (r) {
		printf("%3d	%s\t%s\n", r->tag, labelset[r->tag], r->data);

		r = r->next;
	}

}


void free_tlvfile(struct tlvfile *tf)
{
	struct tlvfile *r, *next;

	r = tf;
	while (r) {
		next = r->next;
		free(r->data);
		free(r);

		r = next;
	}

}


int main(int argc, char **argv)
{
	struct tlvfile *tf;
	FILE *outfile;
	sc_context_t *ctx;
	sc_card_t *card;
	int reader, res, size;
	unsigned char picture[65535];

	if (argc == 3 && !strcmp(argv[1], "-r"))
		reader = strtol(argv[2], NULL, 10);
	else
		reader = 0;

	res = sc_establish_context(&ctx, APPLICATION);
	if (res) {
		printf("unable to establish context: %d\n", res);

		return(1);
	}

	printf("r %d\n", reader);
	printf("connecting to %s\n", ctx->reader[reader]->name);
	res = sc_connect_card(ctx->reader[reader], SLOTNUM, &card);
	if (res) {
		printf("unable to connect to card: %s\n", sc_strerror(res));

		sc_release_context(ctx);

		return(1);
	}

	size = get_picture(card, picture);
	printf("got %d bytes\n", size);
	if ( (outfile = fopen("picture.jpg", "w")) ) {
		fwrite(picture, size, 1, outfile);
		fclose(outfile);
	}

	tf = read_tlvfile(card, "3f00df014031");
	dump_tlvfile(tf, card_id_rn_labels);
	free_tlvfile(tf);
	printf("\n");

	tf = read_tlvfile(card, "3f00df014033");
	dump_tlvfile(tf, card_id_address_labels);
	free_tlvfile(tf);

	sc_disconnect_card(card, 0);
	sc_release_context(ctx);

	return(0);
}

