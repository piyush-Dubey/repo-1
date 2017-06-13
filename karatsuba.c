#include <stdio.h>
#include <string.h>
#include <stdlib.h>


// This functions appends c to s1 n times
char* append(char* s1, char c, int n)
{
	int i;
	int len = strlen(s1);
	char* s2 = malloc(sizeof(char*) * n);
	for(i = 0; i < n; i++)
	{
		s2[i] = c;
	}
	char* str = malloc(sizeof(char*) * (n + len));
	for(i = 0; i < len; i++)
		str[i] = s1[i];
	for(i; i < n + len; i++)
		str[i] = s2[i - len];
	for(i = 0; i < n + len; i++)
	{
		if(str[i] - '0' != 0)
			return str;
	}
	return "0";
}

// This function prepends c to s1 n times
char* prepend(char* s1, char c, int n)
{
	int len1 = strlen(s1), len = n + len1;
	int i;
	char* str = malloc(sizeof(char*) * len);
	for(i = 0; i < n; i++)
	{
		str[i] = c;
	}
	for(i; i < len; i++)
	{
		str[i] = s1[i - n];
	}
	return str;
}

// This function adds two strings which contain numbers and returns the sum as a string
char* add(char* s1, char* s2)
{
	int i;
	int carry = 0;
	int len1 = strlen(s1);
	int len2 = strlen(s2);
	if(len1 == 0 && len2 != 0)
		return s2;
	if(len2 == 0 && len1 != 0)
		return s1;
	if(len1 == 0 && len2 == 0)
		return "0";
	if(len1 > len2)
	{
		s2 = prepend(s2, '0', len1 - len2);
		len2 = len1;
	}
	if(len2 > len1)
	{
		s1 = prepend(s1, '0', len2 - len1);
		len1 = len2;
	}
	char* s = malloc(sizeof(char*) * (len1 + 1));

	for(i = len2 - 1; i >= 0; i--)
	{
		if((s1[i] - '0') + (s2[i] - '0') + carry >= 10)
		{
			s[i] = (((s1[i] - '0') + (s2[i] - '0') + carry) % 10) + '0';
			carry = ((s1[i] - '0') + (s2[i] - '0') + carry) / 10;
		}
		else
		{
			s[i] = ((s1[i] - '0') + (s2[i] - '0') + carry) + '0';
			carry = 0;
		}
	}
	i--;
	if(carry > 0)
	{
		char* head = malloc(sizeof(char*) * (len1 + 2));
		head[0] = carry + '0';
		for(i = 1; i < len1 + 2; i++)
			head[i] = s[i - 1];
		free(s);
		return head;
	}
	return s;
}

/* This function removes the front characters.
If the input string only consists of the character c, then
string str becomes "0".
*/
void rm_front_chars(char* str, char c)
{
	char *pr = str + 1, *pw = str;
	while(*pw == c && *pr)
	{
		*pw = *pr;
		pr++;
	}
	pw++;
	while(*pr)
	{
		*pw = *pr;
		pr++;
		pw++;
	}
	*pw = '\0';
}

// len1 >= len2
char* subtract(char* s1, char* s2)
{
	int i;
	int len1 = strlen(s1);
	int len2 = strlen(s2);
	if(len1 != len2)
		s2 = prepend(s2, '0', len1 - len2);
	int len = len2 = len1;
	int borrow = 0;
	char* str = malloc(sizeof(char*) * len1);
	for(i = len2 - 1; i >= 0 ; i--)
	{
		if(s1[i] >= s2[i] + borrow)
		{
			str[i] = ((s1[i] - s2[i]) - borrow) + '0';
			borrow = 0;
		}
		else
		{
			str[i] = ((s1[i] -s2[i]) + 10 - borrow) + '0';
			borrow = 1;
		}
	}
	rm_front_chars(str, '0');
	return str;
}

// Function to implement karatsuba algorithm

char* karatsuba(char* s1, char* s2)
{
	int len1 = strlen(s1);
	int len2 = strlen(s2);
	char* str = malloc(sizeof(char*) * 2);
	if(len1 == 0 || len2 == 0)
		return "0";
	if(len1 > len2)
	{
		s2 = prepend(s2, '0', len1 - len2);
		len2 = len1;
	}
	if(len2 > len1)
	{
		s1 = prepend(s1, '0', len2 - len1);
		len1 = len2;
	}
	int lena, lenb, lenc, lend, i;
	if(len1 == 1 && len2 == 1)
	{
		str[0] = 0;
		sprintf(str, "%d", (s1[0] - '0') * (s2[0] - '0'));
		rm_front_chars(str, '0');
		return str;
	}
	else
	{
		lena = len1 / 2;
		lenc = len2 / 2;
		lenb = len1 - lena;
		lend = len2 - lenc;
		char* a = malloc(sizeof(char*) * lena);
		char* b = malloc(sizeof(char*) * lenb);
		char* c = malloc(sizeof(char*) * lenc);
		char* d = malloc(sizeof(char*) * lend);
		
		for(i = lenb - 1; i >= 0 ; i--)
		{
			b[i] = s1[len1 - lenb + i];
		}
		for(i; i < lena; i++)
		{
			a[i] = s1[i];
		}
		for(i = lend - 1; i >= 0 ; i--)
		{
			d[i] = s2[len2 - lend + i];
		}
		for(i; i < lenc; i++)
		{
			c[i] = s2[i];
		}
		
		char* ac = malloc(sizeof(char*) * (lena + lenc));
		ac = karatsuba(a, c);
		char* ac_append = malloc(sizeof(char*) * (len1 + len2));
		ac_append = append(ac, '0', lenb + lend);
		char* bd = malloc(sizeof(char*) * (lenb + lend));
		bd = karatsuba(b, d);
		char* abcd = malloc(sizeof(char*) * (lena + lenc + 2));
		char* apb = malloc(sizeof(char*) * (lena + 1));
		char* cpd = malloc(sizeof(char*) * (lenc + 1));
		apb = add(a,b);
		cpd = add(c,d);
		abcd = karatsuba(apb, cpd);
		char* gauss = malloc(sizeof(char*) * (lena + lenc + 2));
		char* acpbd = malloc(sizeof(char*) * (lena + lenc + 1));
		acpbd = add(ac,bd);
		gauss = subtract(abcd, acpbd);
		char* gauss_append = malloc(sizeof(char*) * (len1 / 2 + lena + lenc + 2));
		gauss_append = append(gauss, '0', lenb);
		char* ans = malloc(sizeof(char*) * (len1 + len2));
		ans = add(ac_append, gauss_append);
		ans = add(ans, bd);
		return ans;
	}
}

int main(void)
{
	printf("3141592653589793238462643383279502884197169399375105820974944592 * 2718281828459045235360287471352662497757247093699959574966967627 = ");
	printf("%s\n", karatsuba("3141592653589793238462643383279502884197169399375105820974944592", "2718281828459045235360287471352662497757247093699959574966967627"));
}
