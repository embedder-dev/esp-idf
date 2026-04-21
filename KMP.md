# KMP (Knuth-Morris-Pratt) String Matching Algorithm

The KMP algorithm searches for occurrences of a pattern within a text in **O(n + m)** time, where `n` is the length of the text and `m` is the length of the pattern. It avoids redundant comparisons by precomputing a longest proper prefix-suffix (LPS) table.

## How It Works

1. **Build the LPS table** — For each position in the pattern, compute the length of the longest proper prefix that is also a suffix. This tells the algorithm how far back to fall when a mismatch occurs, without re-scanning characters already matched.
2. **Search** — Walk through the text, advancing the pattern pointer on matches and falling back using the LPS table on mismatches.

## Implementation in C

```c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * Build the Longest Proper Prefix which is also Suffix (LPS) array.
 *
 * lps[i] = length of the longest proper prefix of pattern[0..i]
 *          that is also a suffix of pattern[0..i].
 */
static void kmp_build_lps(const char *pattern, int m, int *lps)
{
    int len = 0; /* length of the previous longest prefix suffix */
    lps[0] = 0;

    int i = 1;
    while (i < m) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

/**
 * Search for all occurrences of `pattern` in `text` using KMP.
 * Prints every index where a match begins.
 *
 * Returns the number of matches found.
 */
int kmp_search(const char *text, const char *pattern)
{
    int n = (int)strlen(text);
    int m = (int)strlen(pattern);

    if (m == 0) {
        return 0;
    }

    int *lps = (int *)malloc(m * sizeof(int));
    if (!lps) {
        return -1;
    }

    kmp_build_lps(pattern, m, lps);

    int count = 0;
    int i = 0; /* index into text    */
    int j = 0; /* index into pattern */

    while (i < n) {
        if (text[i] == pattern[j]) {
            i++;
            j++;
        }

        if (j == m) {
            printf("Pattern found at index %d\n", i - j);
            count++;
            j = lps[j - 1];
        } else if (i < n && text[i] != pattern[j]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }

    free(lps);
    return count;
}

/* Example usage */
int main(void)
{
    const char *text    = "ABABDABACDABABCABAB";
    const char *pattern = "ABABCABAB";

    printf("Text:    %s\n", text);
    printf("Pattern: %s\n\n", pattern);

    int matches = kmp_search(text, pattern);
    printf("\nTotal matches: %d\n", matches);

    return 0;
}
```

## Compile and Run

```bash
gcc -Wall -Wextra -o kmp KMP.c
./kmp
```

Expected output:

```
Text:    ABABDABACDABABCABAB
Pattern: ABABCABAB

Pattern found at index 9

Total matches: 1
```

## Complexity

| Phase      | Time   | Space  |
|------------|--------|--------|
| LPS build  | O(m)   | O(m)   |
| Search     | O(n)   | O(1)   |
| **Total**  | O(n+m) | O(m)   |
