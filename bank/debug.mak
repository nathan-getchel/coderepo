project_debug: user_interface_debug.o llist_debug.o
	g++ -o project_debug user_interface_debug.o llist_debug.o

user_interface_debug.o: user_interface.cpp
	g++ -o user_interface_debug.o -ansi -pedantic-errors -Wall -D DEBUGMODE -c user_interface.cpp

llist_debug.o: llist.cpp
	g++ -o llist_debug.o -ansi -pedantic-errors -Wall -D DEBUGMODE -c llist.cpp