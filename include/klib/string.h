#ifndef KLIB_STRING_H
#define KLIB_STRING_H


// substring_searchSimple simplest substing search
// returns id of first matched char, -1 if no string found
int substring_searchSimple(char *source, char *sub);

int substring_searchKmp(char *source, char *sub);

int substring_searchBoyerMoore(char *source, char *sub);
#endif
