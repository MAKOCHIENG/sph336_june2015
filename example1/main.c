#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main (int argc , char* argv[])
/*arg c is used to show the number of inputs  one put when running the program.
eg ./main.o will give an output of 1 while ./main.o lexy Andati will give an output
of 3 because you have input 3 things while  running the executable file*/
/* in c language char* means a string*/
{
//int a= atoi(argv[1]);
//printf("The value of a was %d \n", a);
//printf("argc = %d, %s\n", argc, argv[argc-3]);
printf("The value of argc is %d value of argv[1] %s and integer value of argv[1] is  \n", argc, argv[1]);
return 0;
}

