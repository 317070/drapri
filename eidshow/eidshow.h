/*
 *  eidshow.h
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


struct tlvfile {
     int tag;
     char *data;
     struct tlvfile *next;
};

char *card_id_rn_labels[] = {
     "Sexual preference",
     "Card number",
     "Chip number",
     "Card validity date begin",
     "Card validity date end",
     "Card delivery municipality",
     "National Number",
     "Name",
     "2 first names",
     "3rd first name initial",
     "Nationality",
     "Birth location",
     "Birth date",
     "Sex",
     "Noble condition",
     "Document type",
     "Special status",
     "Photo hash"
};

char *document_type_labels[] = {
     "Second class citizen",
     "Belgian citizen",
     "European community citizen",
     "non European community citizen",
     "bootstrap card",
     "habilitation/machtigings card"
};

char *status_labels[] = {
     "No status",
     "White cane",
     "extended minority",
     "White cane + extended minority",
     "Yellow cane",
     "Yellow cane + extended minority"
};

char *card_id_address_labels[] = {
     "GSM number",
     "Street + number",
     "Postal code",
     "Municipality"
};



