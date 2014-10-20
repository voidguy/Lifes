
cc=g++ -g -Wall -std=c++11
obj=main
LDFLAGS=-pthread

$(obj): Main.o Server.o
	$(cc) $^ -o $@ $(LDFLAGS)

Main.o: Main.cpp
	$(cc) -c $< -o $@

Server.o: Server.cpp Server.h 
	$(cc) -c $< -o $@

clean:
	rm -rf *.o $(obj)
