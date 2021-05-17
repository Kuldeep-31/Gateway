CC=g++
CFLAGS = -I.
DEPS = gateway.h
OBJ = Main.o gateway.o

TARGET= gateway

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ) -pthread
        
#%.o: %.c $(DEPS)
#       $(CC) -c -o $@ $< $(CFLAGS)
#               
#               #gateway: $(OBJ)
#       $(CC) -o $@ $< $(CFLAGS)
#               
.PHONY: clean
       
clean:
	rm -f $(OBJ) $(TARGET) *~

