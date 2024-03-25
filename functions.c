#include "functions.h"

int kbhit(void)
{
    #ifdef _WIN32
    return _kbhit();
    #else
    struct termios oldt, newt;
    int ch;
    int oldf;
    // Save the current terminal settings
    tcgetattr(STDIN_FILENO, &oldt);

    // Set the terminal to non-blocking mode
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    // Set the file descriptor for stdin to non-blocking
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    // Check for input
    ch = getchar();

    // Restore the terminal settings and file descriptor
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
    #endif
}
int getch()
{
    #ifdef _WIN32
    return _getch();
    #else
    return getchar();
    #endif
}
void clear()
{
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}
void sleep_ms(unsigned int milisecond)
{
    #ifdef _WIN32
        Sleep(milisecond);
    #else
        sleep((int)milisecond/1000);
    #endif
}

void new_str(stringList** buffer, char* input)
{
    stringList* head = (*buffer);
    unsigned int size = strlen(input) + 1;

    if((*buffer) == NULL)
    {
        (*buffer) = (stringList*)malloc(sizeof(stringList));
        (*buffer)->next = NULL;
        (*buffer)->string = (char*)malloc(sizeof(char)*size);
        memset((*buffer)->string, 0, size);
        memcpy((*buffer)->string, input, size);
    }
    else
    {
        while (head->next != NULL)
        {
            head = head->next;
        }
        head->next = (stringList*)malloc(sizeof(stringList));
        head->next->next = NULL;
        head->next->string = (char*)malloc(sizeof(char)*size);
        memset(head->next->string, 0, size);
        memcpy(head->next->string, input, size);
    }
    return;
}
//calculates all the lenght of the stringList
int calc_str_list_len(stringList *list) {
    int length = 0;
    while (list != NULL) {
        // Check if the string is not NULL
        if (list->string != NULL) {
            // Iterate through each character in the string
            for (int i = 0; list->string[i] != '\0'; i++) {
                length++;
            }
        }
        // Move to the next node in the linked list
        list = list->next;
    }
    return length;
}
//prints out buffered strings
#ifdef _WIN32
    void goto_xy(int x, int y)
    {
        COORD coord;
        coord.X=x;
        coord.Y=y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    }
    void cursor(int on)
    {
        if(on)
        {
            CONSOLE_CURSOR_INFO cursorInfo;
            GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
            // Save the initial cursor state
            cursorInfo.dwSize = 1;
            cursorInfo.bVisible = TRUE;
            SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
        }
        else
        {
            CONSOLE_CURSOR_INFO cursorInfo;
            GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
            // Save the initial cursor state
            cursorInfo.dwSize = 1;
            cursorInfo.bVisible = FALSE;
            SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
        }
    }
#else
        void cursor(int on)
        {
            if(on) printf("\e[?25h");  // ANSI escape code to show the cursor
            else printf("\e[?25l");  // ANSI escape code to hide the cursor
            fflush(stdout);
        }
#endif



void print_str(stringList* buffer)
{
    unsigned int size = calc_str_list_len(buffer);
    char* big_buffer = (char*)malloc(sizeof(char)*(size + 1));
    memset(big_buffer, 0, size + 1);
    while (buffer != NULL)
    {
        strcat(big_buffer, buffer->string);
        buffer = buffer->next;
    }

    #ifdef _WIN32
        goto_xy(0,0);
        printf("%s", big_buffer);
    #else
        clear();  // Clear the screen
        mvprintw(0, 0, "%s", big_buffer);  // Print the current line
        refresh();  // Update the screen
    #endif

    free(big_buffer);
    return;
}
//free-s all the list
void free_str(stringList** buffer)
{
    stringList* tmp;
    while ((*buffer) != NULL)
    {
        tmp = (*buffer)->next;
        free((*buffer)->string);
        free(*buffer);
        *buffer = tmp;
    }
    return;
}



int same_title(deadline* List, char* Title)
{
    while (List != NULL)
    {
        if (!strcmp(List->title, Title))
        {
            return 1;
        }
        List = List->next;
    }
    return 0;
}

//1. command - new deadline
char* read_line()
{
    //SET
    size_t bufferSize = STR_SIZE;
    size_t length = 0;
    char curChar = '\0';
    char* input = (char*)malloc(sizeof(char)*bufferSize);
    if (input==NULL)
    {
        perror("Error allocating memory!");
        exit(EXIT_FAILURE);
    }
    memset(input, 0, bufferSize);
    
    //GET INPUT
    while ((curChar = getchar()) != '\n' && curChar != '\0' && curChar != EOF)
    {
        if(length < bufferSize -1)
        {
            input[length++] = curChar;
        }
        else
        {
            bufferSize*=2;
            char* temp = (char*)realloc(input, bufferSize);
            if (temp == NULL)
            {
                perror("Error allocating memory!");
                free(input);
                exit(EXIT_FAILURE);
            }
            
            input = temp;
            input[length++]=curChar;
        }
    }

    //TERMINATING STRING
    input[length] = '\0';
    
    //REALLOC FOR MEMORY EFFICIENCY
    size_t ret_size = length + 1;
    char* ret_input = (char*)malloc(sizeof(char)*ret_size);
    memcpy(ret_input, input, ret_size);
    free(input);

    //FINISH FUNCTION
    return ret_input;
}
long read_int()
{
    char* str = read_line();
    char* endptr;
    long num = strtol(str, &endptr, 10);
    
    if (*endptr == '\0')
    {
        free(str);
        return num;
    }
    else
    {
        free(str);
        return -1;
    }
}
void print_tm_time(struct tm* time, unsigned int is_sec)
{
    if(is_sec)
    {
        printf("%0004d.%02d.%02d. %02d:%02d:%02d", time->tm_year+1900, time->tm_mon+1, time->tm_mday, time->tm_hour, time->tm_min, time->tm_sec);
    }
    else
    {
        printf("%0004d.%02d.%02d. %02d:%02d", time->tm_year+1900, time->tm_mon+1, time->tm_mday, time->tm_hour, time->tm_min);
    }

}
void print_dl(struct deadline* DeadLine, int all)
{
    struct tm* time = gmtime(&DeadLine->time);
    if(all)
    {
        if(DeadLine->ok == 1)
        {
            printf("\tOK\t");
        }
        else 
        {
            printf("\t X\t");
        }
    }
    else printf("\t");
    printf("%04d.%02d.%02d. %02d:%02d\t", time->tm_year+1900, time->tm_mon+1, time->tm_mday, time->tm_hour, time->tm_min);
    printf("%-15s\t%-15s\t%s", DeadLine->title, DeadLine->place, DeadLine->note);
}
void str_cd_dl(struct deadline* DeadLine, int all, stringList** buffer)
{
    time_t currentTime;
    time(&currentTime);

    if(all)
    {
        if(DeadLine->ok == 1)
        {
            new_str(buffer, "\tOK\t");
        }
        else
        {
            new_str(buffer, "\t X\t");
        }
    }
    else
    {
        new_str(buffer, "\t");
    }
    str_cd_time(DeadLine->time - currentTime - 3600, buffer);   //We added 3600 to set it OK
    unsigned int size = 1 + strlen(DeadLine->title) + 1 + strlen(DeadLine->place) + 1 + strlen(DeadLine->note) + 100;
    char* dl_str = (char*)malloc(sizeof(char)*size);
    memset(dl_str, 0, size);
    sprintf(dl_str, "\t%-15s\t%-15s\t%s", DeadLine->title, DeadLine->place, DeadLine->note);
    new_str(buffer, dl_str);
    free(dl_str);
}
void str_cd_time(time_t remTime, stringList** buffer) {
    int remainingYears, remainingMonths, remainingDays, remainingHours, remainingMinutes, remainingSeconds;

    // Calculate remaining time components
    remainingYears = remTime / (365 * 24 * 60 * 60);
    remTime %= (365 * 24 * 60 * 60);

    remainingMonths = remTime / (30 * 24 * 60 * 60); // Assuming a month is approximately 30 days
    remTime %= (30 * 24 * 60 * 60);

    remainingDays = remTime / (24 * 60 * 60);
    remTime %= (24 * 60 * 60);

    remainingHours = remTime / (60 * 60);
    remTime %= (60 * 60);

    remainingMinutes = remTime / 60;
    remainingSeconds = remTime % 60;

    if(remTime < 0)
    {
        char* new1 = (char*)malloc(sizeof(char)*(100));
        sprintf(new1, "- %04d.%02d.%02d. %02d:%02d:%02d",
           -remainingYears, -remainingMonths, -remainingDays,
           -remainingHours, -remainingMinutes, -remainingSeconds);
        new_str(buffer, new1);
        free(new1);
    }
    else
    {
        char* new2 = (char*)malloc(sizeof(char)*(100));
        sprintf(new2, "  %04d.%02d.%02d. %02d:%02d:%02d",
            remainingYears, remainingMonths, remainingDays,
            remainingHours, remainingMinutes, remainingSeconds);
        new_str(buffer, new2);
        free(new2);
    }
}
void print_list(struct deadline* List, int all)
{
    time_t currentTime;
    time(&currentTime);
    byte late = 1, inDay = 1, inWeek = 1, inMonth = 1, inLife = 1;
    time_t remTime;
    while (List!=NULL)
    {
        remTime = List->time-currentTime-3600;
        if (all || !List->ok)
        {
            if((late))
            {
                printf("ALREADY LATE\n");
                late=0;
            }
            if((0 < remTime) && inDay)
            {
                printf("\nIN A DAY\n");
                inDay=0;
            }
            if((24*3600 < remTime) && inWeek)
            {
                printf("\nIN A WEEK\n");
                inWeek=0;
            }
            if((7*24*3600 < remTime) && inMonth)
            {
                printf("\nIN A MONTH\n");
                inMonth=0;
            }
            if((31*24*3600 < remTime) && inLife)
            {
                printf("\nIN A LIFE\n");
                inLife=0;
            }
            print_dl(List, all);
            printf("\n");
        }
        List=List->next;
    }
}
void str_cd_list(struct deadline* List, int all, stringList** buffer)
{
    time_t currentTime;
    time(&currentTime);
    byte late = 1, inDay = 1, inWeek = 1, inMonth = 1, inLife = 1;
    time_t remTime;
    while (List!=NULL)
    {
        remTime = List->time-currentTime-3600;  //We added 3600 sec to it in an other function
        if (all || !List->ok)
        {
            if((late))
            {
                new_str(buffer, "ALREADY LATE\n");
                late=0;
            }
            if((0 < remTime) && inDay)
            {
                new_str(buffer, "\nIN A DAY\n");
                inDay=0;
            }
            if((24*3600 < remTime) && inWeek)
            {
                new_str(buffer, "\nIN A WEEK\n");
                inWeek=0;
            }
            if((7*24*3600 < remTime) && inMonth)
            {
                new_str(buffer, "\nIN A MONTH\n");
                inMonth=0;
            }
            if((31*24*3600 < remTime) && inLife)
            {
                new_str(buffer, "\nIN A LIFE\n");
                inLife=0;
            }

            str_cd_dl(List, all, buffer);

            new_str(buffer, "\n");
        }
        List=List->next;
    }
    return;
}
struct deadline* new_dl(struct deadline* List)
{
    struct deadline* new = (deadline*)malloc(sizeof(deadline));
    new->next=List;

    int sameTitle = 1;
    do {
        printf("Title: ");
        new->title = read_line();
        sameTitle = same_title(List, new->title);
        if (sameTitle == 1)
        {
            printf("%s already exists!\n", new->title);
            free(new->title);
        }
    } while (sameTitle);
    
    printf("Place: ");
    new->place=read_line();
    printf("Note: ");
    new->note=read_line();

    struct tm dateTime = {0};
    int num;

    do
    {
        printf("Year: ");
        num = read_int();
    } while (num == -1);
    dateTime.tm_year=num-1900;

    do
    {
        printf("Month: ");
        num = read_int();
    } while (num == -1 || 1 > num || num > 12);
    dateTime.tm_mon=num-1;
    
    do
    {
        printf("Day: ");
        num = read_int();
        if(dateTime.tm_mon + 1 == 1 || dateTime.tm_mon + 1 == 3 || dateTime.tm_mon + 1 == 5 || dateTime.tm_mon + 1 == 7 || dateTime.tm_mon + 1 == 8 || dateTime.tm_mon + 1 == 10 || dateTime.tm_mon + 1 == 12)
        {
            if(1 > num || num > 31)
            {
                num = -1;
            }
        }
        else if(dateTime.tm_mon + 1 == 2)
        {
            if((dateTime.tm_year + 1900) % 4 == 0)
            {
                if(1 > num || num > 29)
                {
                    num = -1;
                }
            }
            else
            {
                if(1 > num || num > 28)
                {
                    num = -1;
                }
            }
        }
        else
        {
            if(1 > num || num > 30)
            {
                num = -1;
            }
        }
    } while (num == -1);
    dateTime.tm_mday=num;
    
    do
    {
        printf("Hour: ");
        num = read_int();
    } while (num == -1 || 0 > num || num > 23);
    dateTime.tm_hour=num;
    
    do
    {
        printf("Minute: ");
        num = read_int();
    } while (num == -1 || 0 > num || num > 59);
    dateTime.tm_min=num;
    
    new->time=mktime(&dateTime);
    new->time += 3600;  //I have to corrigate mktime() - local timezone can be a problem 
    new->ok=0;
    return new;
}
void del_dl(struct deadline** List, char* Title)
{
    struct deadline* current = *List;
    struct deadline* prev = NULL;

    while(current != NULL && strcmp(current->title, Title) != 0)
    {
        prev = current;
        current = current->next;
    }
    //There is no such deadline, so do nothing at all
    if(current == NULL)
    {
        printf("Couldnt find this deadline: %s", Title);
        return;
    }
    //The deadline to be deleted is the first one
    if (prev == NULL)
    {
        *List = current->next;
    }
    //Skip deadline to delete it
    else
    {
        prev->next = current->next;
    }

    free(current->title);
    free(current->place);
    free(current->note);
    free(current);
}
void ok_dl(struct deadline** List, char* Title)
{
    struct deadline* current = *List;

    while(current != NULL && strcmp(current->title, Title) != 0)
    {
        current = current->next;
    }
    //There is no such deadline, so do nothing at all
    if(current == NULL)
    {
        printf("Couldnt find this deadline: %s", Title);
        return;
    }
    //Skip deadline to delete it
    current->ok=1;
    printf("%s is finished!", Title);
}
void not_dl(struct deadline** List, char* Title)
{
    struct deadline* current = *List;

    while(current != NULL && strcmp(current->title, Title) != 0)
    {
        current = current->next;
    }
    //There is no such deadline, so do nothing at all
    if(current == NULL)
    {
        printf("Couldnt find this deadline: %s", Title);
        return;
    }
    //Skip deadline to delete it
    current->ok=0;
    printf("%s is finished!", Title);
}
void edit_dl(struct deadline** List, char* Title)
{
    struct deadline* current = *List;
    while(current != NULL && strcmp(current->title, Title) != 0)
    {
        current = current->next;
    }
    if(current == NULL)
    {
        printf("There is no deadline: %s\n", Title);
        return;
    }
    printf("EDIT %s\n", Title);
    printf("1 - Title\n2 - Place\n3 - Note\n4 - Time\n5 - OK\n 6 - all\n");
    printf("\nNumber: ");
    unsigned int mode = read_int();
    switch (mode)
    {
    case 1: //Change title
        free(current->title);
        printf("Title: ");
        current->title=read_line();
        break;
    case 2: //Change place
        free(current->place);
        printf("Place: ");
        current->place=read_line();
        break;
    case 3: //Change note
        free(current->note);
        printf("Note: ");
        current->note=read_line();
        break;
    case 4: //Change time
    {
        int num;
        struct tm dateTime = {0};
        do
        {
            printf("Year: ");
            num = read_int();
        } while (num == -1);
        dateTime.tm_year=num-1900;
        do
        {
            printf("Month: ");
            num = read_int();
        } while (num == -1 || 1 > num || num > 12);
        dateTime.tm_mon=num-1;
        do
        {
            printf("Day: ");
            num = read_int();
            if(dateTime.tm_mon + 1 == 1 || dateTime.tm_mon + 1 == 3 || dateTime.tm_mon + 1 == 5 || dateTime.tm_mon + 1 == 7 || dateTime.tm_mon + 1 == 8 || dateTime.tm_mon + 1 == 10 || dateTime.tm_mon + 1 == 12)
            {
                if(1 > num || num > 31)
                {
                    num = -1;
                }
            }
            else if(dateTime.tm_mon + 1 == 2)
            {
                if((dateTime.tm_year + 1900) % 4 == 0)
                {
                    if(1 > num || num > 29)
                    {
                        num = -1;
                    }
                }
                else
                {
                    if(1 > num || num > 28)
                    {
                        num = -1;
                    }
                }
            }
            else
            {
                if(1 > num || num > 30)
                {
                    num = -1;
                }
            }
        } while (num == -1);
        dateTime.tm_mday=num;
        do
        {
            printf("Hour: ");
            num = read_int();
        } while (num == -1 || 0 > num || num > 23);
        dateTime.tm_hour=num;
        do
        {
            printf("Minute: ");
            num = read_int();
        } while (num == -1 || 0 > num || num > 59);
        dateTime.tm_min=num;
        current->time=mktime(&dateTime);
        current->time += 3600;
        break;
    }
    case 5:
        printf("Is it ready [0-no, 1-yes]: ");
        while(current->ok=read_int() != 0 || current->ok != 1);
    break;
    default:
        del_dl(List, Title);
        *List = new_dl(*List);
    }
    printf("\n%s was edited:\n", Title);
    print_dl(current, 0);
    printf("\n");
}
struct deadline* merge(struct deadline* list1, struct deadline* list2) {
    if (list1 == NULL) {
        return list2;
    }
    if (list2 == NULL) {
        return list1;
    }

    if (list1->time <= list2->time) {
        list1->next = merge(list1->next, list2);
        return list1;
    } else {
        list2->next = merge(list1, list2->next);
        return list2;
    }
}
struct deadline* mergeSort(struct deadline* head) {
    if (head == NULL || head->next == NULL) {
        return head;
    }

    struct deadline* slow = head;
    struct deadline* fast = head->next;

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }

    struct deadline* secondHalf = slow->next;
    slow->next = NULL;

    struct deadline* sortedFirstHalf = mergeSort(head);
    struct deadline* sortedSecondHalf = mergeSort(secondHalf);

    return merge(sortedFirstHalf, sortedSecondHalf);
}
void free_list(struct deadline* List)
{
    deadline* tmp;
    while(List!=NULL)
    {
        tmp=List->next;
        free(List->title);
        free(List->place);
        free(List->note);
        free(List);
        List = tmp;
    }
}

// Function to save linked list to a binary file
void save_file(const char* filename, deadline* head) {
    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    deadline* current = head;
    while (current != NULL) {
        // Write the data of the current node to the file
        fwrite(&(current->time), sizeof(time_t), 1, file);
        
        size_t titleLen = strlen(current->title) + 1; // Include the null terminator
        fwrite(&titleLen, sizeof(size_t), 1, file);
        fwrite(current->title, sizeof(char), titleLen, file);

        size_t placeLen = strlen(current->place) + 1;
        fwrite(&placeLen, sizeof(size_t), 1, file);
        fwrite(current->place, sizeof(char), placeLen, file);

        size_t noteLen = strlen(current->note) + 1;
        fwrite(&noteLen, sizeof(size_t), 1, file);
        fwrite(current->note, sizeof(char), noteLen, file);

        fwrite(&(current->ok), sizeof(unsigned int), 1, file);

        // Move to the next node
        current = current->next;
    }

    fclose(file);
}

// Function to read linked list from a binary file
deadline* read_file(FILE* file) {
    deadline* head = NULL;
    deadline* current = NULL;

    while (1) {
        // Read the data of the current node from the file
        deadline* newNode = (deadline*)malloc(sizeof(deadline));
        if (newNode == NULL) {
            perror("Error allocating memory");
            fclose(file);
            free(newNode);
            return NULL;
        }

        size_t titleLen, placeLen, noteLen;

        if (fread(&(newNode->time), sizeof(time_t), 1, file) != 1) {
            free(newNode);
            break; // Reached end of file or error
        }

        fread(&titleLen, sizeof(size_t), 1, file);
        newNode->title = (char*)malloc(titleLen * sizeof(char));
        fread(newNode->title, sizeof(char), titleLen, file);

        fread(&placeLen, sizeof(size_t), 1, file);
        newNode->place = (char*)malloc(placeLen * sizeof(char));
        fread(newNode->place, sizeof(char), placeLen, file);

        fread(&noteLen, sizeof(size_t), 1, file);
        newNode->note = (char*)malloc(noteLen * sizeof(char));
        fread(newNode->note, sizeof(char), noteLen, file);

        fread(&(newNode->ok), sizeof(unsigned int), 1, file);

        newNode->next = NULL;

        if (head == NULL) {
            head = newNode;
            current = newNode;
        } else {
            current->next = newNode;
            current = newNode;
        }
    }

    fclose(file);
    return head;
}