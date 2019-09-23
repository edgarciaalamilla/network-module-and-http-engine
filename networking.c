/*
 * Copyright (c) 2018, Hammurabi Mendes.
 * License: BSD 2-clause
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>

#include "networking.h"

int create_server(int port) {
	return -1;
}

int accept_client(int accept_socket) {
	struct sockaddr_storage client_address;
	socklen_t client_length = sizeof(struct sockaddr_storage);

	int client_socket = accept(accept_socket, (struct sockaddr *) &client_address, &client_length);

	return client_socket;
}

void get_peer_information(int socket, char *host_string, int host_length, int *port) {
	int result;

	struct sockaddr_storage address;
	socklen_t length;

	result = getpeername(socket, (struct sockaddr *) &address, &length);

	if(result == -1) {
		perror("getpeername");

		return;
	}

	char port_string[16];

	result = getnameinfo((struct sockaddr *) &address, length, host_string, host_length, port_string, 16, NI_NUMERICHOST | NI_NUMERICSERV);

	*port = atoi(port_string);

	if(result != 0) {
		perror("getnameinfo");

		return;
	}
}
