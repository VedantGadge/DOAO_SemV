#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

static const int directions[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};

// Depth-first search. Returns true if word[idx..] can be found starting at board[i][j].
bool find_word(char **board, int i, int j, int n, int m, const char *word, int idx) {
	if (word[idx] == '\0')
		return true;
	if (i < 0 || j < 0 || i >= n || j >= m)
		return false;
	if (board[i][j] == '$' || board[i][j] != word[idx])
		return false;

	char temp = board[i][j];
	board[i][j] = '$'; // mark visited

	for (int d = 0; d < 4; ++d) {
		int ni = i + directions[d][0];
		int nj = j + directions[d][1];
		if (find_word(board, ni, nj, n, m, word, idx + 1)) {
			board[i][j] = temp; // restore before returning
			return true;
		}
	}

	board[i][j] = temp; // backtrack
	return false;
}

// Exist function: returns true if the word exists in the board following adjacency rules.
bool exist(char **board, int n, int m, const char *word) {
	if (!board || n == 0 || m == 0 || !word)
		return false;
	int len = strlen(word);
	if (len == 0)
		return true;

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (board[i][j] == word[0]) {
				if (find_word(board, i, j, n, m, word, 0))
					return true;
			}
		}
	}
	return false;
}

// Interactive program: show the board, then accept user words to search for.
int main(void) {
	// Sample board from classic examples
	const char *rows[] = {"ABCE", "SFCS", "ADEE"};
	int n = sizeof(rows) / sizeof(rows[0]);
	int m = strlen(rows[0]);

	// Make a mutable copy of rows (the algorithm mutates the board during search)
	char **board = malloc(n * sizeof(char*));
	if (!board) return 1;
	for (int i = 0; i < n; ++i) {
		board[i] = strdup(rows[i]);
		if (!board[i]) return 1;
	}

	// Show the board to the user
	printf("Board:\n");
	for (int i = 0; i < n; ++i) {
		printf("%s\n", board[i]);
	}

	char input[256];
	while (1) {
		printf("\nEnter a word to search (empty line to quit): ");
		if (!fgets(input, sizeof(input), stdin)) {
			// EOF or read error
			break;
		}
		// strip newline
		size_t L = strlen(input);
		if (L > 0 && input[L-1] == '\n') {
			input[--L] = '\0';
		}
		if (L == 0) break; // empty line => exit

		// Provide a fresh copy of the board because exist() mutates it
		char **copy = malloc(n * sizeof(char*));
		if (!copy) break;
		for (int i = 0; i < n; ++i) {
			copy[i] = strdup(board[i]);
			if (!copy[i]) {
				// free any allocated and break
				for (int k = 0; k < i; ++k) free(copy[k]);
				free(copy);
				copy = NULL;
				break;
			}
		}
		if (!copy) {
			fprintf(stderr, "Memory allocation failed.\n");
			break;
		}

		bool found = exist(copy, n, m, input);
		printf("Result: %s\n", found ? "FOUND" : "NOT FOUND");

		for (int i = 0; i < n; ++i) free(copy[i]);
		free(copy);
	}

	for (int i = 0; i < n; ++i) free(board[i]);
	free(board);
	return 0;
}

