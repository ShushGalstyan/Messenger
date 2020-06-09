SOURCES := ClientThread.cpp MyThread.cpp Packaging.cpp TCPServer.cpp Main.cpp
LDFLAGS=-pthread 
OBJECTS := $(patsubst %.cpp,%.o,$(SOURCES))
DEPENDS := $(patsubst %.cpp,%.dep,$(SOURCES))
server : $(OBJECTS)
	g++ -Wall -pedantic -pthread -std=c++0x  $^ -o $@
%.o : %.cpp
	g++ $(LDFLAGS) -std=c++0x  -c $< -o $@
%.dep : %.cpp
	g++ -MM %< -MT “$@ $(patsubst %.dep,%.o,$@)” -o $@
-include $(DEPENDS)

clean:
	rm -f *.o

