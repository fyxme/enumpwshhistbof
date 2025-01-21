CC = x86_64-w64-mingw32-gcc
STRIP = x86_64-w64-mingw32-strip
RM = rm -vf

BIN=./bin
SRC=./src

.PHONY: all clean
all: enumpwshhist.bof.o 

enumpwshhist.bof.o: $(SRC)/*.c $(SRC)/*.h

%.bof.o : $(SRC)/%.c
	$(CC) -DBOF $(CFLAGS) $(TARGET_ARCH) -c -o $(BIN)/$@ $<

clean:
	@$(RM) $(BIN)/*.o 2>/dev/null || true
	@$(RM) $(BIN)/*.exe 2>/dev/null || true

