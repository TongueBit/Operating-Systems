#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#define DELIM " "

//declared variables for the getline() function
char *line = NULL;
size_t len = 0;
ssize_t red;
char exval[6] = "exit\n";
char end[3] = "\0";
//



char *token; //used in parser function


int batch(FILE f) {
    /**
            This method takes a file and prints the contents until the EOF upon which it successfully exits
                        The actual version of this should execute the commands from the file
     */
    
    while(!feof(&f)) {
            red = getline(&line, &len, &f);
            printf("%s",line);
    }
    free(line); //line if NULL at start must be freed
    exit(0);
}

int parser(char *s) {
    /**
        This method takes a string and parses it by white space. It adds an string pointer to an array
     */
    
    while ((token = strsep(&s, DELIM)) != NULL) {
        if (!(isalpha(*token) == 0) || (ispunct(*token)) || (isdigit(*token))) {
            printf("%s\n", token);
            }
        }
        return 0;
}

int forker(char *line) {
    printf("-------main process-------\n");
    int rc = fork();
    if (rc == 0) {
        printf("we have forked\n");
        parser(line);
    }
    return 0;
    
    
}

int main(int argc, char  *argv[]) {

        if(argc > 1) {
            FILE *fp = fopen(argv[1], "r"); //returns the file address so it needs a pointer
            batch(*fp);
        }
    
        while(1) {
                printf("wish> "); //the extra space here is important
                red = getline(&line,  &len, stdin); //the reference read stores the size of what what typed
                
                if(strcmp(line, exval) == 0) {
                        free(line); //line if NULL at start must be freed
                        exit(0);
                }
                forker(line);
               
                                   
        }
}

