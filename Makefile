# Variables
CXX = g++
CXXFLAGS = -Wall -Wextra -Werror
EXEC = prog
SRCS = $(wildcard *.cpp) # Tous les fichiers .cpp
OBJ = $(SRCS:.cpp=.o) # Remplace .cpp par .o

# Règle par défaut : générer l'exécutable
all: $(EXEC)

# Lien des fichiers objets pour créer l'exécutable
# Créer l'exécutable à partir des fichiers objets
$(EXEC) : $(OBJ)
	$(CXX) $(OBJ) -o $(EXEC)


# Règles de compilation pour chaque fichier .cpp en .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<


# Règle pour exécuter le programme
run: $(EXEC)
	./$(EXEC)


# Clean pour supprimer les fichiers objets et l'exécutable
clean:
	rm -f $(OBJ) $(EXEC)
