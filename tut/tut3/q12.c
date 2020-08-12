#include <stdio.h>
#include <stdlib.h>

// if no command line arguments, then read from standard input, output to standard output
// for other arguments, open the filename, read from the file, output to standard output
// for argument '-', read from standard input instead 

int main(int agvc, char **argv) {
    int num;

    // use appropriate location if you are using MacOS or Linux
    FILE *fptr = fopen(argv[1],"w");

    if(fptr == NULL) {
        printf("Error!\n");
        exit(1);
    }

    printf("Enter num: \n");
    scanf("%d",&num);

    fprintf(fptr,"%d\n",num);
    fclose(fptr);

    return 0;
}
