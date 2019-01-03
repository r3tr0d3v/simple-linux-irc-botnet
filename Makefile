BUILD  ?= build/
SRC    ?= src/
CFLAGS ?= -Wall -g -Os


all: pre $(BUILD)backdoor

pre:
	mkdir -p $(BUILD)

$(BUILD)backdoor: $(BUILD)main.o $(BUILD)parser.o $(BUILD)random.o $(BUILD)protocol.o $(BUILD)rat_functions.o $(BUILD)sckt.o
	gcc $(BUILD)main.o $(BUILD)parser.o $(BUILD)random.o $(BUILD)protocol.o $(BUILD)rat_functions.o $(BUILD)sckt.o -o $(BUILD)backdoor

$(BUILD)main.o: $(SRC)main.c $(SRC)parser.h $(SRC)protocol.h $(SRC)random.h $(SRC)rat_functions.h $(SRC)sckt.h
	gcc -c $(SRC)main.c -o $(BUILD)main.o  

$(BUILD)parser.o: $(SRC)parser.c $(SRC)parser.h $(SRC)protocol.h $(SRC)rat_functions.h
	gcc -c $(SRC)parser.c -o $(BUILD)parser.o

$(BUILD)random.o: $(SRC)random.c $(SRC)random.h
	gcc -c $(SRC)random.c -o $(BUILD)random.o

$(BUILD)protocol.o: $(SRC)protocol.c $(SRC)protocol.h $(SRC)sckt.h
	gcc -c $(SRC)protocol.c -o $(BUILD)protocol.o

$(BUILD)rat_functions.o: $(SRC)rat_functions.c $(SRC)rat_functions.h $(SRC)sckt.h
	gcc -c $(SRC)rat_functions.c -o $(BUILD)rat_functions.o

$(BUILD)sckt.o: $(SRC)sckt.c $(SRC)sckt.h
	gcc -c $(SRC)sckt.c -o $(BUILD)sckt.o

clean:
	rm -rf $(BUILD)

.PHONY: pre all clean
