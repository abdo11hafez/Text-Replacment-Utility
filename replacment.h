FILE* open_file(char file_name[] );

void scan_prameters (char word[],char new_word[] ,char *enable ,char *sensitivity);

int occur_count (FILE * fptr1 ,char word[],char sensitivity);

int replace_text(char filename[],FILE *fptr1 ,char word[] ,char new_word[], int occur,char enable ,char sensitivity);
