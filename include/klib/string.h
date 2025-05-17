#ifndef KLIB_STRING
#define KLIB_STRING


// substring_searchSimple simplest substing search
// returns id of first matched char, -1 if no string found
int substring_searchSimple(char *source, char *sub);

int substring_searchKmp(char *source, char *sub);

int substring_searchBoyerMoore(char *source, char *sub);
#endif
