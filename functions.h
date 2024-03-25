#ifndef FUNCTIONS_HEADER
#define FUNCTIONS_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
//#include "debugmalloc_better_version.h"

#define STR_SIZE 20

// ==================== DEFINE WINDOWS OR LINUX FUNCTIONS ====================

#ifdef _WIN32
    #include <windows.h>
    #include <conio.h>
#else
    #include <curses.h>
    #include <unistd.h>
    #include <termios.h>
    #include <fcntl.h>
#endif

#ifdef _WIN32
    void goto_xy(int, int);
#endif

void cursor(int);
//terminal clear - on both windows & linux
void clear();
//wait millisecond - on both windows & linux
void sleep_ms(unsigned int);

// ==================== DEFINE LINKED LIST DEADLINE STRUCTURE ====================

//linked list deadline structure
typedef struct deadline 
{
    time_t time;
    char* title;
    char* place;
    char* note;
    unsigned int ok;
    struct deadline* next;
} deadline;

//linked list string structure
typedef struct stringList 
{
    char* string;
    struct stringList* next;
} stringList;

int calc_str_list_len(stringList*);

//ads new str to the list
void new_str(stringList**, char*);
//prints out buffered strings
void print_str(stringList*);
//free-s all the list
void free_str(stringList**);

//Returns 1 if they are the same
int same_title(deadline* List, char* Title);

//reads in a string dinamiclly allocating memory for it
char* read_line();
//reads uint - returns -1 if not valid
long read_int();
//prints out tm_time
void print_tm_time(struct tm*, unsigned int);
//print out deadline data
void print_dl(struct deadline*, int);
//prints out deadline with coundown
void str_cd_dl(struct deadline*, int, stringList** buffer);
//prints out rem time
void str_cd_time(time_t, stringList** buffer);
//prints out deadlines in specific order
void print_list(struct deadline*, int);
//shows deadlines with countdown
void str_cd_list(struct deadline*, int, stringList** buffer);
//deletes one deadline
void del_dl(struct deadline**, char*);
//finishes a deadline
void ok_dl(struct deadline**, char*);
//sets deadline to incomplete
void not_dl(struct deadline**, char*);
//edit deadline
void edit_dl(struct deadline**, char*);
//sort deadlines
struct deadline* merge(struct deadline*, struct deadline*);
struct deadline* mergeSort(struct deadline*);
//free allocated memory
void free_list(struct deadline*);
//adds new deadline item to linked list - list* must be NULL if no element
struct deadline* new_dl(struct deadline*);

//save linked list to a binary file
void save_file(const char*, deadline*);
// Function to read linked list from a binary file
deadline* read_file(FILE* file);

#endif