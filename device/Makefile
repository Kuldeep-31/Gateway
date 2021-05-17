CC=g++
CFLAGS = -I.
DEPS = device.h
OBJ = Main.o device.o

TARGET= device

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)
        
#%.o: %.c $(DEPS)
#       $(CC) -c -o $@ $< $(CFLAGS)
#               
#               #gateway: $(OBJ)
#       $(CC) -o $@ $< $(CFLAGS)
#               
.PHONY: clean
                       
clean:
	rm -f $(OBJ) $(TARGET) *~

