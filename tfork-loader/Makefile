PROG=loader
SRC=loader.c
CC=gcc

.PHONY: module
module: loader

CFLAGS = -std=gnu99 -fpie -rdynamic -g -fno-omit-frame-pointer -fno-stack-protector -O2
LDFLAGS =

$(PROG):
	$(CC) $(CFLAGS) -pie $(SRC) -o $@ $(LDFLAGS)

objdump: $(PROG)
	objdump --source $(PROG) > /tmp/objdump.txt && vim /tmp/objdump.txt

clean:
	rm -f $(PROG)
