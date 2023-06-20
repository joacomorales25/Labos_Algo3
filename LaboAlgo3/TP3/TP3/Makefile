CXX = g++
CXXFLAGS = -Wall -g -std=c++14

EJ1 = ej1
EJ2 = ej2


all :sources tests

sources:
	$(CXX) $(CXXFLAGS) -o ej1.o $(EJ1).cpp
	$(CXX) $(CXXFLAGS) -o ej2.o $(EJ2).cpp

tests:
	$(CXX) $(CXXFLAGS) -o ej1_prueba_log_n.o $(EJ1)_prueba_log_n.cpp
	$(CXX) $(CXXFLAGS) -o ej1_prueba_n2.o $(EJ1)_prueba.cpp

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -cpp $< -o $@

clean:
	rm -f *.o
