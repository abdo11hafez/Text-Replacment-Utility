#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "replacment.h"


int main(void) {
    int occurences ;
    char filename[100] , word[100], new_word[100] , enable ,sensitivity ;
    FILE *fptr1 = open_file(filename);
    scan_prameters (word , new_word , &enable , &sensitivity);

    occurences = occur_count(fptr1,word, sensitivity);
    fptr1 = fopen(filename, "r+");  // reopen the file because occur_count closed it

    replace_text(filename ,fptr1 ,word ,new_word , occurences ,enable ,sensitivity);
    return 0;
    		}


