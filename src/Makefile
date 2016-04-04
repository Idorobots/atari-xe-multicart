CC = cl65
CFLAGS = -v -tatari 

LINKER_CONFIG = menu.cfg
LDFLAGS = -C$(LINKER_CONFIG)

export CC65_INC = /usr/share/cc65/include/
export CA65_INC = /usr/share/cc65/asminc/
export LD65_LIB = /usr/share/cc65/lib/
export LD65_OBJ = /usr/share/cc65/lib/
export LD65_CFG = /usr/share/cc65/cfg/

SRC = menu.c

TARGET = menu.bin

all: $(TARGET)

$(TARGET):
	$(CC) $(CFLAGS) $(SRC) $(LDFLAGS) -m $(TARGET).map -o $@

.PHONY: clean
clean:
	$(RM) $(TARGET).map
	$(RM) $(TARGET)
	$(RM) *.o
