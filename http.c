/*
 * Copyright (c) 2018, Hammurabi Mendes.
 * License: BSD 2-clause
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "http.h"

int header_complete(char *buffer, int buffer_length) {
	buffer[buffer_length] = '\0';

	if(strstr(buffer, "\r\n\r\n")) {
		return 1;
	}

	return 0;
}

int header_parse(char *buffer, int buffer_length, char *filename, int filename_length, char *protocol, int protocol_length, int *content_length) {
	if(!buffer || !filename || !protocol || !content_length) {
		fprintf(stderr, "Please provide non-null buffer/filename/protocol/content-length\n");
		return -1;
	}

	if(buffer_length < 128 || filename_length < 128 || protocol_length < 16) {
		fprintf(stderr, "Please provide buffer/filename strings with sizes >= 128 and a protocol string with size >= 16\n");

		return -1;
	}
	char* request; 
	char* rest;
	char* temp;

	buffer[buffer_length] = '\0';

	temp = strcasestr(buffer, "/") + 1;
	rest = strcasestr(temp, " ");
	*rest = '\0';
	rest++;
	strcpy(filename, temp);

	temp = strcasestr(rest, "HTTP");
	rest = strcasestr(temp, "\r\n");
	*rest = '\0';
	rest++;
	strcpy(protocol, temp);

	temp = (strcasestr(rest, "Content-Length:"));
	if(temp != NULL){
		temp += 16;
		rest = strcasestr(temp, "\r");
		*rest = '\0';
		*(content_length) = atoi(temp);
		return METHOD_PUT;
	}
	return METHOD_GET;
}

void fill_reply_200(char *buffer, char *filename, char *protocol, int filesize) {
	sprintf(buffer, "%s 200 OK\r\nFilename: %s\r\nContent-Length: %d\r\n\r\n", protocol, filename, filesize); //have to show file content
}

void fill_reply_201(char *buffer, char *filename, char *protocol) {
	sprintf(buffer, "%s 201 Created\r\n\r\n", protocol);
}

void fill_reply_403(char *buffer, char *filename, char *protocol) {
	sprintf(buffer, "%s", protocol);
	sprintf(buffer, "403 Not Found\n");
	sprintf(buffer, "Filename: ");
	sprintf(buffer, "%s",filename);
	sprintf(buffer, "\n\n");
	sprintf(buffer, "<html> <p>Error 403! You do not have permission to access.</p> </html>");
}

void fill_reply_404(char *buffer, char *filename, char *protocol) {

	sprintf(buffer, "%s", protocol);
	sprintf(buffer, "404 Not Found\n");
	sprintf(buffer, "Filename: ");
	sprintf(buffer, "%s",filename);
	sprintf(buffer, "\n\n");
	sprintf(buffer, "<html> <p>Error 404! The page does not exist.</p> </html>");
}
