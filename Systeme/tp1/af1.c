/********************************
 * Fichier bomb.c
 * Livre "Programmation d'applications système sous Linux"
 *
 * P. Alain, J. Chevelu, S. Le Maguer, V. Thion, B. Vozel
 *
 ********************************/
#include <stdio.h>		/* printf */
#include <unistd.h>		/* fork */
#include <stdlib.h>		/* exit */
#include <sys/errno.h>		/* errno */
#include <string.h>		/* strerror */

int main(void)
{
	int fork_return_value;


	do {
		fork_return_value = fork();
		if (fork_return_value == 0) {
			printf("%d\n", getpid());
		}
	} while (1);

	return 0;
}
