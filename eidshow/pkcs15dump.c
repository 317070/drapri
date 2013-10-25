/*
 *  pkcs15dump.c
 *
 *  Copyright 2005 Bert Vermeulen <bert@biot.com>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <opensc.h>
#include <pkcs15.h>

#define APPLICATION      "pkcs15dump"
#define READERNUM        0
#define SLOTNUM          0


void list_objects(sc_pkcs15_object_t *objlist)
{
     sc_pkcs15_object_t *obj;

     printf("objectlist: (%x)\n", (unsigned int) objlist);
     obj = objlist;
     while(obj)
     {
	  printf("object: %s\n", obj->label);

	  obj = obj->next;
     }

}


int main(int argc, char **argv)
{
     sc_context_t *ctx;
     sc_card_t *card;
     sc_pkcs15_card_t *p15card;
     int res;

     res = sc_establish_context(&ctx, APPLICATION);
     if(res)
     {
	  printf("unable to establish context: %d\n", res);

	  return(1);
     }

     printf("connecting to %s\n", ctx->reader[READERNUM]->name);
     res = sc_connect_card(ctx->reader[READERNUM], SLOTNUM, &card);
     if(res)
     {
	  printf("unable to connect to card: %s\n", sc_strerror(res));

	  sc_release_context(ctx);

	  return(1);
     }

     res = sc_pkcs15_bind(card, &p15card);
     if(res < 0)
     {
	  printf("unable to bind to pkcs15 card: %s\n", sc_strerror(res));

	  sc_disconnect_card(card, 0);
	  sc_release_context(ctx);

	  return(1);
     }

     printf("app: %s\nflags 0x%x\n", p15card->label, p15card->flags);
     list_objects(p15card->obj_list);


     sc_pkcs15_unbind(p15card);


     printf("ok\n");

     sc_disconnect_card(card, 0);
     sc_release_context(ctx);

     return(0);
}

