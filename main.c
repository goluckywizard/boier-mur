#include <stdio.h>
#include "boier-mur.h"

int main(int argc, char *argv[]) {
    FILE *inpf;
    if (argc > 1)
    {
        inpf = fopen(argv[1], "rt");

        if (NULL == inpf)
        {
            printf("Cannot open file %s\n", argv[1]);
            return 1;
        }
    }
    else
    {
        inpf = stdin;
    }

    BoierMur(inpf);

    printf("\n");
    if (inpf != stdin)
        fclose(inpf);
    return 0;
}
