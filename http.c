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
	// if(!buffer || !filename || !protocol || !content_length) {
	// 	fprintf(stderr, "Please provide non-null buffer/filename/protocol/content-length\n");

	// 	return -1;
	// }

	// if(buffer_length < 128 || filename_length < 128 || protocol_length < 16) {
	// 	fprintf(stderr, "Please provide buffer/filename strings with sizes >= 128 and a protocol string with size >= 16\n");

	// 	return -1;
	// }

	char* rest;

	buffer[buffer_length] = '\0';

	filename = strcasestr(buffer, "/") + 1;
	filename_length = strlen(filename);	//are we given filename_length?

	rest = strcasestr(filename, " ");
	*rest = '\0';
	rest++;

	protocol = strcasestr(rest, "HTTP");
	protocol_length = strlen(protocol);

	rest = strcasestr(protocol, " ");
	*rest = '\0';
	rest++;

	//extending for part II
	// char* host = strcasestr(rest, "Host:");
	// int host_length = strlen(host);

	// rest = strcasestr(host, " ");
	// *rest = '\0';
	// rest++;

	printf("%s\n", filename);
	printf("%s\n", protocol);
	// printf("%s\n", host);

	return -1;
}

void fill_reply_200(char *buffer, char *filename, char *protocol, int filesize) {
	sprintf(buffer, "%s 200 OK\r\nFilename: %s\r\nContent-Length: %d\r\n\r\n", protocol, filename, filesize);
}

void fill_reply_201(char *buffer, char *filename, char *protocol) {
	sprintf(buffer, "%s 201 Created\r\n\r\n", protocol);
}

void fill_reply_403(char *buffer, char *filename, char *protocol) {
}

void fill_reply_404(char *buffer, char *filename, char *protocol) {
}


int main(){
	//for testing
	char header[128] = "PUT /filename.txt HTTP/1.1 Host: localhost:9000";
	int buffer_length;
	char* filename;
	int filename_length;
	char* protocol;
	int protocol_length;
	int* content_length;
	header_parse(header, 128, filename, filename_length, protocol, protocol_length, content_length);
}
