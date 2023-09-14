CXXFLAGS:=-g -Wall -I/usr/local/include/
OBJ= main.o list.o book.o

all: $(OBJ)
	$(CXX) -o book $(OBJ) $(CXXFLAGS) $(LDFLAGS)

%.o: %.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

clean:
	rm $(OBJ) book -f *.o
