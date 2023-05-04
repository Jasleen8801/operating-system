/****************************************************
    FORK3.C
*****************************************************

Made by: 	 Jasleen Kaur
Roll NO.:    102118064
Group:       BS-3
Course No:   UCT401
Course Name: Operating Systems
Thapar Institute of Engineering and Technology, Patiala

****************************************************/

/* fork3.c
 *   Illustrate the use of fork() to create a child process.
 *   The child process will print "Hello world!".
 *
 *  Note:  This program will not work on some systems.

****************************************************/

// C++ code for the above program

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
    if (fork() && fork()) {
        printf("Hello world!\n");
    }
    printf("Bye world!\n");
    return 0;
}

/****************************************************
To compile: gcc -o output/fork3 fork3.c
To run: ./output/fork3

OUTPUT of above program:-
Bye world!  
Hello world!
Bye world!  
Bye world! 

*****************************************************/
