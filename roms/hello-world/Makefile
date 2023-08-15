
ROOT = .

include $(ROOT)/config.mk

#_________________________________________________________________________


ASLISTING    = -alh

HELLO_OBJS   = src/crt0.o  src/hello.o src/vectors.c 

all:hello.bin 

welcome monitor.bin boot.bin: CFLAGS += -mpcrel

welcome:
	$(AS) -m68000 -o welcome.elf src/welcome.s
	$(OBJCOPY) -O binary welcome.elf welcome.bin

hello.bin:	$(HELLO_OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) --entry=_start -Thello.ld -o $@.elf $^
	$(CC) $(CFLAGS) $(LDFLAGS) --entry=_start -Thello.ld -Wl,--oformat=binary -o $@ $^

#_________________________________________________________________________ generale rules

%.a: $^
	$(AR) rc $@ $^
	$(RANLIB) $@

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

%.o: %.s
	$(AS) $(ASFLAGS) -c -o $@ $<

clean:
	find . \( -name "*.o" -or -name "*.a" -or -name "*.bin" -or -name "*.elf" -or -name "*.load" \) -delete -print




