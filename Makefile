CC=g++ --std=c++11
CFLAGS= \
	-I. \
	-I/usr/include/libxml2
DEPS=
LIBS=-lxml2
OBJ= \
	dialog_entry.o \
	dialog_manager.o \
	main.o 
OUTPUT=dialog_manager_test

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(OUTPUT): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: debug
debug: CFLAGS += -D DEBUG -g
debug: $(OUTPUT)

.PHONY: clean
clean:
	rm -f *.o $(OUTPUT)