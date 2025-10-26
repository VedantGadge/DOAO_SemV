/*
 * lcs.c - simplified Longest Common Subsequence (LCS) implementation in C
 * Reads two lines from stdin and prints the LCS and its length.
 *
 * Simple iterative DP with backtracking. Keeps memory usage reasonable
 * and code easy to understand for educational purposes.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 1000

/* Remove trailing newline characters from a string read by fgets */
static void strip_newline(char *s) {
	if (!s) return;
	size_t i = strlen(s);
	while (i > 0 && (s[i-1] == '\n' || s[i-1] == '\r')) {
		s[i-1] = '\0';
		--i;
	}
}

/* Compute LCS and return a newly-allocated string (caller frees it). */
char *compute_lcs(const char *X, const char *Y) {
	int m = (int)strlen(X);
	int n = (int)strlen(Y);

	/* Allocate DP table C of size (m+1)*(n+1) */
	int *C = malloc((m + 1) * (n + 1) * sizeof(int));
	/* Direction table for backtracking: '\\' = diagonal(match), '^' = up, '<' = left */
	char *B = malloc((m + 1) * (n + 1) * sizeof(char));
	if (!C || !B) {
		fprintf(stderr, "Memory allocation failed\n");
		free(C); free(B);
		return NULL;
	}

	#define IDX(i,j) ((i) * (n + 1) + (j))

	for (int i = 0; i <= m; ++i) C[IDX(i, 0)] = 0;
	for (int j = 0; j <= n; ++j) C[IDX(0, j)] = 0;

	for (int i = 1; i <= m; ++i) {
		for (int j = 1; j <= n; ++j) {
			if (X[i-1] == Y[j-1]) {
				C[IDX(i,j)] = C[IDX(i-1,j-1)] + 1;
				B[IDX(i,j)] = '\\'; /* match: diagonal */
			} else if (C[IDX(i-1,j)] >= C[IDX(i,j-1)]) {
				C[IDX(i,j)] = C[IDX(i-1,j)];
				B[IDX(i,j)] = '^'; /* move up */
			} else {
				C[IDX(i,j)] = C[IDX(i,j-1)];
				B[IDX(i,j)] = '<'; /* move left */
			}
		}
	}

	int len = C[IDX(m,n)];
	char *lcs = malloc((len + 1) * sizeof(char));
	if (!lcs) {
		fprintf(stderr, "Memory allocation failed\n");
		free(C); free(B);
		return NULL;
	}
	lcs[len] = '\0';

	/* Backtrack to build LCS from end to start */
	int i = m, j = n, k = len - 1;
	while (i > 0 && j > 0) {
		char dir = B[IDX(i,j)];
		if (dir == '\\') {
			lcs[k--] = X[i-1];
			--i; --j;
		} else if (dir == '^') {
			--i;
		} else { /* '<' */
			--j;
		}
	}

	free(C);
	free(B);
	return lcs;
}

int main(void) {
	char X[MAXLEN];
	char Y[MAXLEN];

	printf("Enter first string (max %d chars):\n", MAXLEN-1);
	if (!fgets(X, sizeof X, stdin)) return 0;
	printf("Enter second string (max %d chars):\n", MAXLEN-1);
	if (!fgets(Y, sizeof Y, stdin)) return 0;

	strip_newline(X);
	strip_newline(Y);

	char *lcs = compute_lcs(X, Y);
	if (!lcs) return 1;

	printf("\nLongest Common Subsequence: %s\n", lcs);
	printf("Length: %zu\n", strlen(lcs));

	free(lcs);
	return 0;
}

