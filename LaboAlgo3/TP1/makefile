CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -Werror -pedantic -O2 -Wno-sign-compare

all : ej1 ej2 ej3
# Build rule for executable ej1
ej1: cuadrado_magico.cpp
	$(CXX) $(CXXFLAGS) cuadrado_magico.cpp -o ej1

# Build rule for executable ej2
ej2: operaciones.cpp
	$(CXX) $(CXXFLAGS) operaciones.cpp -o ej2

# Build rule for executable ej3
ej3: actividades.cpp
	$(CXX) $(CXXFLAGS) actividades.cpp -o ej3

# Clean rule
clean:
	rm -f ej1 ej2 ej3

