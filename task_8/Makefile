CC = gcc
LD = gcc

CFLAGS = -fopenmp -c
LDFLAGS = -fopenmp

OBJPATH = ./obj

SRCC = main.c

OBJC = $(SRCC:%.c=$(OBJPATH)/%.o)
HEAD = 

EXECUTABLE_WINDOWS = run.exe
EXECUTABLE_LINUX = run.out

linux: $(OBJPATH) $(SRCC) $(EXECUTABLE_LINUX)

windows: $(OBJPATH) $(SRCC) $(EXECUTABLE_WINDOWS)

$(OBJPATH):
	@mkdir $@

$(EXECUTABLE_LINUX): $(OBJC)
	@echo "LINKING:"
	$(LD) $(LDFLAGS) $(OBJC) -o  $@

$(EXECUTABLE_WINDOWS): $(OBJC)
	@echo "LINKING:"
	$(LD) $(LDFLAGS) $(OBJC) -o  $@

$(OBJPATH)/%.o: %.c $(HEAD)
	@echo "COMPILING:"
	$(CC) $(CFLAGS) $< -o $@

.PHONY: clean

clean:
	rm -rf $(OBJPATH)
