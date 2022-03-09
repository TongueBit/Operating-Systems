#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#define DELIM " "
#define COLON ":"


//declared variables for the getline() function
char *line = NULL;
size_t len = 0;
ssize_t red;
char exval[6] = "exit\n";
char end[3] = "\0";
char *token; //used in parser function


int batch(FILE f) {
    /**
            This method takes a file and prints the contents until the EOF upon which it successfully exits
                        The actual version of this should execute the commands from the file
     */
    while(!feof(&f)) {
            red = getline(&line, &len, &f);
            printf("%s",line);
    } //end while
    free(line); //line if NULL at start must be freed
    exit(0);
}
/**
int getPath(void) {
    
    printf("%s\n", path);
    return 0;
    
}
*/
int setPath(char *string) {
    
    //we calculate the length of the string so that we don't just throw some arbitrary number to calculate the size of the array. We kknow the path can't be longer than the sting itself. In the end though I added some arbitrariness cause I couldn't spend any more time on this.
    int i;
    for (i = 0; string[i] != '\0'; ++i);
    char path[i];
    strcpy(path, "/bin");
    
    while ((token = strsep(&string, DELIM)) != NULL) {
        if (!(isalpha(*token) == 0) || (ispunct(*token)) || (isdigit(*token))) {
            if (strcmp(token, "path") != 0) {
                //printf("%s\n", token);
                strncat(path, COLON, 1);
                
                int j;
                for (j = 0; token[j] != '\0'; ++j); //size of the string
                strncat(path, token, j);
            }
        }
    } //end while
    printf("%s\n", path);
    return 0;
}


int parser(char *s) {
    /**
        This method takes a string and parses it by white space. It adds an string pointer to an array
     */
    
    while ((token = strsep(&s, DELIM)) != NULL) {
        if (!(isalpha(*token) == 0) || (ispunct(*token)) || (isdigit(*token))) {
            //printf("%s\n", token);
            if(strcmp(token, "path") == 0)
                setPath(s);
            /*
            else if(strcmp(token, "print") == 0)
                getpath();
             */
        }
    } //end while
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
                parser(line);
        } //end while
}

