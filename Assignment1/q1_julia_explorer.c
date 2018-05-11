#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int replace(char *string, char *oldSubstr, char *newSubstr);

int main(int argc, char *argv[]) {
    /* ensures correct number of arguments */
    if (argc != 4) {                           
        printf("Error: Usage: %s filename float1 float2\n)", argv[0]);
        return -1;
    }

    char *script;
    int fileLength = 0;

    /* opens file from input arguments */
    FILE *file = fopen(argv[1], "r"); 
    if (file == NULL) {
        printf("Error: bad file\n");
        return -1;
    }

    /*
     * computes length of file, allocates that much memory to a char pointer, 
     * ensures the string will be null-terminated, then stores the file
     * contents in the char array
     */
    fseek(file, 0L, SEEK_END);
    fileLength = ftell(file);
    rewind(file);           
    script = malloc((fileLength + 1) * (sizeof(char)));
    fread(script, sizeof(char), fileLength, file);
    script[fileLength] = '\0';         
    fclose(file);
    
    /* checks if file contains required tags */
    if (strstr(script, "#A#") == NULL || strstr(script, "#B#") == NULL) {
        printf("Error: bad file\n");
        return -1;
    }

    /* checks if float arguments are valid */
    float a = atof(argv[2]);
    float b = atof(argv[3]);
    if (a == 0.0 || b == 0.0) {
        printf("Error: bad float arg\n");
        return -1;
    }

    char argA[32], argB[32], buffer[32];
    sprintf(buffer, "%.6f", a);
    strcpy(argA, buffer);
    sprintf(buffer, "%.6f", b);
    strcpy(argB, buffer);

    /* ensures the float arguments actually contain a floating point */
    if (!(strchr(argA, '.'))) {
        strcat(argA, ".0");
    }
    if (!(strchr(argB, '.'))) {
        strcat(argB, ".0");
    } 
    
    /* 
     * replace tags with strings representing floats and print result
     * to standard out
     */
    char output[fileLength + 32];
    strcpy(output, script);
    replace(output, "#A#", argA);
    replace(output, "#B#", argB);
    printf("%s", output);
    return 0;
}

/*
 * replace: finds first instance of oldSubStr in string and replaces it 
 * with newSubstr
 */
int replace(char *string, char *oldSubstr, char *newSubstr) {
    char buffer[strlen(string) + strlen(newSubstr)];
    char *location = strstr(string, oldSubstr);
    if (location == NULL) {
        return -1;
    }
    strncpy(buffer, string, location - string);
    buffer[location - string] = '\0';
    sprintf(buffer + (location - string), "%s%s", newSubstr, location + strlen(oldSubstr));
    string[0] = '\0';
    strcpy(string, buffer);
    return 0;
}
