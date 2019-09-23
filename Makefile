PROGRAM = webserver
OBJECTS = main.o clients_common.o http.o networking.o

webserver-clean: clean webserver

webserver: $(OBJECTS)
	clang -g -o webserver $(OBJECTS) -I.

%.o: %.c
	clang -g -c -o $@ -I. -Inet $<

clean:
	rm -f *.o webserver
