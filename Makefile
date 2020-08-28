CC = gcc
SRC= src
OBJ = obj
INCL= incl
LOCAL = false
OP_BASH =
SISTEMA := -D LINUX
CLEAN_COMMAND := rm -f
CLEAN_COMMAND_v2 = del
EXECUTABLE_NAME = lab2
OPTION_COMPILE = -DDEBUG -Wall

SOURCES := $(wildcard $(SRC)/*.c)
OBJECTS := $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SOURCES))

all: clean main
	$(eval LOCAL=true)
	@echo "-------------------------------------------------------"
	@echo "Ejecutable generado! Nombre: $(EXECUTABLE_NAME) "


main: $(OBJECTS)
	$(eval LOCAL=true)
	@echo "Generando ejecutable ..."
	($(CC) $^ -lm $(DEBUG_MODE) $(SISTEMA)  -o $(EXECUTABLE_NAME) -ljpeg && echo "[OK]") \
		||  (echo "[ERROR]" && exit 1; )

$(OBJ)/%.o: $(SRC)/%.c
	@echo "Generando archivos object de $@ ...."
	($(CC) -g $(DEBUG_MODE) $(SISTEMA)  -lm -I$(SRC) -c $< -o $@ && echo "[OK]") \
		||  (echo "[ERROR]" && exit 1; )
	$(eval LOCAL=true)

clean:
	$(eval LOCAL=true)
	@echo "Eliminando .out antiguos..."
	@echo >> rm.out

	(($(CLEAN_COMMAND) *.out || $(CLEAN_COMMAND_v2) *.out || $(CLEAN_COMMAND_v3) *.out ) \
		&& echo "[OK]") \
		||  (echo "[ERROR]" && exit 1; )

	@echo "Eliminando .o antiguos..."
	(cd $(OBJ) && echo >> rm.o )


	(cd $(OBJ) && ($(CLEAN_COMMAND) *.o || $(CLEAN_COMMAND_v2) *.o ) \
		&& echo "[OK]") \
		||  (echo "[ERROR]" && exit 1; ) \


	@echo "Limpieza de archivos antiguos completa!!"
	@echo "-------------------------------------------------------"

.SILENT: clean all make main $(OBJ)/%.o $(SOURCES) $(OBJECTS) install $(SRC)/%.c main-debug rm