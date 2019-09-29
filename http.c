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

	buffer[buffer_length] = '\0';

	filename = strcasestr(rest, "/") + 1;

	rest = strcasestr(filename, " ");
	*rest = '\0';
	rest++;

	protocol = strcasestr(rest, "HTTP");

	rest = strcasestr(protocol, " ");
	*rest = '\0';
	rest++;


	char* content_length_label = strcasestr(rest, "Content-Length:");
	if(content_length_label != NULL){
		content_length_label += 16;
		char* rest = strcasestr(content_length_label, " ");
		*rest = '\0';
		
		//should be fine now
		content_length = (void*) (uintptr_t) atoi(content_length_label);
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
	//use sprintf instead;
	sprintf(buffer, "%s", protocol);
	sprintf(buffer, "403 Not Found\n");
	sprintf(buffer, "Filename: ");
	sprintf(buffer, "%s",filename);
	sprintf(buffer, "\n\n");
	//not sure how to add html stuff
}

void fill_reply_404(char *buffer, char *filename, char *protocol) {

	sprintf(buffer, "%s", protocol);
	sprintf(buffer, "404 Not Found\n");
	sprintf(buffer, "Filename: ");
	sprintf(buffer, "%s",filename);
	sprintf(buffer, "\n\n");
	//not sure how to add html stuff

}


// int main(){
// 	//for testing
// 	char header[128];
// 	strcpy(header, "PUT /filename.txt HTTP/1.1 Host: localhost:9000 User-Agent: curl/7.54.0 Accept: */* Content-Length: 14 Expect: 100-continue ");

// 	int buffer_length;
// 	char* filename;
// 	int filename_length; 
// 	char* protocol;
// 	int protocol_length;
// 	int* content_length;
// 	header_parse(header, 128, filename, filename_length, protocol, protocol_length, content_length);
// }
