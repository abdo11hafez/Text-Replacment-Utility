#include <stdio.h>
#include <string.h>
FILE* open_file(char file_name[] )
{
   printf("Enter the filename to open for reading \n");
   scanf("%s", file_name);
   FILE *fptr1 = fopen(file_name, "r+");
   if (fptr1 == NULL)
    {
        printf("Cannot open file %s \n", file_name);
        return open_file(file_name);
    }
   return fptr1;
}

void scan_prameters (char word[],char new_word[] ,char *enable ,char *sensitivity)
{
    printf("Enter the word to search for in file \n");
    scanf("%s", word);

    printf("Enter the new word \n");
    scanf("%s", new_word);

    printf("Enter replacing mode (\"f\"->first    \"l\"->last    \"2\"->first&last     \"a\"->all ):");
    scanf(" %c", enable);

    printf("Enter sensitivity mode (\"i\"-> case insensitive   \"s\"-> case sensitive ):");
    scanf(" %c", sensitivity);


}



int occur_count (FILE * fptr1 ,char word[],char sensitivity)
{
    int i= 0 , sensitivity_enable =0;
    int word_length = strlen(word) ;
    int  ctr=0;
    char temp = fgetc(fptr1);
    switch (sensitivity)
        {
            case 'i' : sensitivity_enable=1; break;
            case 's' : sensitivity_enable=0; break;
        }

   while (temp != EOF)
 {
     i=0;

    if ( (temp == word[i]) || ((sensitivity_enable) && ( (temp == (word[i]+('a' - 'A'))) || (temp == (word[i]-('a' - 'A'))))))
        {   while (((temp == word[i]) || ((sensitivity_enable) && ( (temp == (word[i]+('a' - 'A'))) || (temp == (word[i]-('a' - 'A')))))) && (i < word_length))
            {
            i++;
            if (i == word_length) break ;
            temp = fgetc(fptr1);
            }
            if (i== word_length)
            {
                ctr++;
            }
        }
    else
        {
            temp = fgetc(fptr1);
        }
 }
    fclose(fptr1);
    return (ctr);
}



int replace_text(char filename [],FILE *fptr1 ,char word[] ,char new_word[], int occur , char enable ,char sensitivity)
{
    int first_enable=0 ,last_enable=0 ,all_enable=0 ,sensitivity_enable=0;
    switch (enable)
        {
            case 'f' : first_enable=1; break;
            case 'l' : last_enable =1; break;
            case 'a' : all_enable =1 ; break;
            case '2' : first_enable=1 ; last_enable =1; break;
        }
    switch (sensitivity)
        {
            case 'i' : sensitivity_enable=1; break;

        }


    printf("first=%d   last=%d    all=%d   sensitivity=%d \n",first_enable,last_enable,all_enable,sensitivity_enable);
    FILE *back_up = fopen("back_up.txt","w+");
    int word_length = strlen(word) ;
    int i= 0;
    int p ;
    int ctr = 0;
    char temp = fgetc(fptr1);

   while (temp != EOF)
 {
     i=0;
    if ((temp != word[i] && !sensitivity_enable) || (sensitivity_enable && ( (temp != word[i]+('a' - 'A')) && (temp != word[i])&& (temp != word[i]-('a' - 'A')))))
        {
         fputc(temp,back_up);
        }

    if ( (temp == word[i]) || ( sensitivity_enable && ( (temp == word[i]+('a' - 'A')) || (temp == word[i]-('a' - 'A')))))
        {   while (((temp == word[i]) || (sensitivity_enable && ( (temp == (word[i]+('a' - 'A'))) || (temp == (word[i]-('a' - 'A'))))))
              && i < word_length)
            {
            i++;
            if (i == word_length) break ;
            temp = fgetc(fptr1);
        }
      if (i== word_length)
       { ctr++ ;
         if (ctr==1 && first_enable == 1)
            {
             fputs(new_word,back_up);
            }
         else if (ctr == occur && last_enable == 1)
            {
             fputs(new_word,back_up);
            }
         else if(all_enable == 1)
            {
             fputs(new_word,back_up);
            }
         else
            {
               // fputs(word,back_up);
          fseek(fptr1,-(i),SEEK_CUR);
          for(p=0;p<i;p++)
          {
            temp = fgetc(fptr1);
            fputc(temp,back_up);
          }
            }
        }
      else
        { if (temp == 10) fseek(fptr1, -1 , SEEK_CUR);
          fseek(fptr1,-(i+1),SEEK_CUR);
          for(p=0;p<i;p++)
          {
            temp = fgetc(fptr1);
            fputc(temp,back_up);
          }
        }
    }
    temp = fgetc(fptr1);

}
    printf("--------------------------------------------------\n");
    printf("replacing finished and new file has been generated \n");
    printf("--------------------------------------------------\n");
    fclose(fptr1);
    fclose(back_up);
    printf("Do you want to create backup file ( y/ n) :");
    scanf(" %c", &temp);
    if(temp=='y') return (0) ;
    if(temp=='n')
    {
        remove(filename);
        rename("back_up.txt",filename);
        return (0);
    }
 return 0 ;
}

