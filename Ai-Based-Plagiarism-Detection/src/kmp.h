#ifndef KMP_H
#define KMP_H

void compute_lps(char pattern[], int lps[]);
int kmp_search(char text[], char pattern[]);

#endif
