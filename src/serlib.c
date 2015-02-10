#include "serlib.h"
#include <at89x52.h>

char getchar(void)
{
    char c;
    while (!RI) ;		/* wait to receive */
    c = SBUF;		/* receive from serial */
    RI = 0;
    return c;
}

void putchar(const char c)
{
    while (!TI) ;		/* wait end of last transmission */
    TI = 0;
    SBUF = c;		/* transmit to serial */
}

int strlen(const char *str)
{
    const char *s;

    for (s = str; *s; ++s)
        ;
    return (s - str);
}
void putstr(const char* str)
{
    int len = strlen(str);
    char i;
    for ( i = 0; i < len; i++ ) {
        putchar(str[i]);
    }

}
void newline(const char* str)
{

    putstr("\r\n");
    putstr(str);
    putstr("\r\n");
}

int strlcpy(char *dst, const char *src, int siz)
{
	char *d = dst;
	const char *s = src;
	int n = siz;

	/* Copy as many bytes as will fit */
	if (n != 0) {
		while (--n != 0) {
			if ((*d++ = *s++) == '\0')
				break;
		}
	}

	/* Not enough room in dst, add NUL and traverse rest of src */
	if (n == 0) {
		if (siz != 0)
			*d = '\0';		/* NUL-terminate dst */
		while (*s++)
			;
	}

	return(s - src - 1);	/* count does not include NUL */
}

int strcmp(const char *s1, const char *s2)
{
	while (*s1 == *s2++)
		if (*s1++ == 0)
			return (0);
	return (*(unsigned char *)s1 - *(unsigned char *)--s2);
}

