all: lib/libconnection_handler.so
	
lib/libconnection_handler.so: src/fantastic_connection_handler.o src/tcp_connection_handler.o lib
	g++ -std=c++11 -shared src/fantastic_connection_handler.o src/tcp_connection_handler.o -o lib/libconnection_handler.so

src/fantastic_connection_handler.o: src/fantastic_connection_handler.cpp
	g++ -std=c++11 -c -fPIC -I inc/ src/fantastic_connection_handler.cpp -o src/fantastic_connection_handler.o

src/tcp_connection_handler.o: src/tcp_connection_handler.cpp
	g++ -std=c++11 -c -fPIC -I inc/ src/tcp_connection_handler.cpp -o src/tcp_connection_handler.o

lib:
	mkdir lib

distclean: clean
	rm -rf lib

clean:
	rm -rf src/*.o

