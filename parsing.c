#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
	char buffer[1024];

	strcpy(buffer, "This is a ||| test");

	char *location = strcasestr(buffer, "|||");

	// Make the character at location be the null character
	*location = '\0';

	// Now print buffer
	printf("%s\n", buffer);

	// Print what follows the first pipe character
	// Note the pointer arithmetic: it will give you the address one byte after the original location
	printf("%s\n", location + 1);

	return 0;
}
