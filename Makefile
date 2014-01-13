PROG = prsigset
CFILES = prsigset.c

CFLAGS = -Wall -Werror

$(PROG): $(CFILES)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(PROG)
