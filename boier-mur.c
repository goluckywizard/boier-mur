#include "boier-mur.h"
#define BUF_SIZE 1000
void createTable (char *pattern, size_t *table)
{
    size_t len = 0;
    while ((unsigned char)pattern[len] != 0)
    {
        len++;
    }
    len -= 1;
    for (int i = 0; i < 256; ++i)
    {
        table[i] = len;
    }
    for (size_t i = 0; i <= len - 2; ++i)
    {
        table[(unsigned char)pattern[i]] = len - i - 1;
    }
}

void find(size_t length, size_t *local_pos, size_t *position, char *text, char *pattern, size_t table[256], size_t size)
{
    size_t pat_index = 0;
    while ((*local_pos < size))
    {
        if (text[(int)(*local_pos - pat_index)] == pattern[(int)(length - pat_index)])
        {
            printf("%zu ", (*position - pat_index) + 1);
            //printf("%c %c\n", text[*local_pos - pat_index], pattern[length - pat_index]);
            pat_index++;
        }
        else
        {
            printf("%zu ", (*position - pat_index) + 1);
            //printf("%c %c ", text[*local_pos - pat_index], pattern[length - pat_index]);
            //*position += table[(int)(*local_pos - pat_index)];
            //*local_pos += table[(int)(*local_pos - pat_index)];
            *position += table[(unsigned char)text[(*local_pos)]];
            //printf("%c %c %Iu\n", text[*local_pos], pattern[length], table[(int)text[(*local_pos)]]);
            *local_pos += table[(unsigned char)text[(*local_pos)]];
            pat_index = 0;
        }
        if (pat_index == length + 1)
        {
            *position += table[(unsigned char)text[(*local_pos)]];
            *local_pos += table[(unsigned char)text[(*local_pos)]];
            pat_index = 0;
        }
    }
}

void BoierMur(FILE *input) {
    char pattern[20];
    size_t table[256] = {0};
    char text[BUF_SIZE];
    memset(text, 0, BUF_SIZE);
    //size_t temp = 0;
    //while ((pattern[temp] = fgetc(input)) != '\n')
    //    temp++;
    if (fgets(pattern, 20, input) == NULL)
    {
        printf("bad pattern");
        exit(1);
    }
    createTable(pattern, table);
    size_t length = 0;
    while (pattern[length] != 0)
    {
        length++;
    }
    length -= 2;
    //printf("%Iu\n", length);
    //char k = '\xe0';
    //printf("%d ", (unsigned char)k);
    /*for (int i = 0; i < 256; ++i)
    {
        if (table[i] != length + 1)
        {
            printf("%d %zu\n", i, table[i]);
        }
    }*/
    size_t position = length;
    size_t size;
    //size = fread(text, 1, BUF_SIZE, input);
    //printf("%s", pattern);
    do
    {
        //char temp_buff[BUF_SIZE / 2] = {0};
        size = fread(text, 1, BUF_SIZE, input);
        //printf("hui %Iu hui ", size);
        //shift(text, temp_buff);
        size_t local_pos = position % (BUF_SIZE);
        //printf("%Iu\n", size);
        find(length, &local_pos, &position, text, pattern, table, size);
    }
    while (size > 0);
}
