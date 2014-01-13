/*
 * prsigset.c: tool for printing out a sigset_t.
 */

#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

void prsigset(FILE *, sigset_t *);

int
main(int argc, char *argv[])
{
	int i;
	char *end;
	union {
		sigset_t set;
		unsigned int sigbits[4];
	} uset;

	if (argc == 1) {
		fprintf(stderr, "usage: %s word1 [word2 [word3 [word4]]]\n",
		    argv[0]);
		fprintf(stderr, "prints signals masked by the sigset_t with "
		    "uint words 1, 2, 3, 4\n"
		    "(dumped from MDB or DTrace)\n");
		return (2);
	}

	sigemptyset(&uset.set);
	for (i = 0; i < 4 && i < argc - 1; i++) {
		uset.sigbits[i] = strtoul(argv[i + 1], &end, 16);
		if (*end != '\0') {
			(void) fprintf(stderr, "arg %d is malformed: %s\n",
			    i + 1, argv[i + 1]);
			return (1);
		}
	}

	prsigset(stdout, &uset.set);
	return (0);
}

void
prsigset(FILE *fp, sigset_t *set)
{
	int i;
	char signame[SIG2STR_MAX];

	for (i = 1; i <= MAXSIG; i++) {
		sig2str(i, signame);
		(void) fprintf(fp, "%d  SIG%s\n", sigismember(set, i), signame);
	}
}
