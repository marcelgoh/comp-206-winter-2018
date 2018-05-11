#include "A4_sort_helpers.h"

// Function: read_all() 
// Provided to read an entire file, line by line.
// No need to change this one.
void read_all( char *filename ){
    
    FILE *fp = fopen( filename, "r" );
    int curr_line = 0;
	
    while( curr_line < MAX_NUMBER_LINES && 
           fgets( text_array[curr_line], MAX_LINE_LENGTH, fp ) )
    {
        curr_line++;
    }
	
    text_array[curr_line][0] = '\0';
    fclose(fp);
}

// Function: read_all() 
// Provided to read only the lines of a file staring with first_letter.
// No need to change this one.
void read_by_letter( char *filename, char first_letter ){

    FILE *fp = fopen( filename, "r" );
    int curr_line = 0;
    text_array[curr_line][0] = '\0';
	
    while( fgets( text_array[curr_line], MAX_LINE_LENGTH, fp ) ){
        if( text_array[curr_line][0] == first_letter ){
            curr_line++;
        }

        if( curr_line == MAX_NUMBER_LINES ){
            sprintf( buf, "ERROR: Attempted to read too many lines from file.\n" );
            write( 1, buf, strlen(buf) );
            break;
        }
    }
	
    text_array[curr_line][0] = '\0';
    fclose(fp);
}

// YOU COMPLETE THIS ENTIRE FUNCTION FOR Q1.
void sort_words( ){
    char temp[MAX_LINE_LENGTH];
    int index;

    for (int i=0; text_array[i][0] != '\0'; ++i) {
        strcpy(temp, text_array[i]);
        index = i;
        for (int j=i+1; text_array[j][0] != '\0'; ++j) {
            if (strcmp(text_array[j], temp) < 0) {
                strcpy(temp, text_array[j]);
                index = j;
            }
        }
        if (index != i) {
            strcpy(text_array[index], text_array[i]);
            strcpy(text_array[i], temp);
        }
    }

}

// YOU COMPLETE THIS ENTIRE FUNCTION FOR Q2.
int initialize( ){
    /* create temporary file to dump outputs */
    FILE *temp_file = fopen("temp_file.txt", "w");
    if (!temp_file) {
        printf("Error creating text file.\n");
        return -1;
    }
    fclose(temp_file);

    /* create 27 semaphores: one for finalize() and one for each letter */
    sem_unlink("/final_sem");
    sem_t *creator = sem_open("/final_sem", O_CREAT | O_EXCL, 00700, 0);
    sem_close(creator);
    unsigned int value;
    char sem_name[16];
    for (char letter='a'; letter<='z'; ++letter) {
        value = (letter == 'a') ? 1 : 0;
        sprintf(sem_name, "/%c_sem", letter);
        sem_unlink(sem_name);
        creator = sem_open(sem_name, O_CREAT | O_EXCL, 00700, value);
        sem_close(creator);
    }

    return 0;
}

// YOU MUST COMPLETE THIS FUNCTION FOR Q2 and Q3.   
int process_by_letter( char* input_filename, char first_letter ){
    /* create and initialize semaphore pointers and names */
    sem_t *this_ptr;
    sem_t *next_ptr;
    char this_name[16];
    char next_name[16];
    sprintf(this_name, "/%c_sem", first_letter);
    strcpy(next_name, this_name);
    if (first_letter != 'z') {
        ++(next_name[1]);
    } else {
        sprintf(next_name, "/final_sem");
    }
    
    /* opens semaphore that belongs to the process and waits */
    this_ptr = sem_open(this_name, O_CREAT);
    sem_wait(this_ptr);

    /* 
     * Code from Q2:
     * sprintf( buf, "This process will sort the letter %c.\n",  first_letter );
     * write(1,buf,strlen(buf)); 
     */

    /* Q3: sort all words that start with first_letter */
    read_by_letter( input_filename, first_letter );
    sort_words( );
    
    /* open temporary file and append array contents to file */
    FILE *temp_file = fopen("temp_file.txt", "a");
    if (!temp_file) {
        printf("Error opening text file.\n");
        return -1;
    }
    for (int i=0; text_array[i][0] != '\0'; ++i) {
        fprintf(temp_file, "%s", text_array[i]);
    }
    fclose(temp_file);

    /* opens next semaphore, posts it, then closes own semaphore */
    next_ptr = sem_open(next_name, O_CREAT);
    sem_post(next_ptr);
    sem_close(this_ptr);
    sem_close(next_ptr);

    return 0;
}

// YOU COMPLETE THIS ENTIRE FUNCTION FOR Q2 and Q3.
int finalize( ){
    /* open semaphore and wait for processes to finish */
    sem_t *this_ptr = sem_open("/final_sem", O_CREAT);
    sem_wait(this_ptr);

    /* print contents of temp_file to standard out */
    FILE *temp_file = fopen("temp_file.txt", "r");
    if (!temp_file) {
        printf("Error opening text file.\n");
        return -1;
    }
    char c;
    while ((c = getc(temp_file)) != EOF) {
        putchar(c);
    }
    fclose(temp_file);

    /* required to pass comparison test */
    printf("Sorting complete!\n");

    /* unlink and close all semaphores */
    sem_unlink("/final_sem");
    sem_close(this_ptr);
    char sem_name[16];
    for (char letter='a'; letter<='z'; ++letter) {
        sprintf(sem_name, "/%c_sem", letter);
        this_ptr = sem_open(sem_name, O_CREAT);
        sem_unlink(sem_name);
        sem_close(this_ptr);
    }

    return 0;
}

