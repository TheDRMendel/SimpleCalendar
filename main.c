#include "functions.h"

int main(void)
{
    deadline* List = NULL;
    char* cmd = NULL;
    FILE* fp = fopen("deadlines.bin", "rb");
    if(fp != NULL)
    {
        List = read_file(fp);
    }
    fclose(fp);
    clear();
    while (1)
    {
        cmd = NULL;
        printf("*********** SIMPLE CALENDAR ***********\n");
        printf(" ~ ");
        cmd = read_line();
        if(cmd == "") continue;
        else if (strcmp(cmd, "h") == 0 || strcmp(cmd, "he") == 0 || strcmp(cmd, "hel") == 0 || strcmp(cmd, "help") == 0)
        {
            printf("\t\tHELP\n\n");

            printf("    n - add new deadline to the calendar\n");
            printf("    d - deletes task from calendar\n");
            printf("   ok - set task to finished\n");
            printf("   ic - set task to incomplete\n");
            printf("    e - edit deadline in the way you want\n\n");

            printf("   ls - lists reamining tasks\n");
            printf("  als - list all deadlines: finished and unfinished\n");
            printf("   cd - countdown reamining tasks\n");
            printf("  acd - countdown all deadlines: finished and unfinished\n\n");

            printf("    c - sets console to default\n");
            printf("    s - save deadlines\n");
            printf("   ex - exit from the program\n\n");
        }
        else if(strcmp(cmd, "n") == 0 || strcmp(cmd, "ne") == 0 || strcmp(cmd, "new") == 0)
        {
            printf("\t\tNEW DEADLINE\n\n");
            List = new_dl(List);
            printf("\nNew deadline:\n");
            print_dl(List, 0);
            printf("\n\n");
        }
        else if(strcmp(cmd, "d") == 0 || strcmp(cmd, "de") == 0 || strcmp(cmd, "del") == 0)
        {
            printf("\t\tDELETE DEADLINE\n\n");
            printf("Title: ");
            char* Title = read_line();
            del_dl(&List, Title);
            printf("%s is deleted!\n\n", Title);
        }
        else if(strcmp(cmd, "o") == 0 || strcmp(cmd, "ok") == 0)
        {
            printf("\t\tFINISH DEADLINE\n\n");
            printf("Title: ");
            char* Title = read_line();
            ok_dl(&List, Title);
            printf("\n\n");
        }
        else if(strcmp(cmd, "i") == 0 || strcmp(cmd, "ic") == 0 || strcmp(cmd, "inc") == 0 || strcmp(cmd, "inco") == 0 || strcmp(cmd, "incom") == 0 || strcmp(cmd, "incomp") == 0 || strcmp(cmd, "incompl") == 0 || strcmp(cmd, "incomple") == 0 || strcmp(cmd, "incomplet") == 0 || strcmp(cmd, "incomplete") == 0)
        {
            printf("\t\tINCOMPLETE DEADLINE\n\n");
            printf("Title: ");
            char* Title = read_line();
            not_dl(&List, Title);
            printf("\n\n");
        }
        else if(strcmp(cmd, "e") == 0 || strcmp(cmd, "ed") == 0 || strcmp(cmd, "edi") == 0 || strcmp(cmd, "edit") == 0)
        {
            printf("\t\tEDIT DEADLINE\n\n");
            printf("Title: ");
            char* Title = read_line();
            printf("\n");
            edit_dl(&List, Title);
            printf("\n");
        }
        else if(strcmp(cmd, "l") == 0 || strcmp(cmd, "ls") == 0 || strcmp(cmd, "li") == 0 || strcmp(cmd, "lis") == 0 || strcmp(cmd, "list") == 0)
        {
            printf("\t\tLIST DEADLINES\n\n");
            List = mergeSort(List);
            print_list(List, 0);
            printf("\n");
        }
        else if(strcmp(cmd, "al") == 0 || strcmp(cmd, "als") == 0 || strcmp(cmd, "ali") == 0 || strcmp(cmd, "alis") == 0 || strcmp(cmd, "alist") == 0)
        {
            printf("\n\t\tLIST ALL DEADLINES\n\n");
            List = mergeSort(List);
            print_list(List, 1);
            printf("\n");
        }
        else if(strcmp(cmd, "cd") == 0 || strcmp(cmd, "co") == 0 || strcmp(cmd, "cou") == 0 || strcmp(cmd, "coun") == 0 || strcmp(cmd, "count") == 0 || strcmp(cmd, "countd") == 0 || strcmp(cmd, "countdo") == 0 || strcmp(cmd, "countdow") == 0 || strcmp(cmd, "countdown") == 0)
        {
            stringList* buffer = NULL;
            List = mergeSort(List);
            time_t start_time = time(NULL);
            int cleared = 0;
            
            #ifndef _WIN32
                initscr();  // Initialize the curses library
                timeout(0); // Set non-blocking input
            #endif

            while (1)
            {
                // Calculate elapsed time
                time_t current_time = time(NULL);
                
                // Your task to be performed every one second
                new_str(&buffer, "*********** SIMPLE CALENDAR ***********\n");
                new_str(&buffer, " ~ ");
                new_str(&buffer, cmd);
                new_str(&buffer, "\n\t\tDEADLINE COUNTDOWN\n\n");
                str_cd_list(List, 0, &buffer);
                new_str(&buffer, "\n\t\tPress ESC to escape");
                
                if(!cleared)
                {
                    cleared = 1;
                    clear();
                }

                //WRITE OUT THE BUFFERED STRING
                cursor(0);
                print_str(buffer);
                free_str(&buffer);

                // Update the start time
                start_time = current_time;

                #ifndef _WIN32
                    endwin();
                #endif

                //ESC is pressed or not
                if (kbhit())
                {
                    int key = getch();
                    if (key == 27) break;
                }

                sleep_ms(1000);
            }
            clear();
            cursor(1);
        }
        else if(strcmp(cmd, "acd") == 0 || strcmp(cmd, "aco") == 0 || strcmp(cmd, "acou") == 0 || strcmp(cmd, "acoun") == 0 || strcmp(cmd, "acount") == 0 || strcmp(cmd, "acountd") == 0 || strcmp(cmd, "acountdo") == 0 || strcmp(cmd, "acountdow") == 0 || strcmp(cmd, "acountdown") == 0)
        {
            stringList* buffer = NULL;
            List = mergeSort(List);
            time_t start_time = time(NULL);
            int cleared = 0;
            
            #ifndef _WIN32
                initscr();  // Initialize the curses library
                timeout(0); // Set non-blocking input
            #endif

            while (1)
            {
                // Calculate elapsed time
                time_t current_time = time(NULL);
                
                // Your task to be performed every one second
                new_str(&buffer, "*********** SIMPLE CALENDAR ***********\n");
                new_str(&buffer, " ~ ");
                new_str(&buffer, cmd);
                new_str(&buffer, "\n\t\tDEADLINE COUNTDOWN\n\n");
                str_cd_list(List, 1, &buffer);
                new_str(&buffer, "\n\t\tPress ESC to escape");
                
                if(!cleared)
                {
                    cleared = 1;
                    clear();
                }

                //WRITE OUT THE BUFFERED STRING
                cursor(0);
                print_str(buffer);
                free_str(&buffer);

                // Update the start time
                start_time = current_time;

                #ifndef _WIN32
                    endwin();
                #endif

                //ESC is pressed or not
                if (kbhit())
                {
                    int key = getch();
                    if (key == 27) break;
                }

                sleep_ms(1000);
            }
            clear();
            cursor(1);
        }
        else if(strcmp(cmd, "c") == 0 || strcmp(cmd, "cl") == 0 || strcmp(cmd, "cls") == 0 || strcmp(cmd, "cle") == 0 || strcmp(cmd, "clea") == 0 || strcmp(cmd, "clear") == 0)
        {
            clear();
        }
        else if(strcmp(cmd, "ex") == 0 || strcmp(cmd, "exi") == 0 || strcmp(cmd, "exit") == 0)
        {
            clear();
            printf("*********** SIMPLE CALENDAR EXIT ***********\n\n");
            printf("Are you sure that you want to do now these interesting tasks? [Y/N]\n");
            printf(" ~ ");
            char *c = read_line();
            if (c != NULL && (!strcmp(c, "N") || !strcmp(c, "n")))
            {
                clear();
                free(cmd);
                free(c);
                printf("\n");
                continue;
            }
            else
            {
                clear();
                printf("GET RID OF YOUR TASKS!!!");
                sleep_ms(700);
                clear();
                printf("SO DO THEM!!!");
                sleep_ms(700);
                save_file("deadlines.bin", List);
                clear();
                printf("Bye!");
                sleep_ms(700);
                clear();
                free_list(List);
                free(cmd);
                if(c) free(c);
                break;
            }
        }
        else if(strcmp(cmd, "s") == 0 || strcmp(cmd, "sa") == 0 || strcmp(cmd, "sav") == 0 || strcmp(cmd, "save") == 0)
        {
            printf("\t\tSAVE DEADLINES\n\n");
            List = mergeSort(List);
            save_file("deadlines.bin", List);
            printf("Deadlines are saved!\n\n");
        }
        free(cmd);
    }
    return 0;
}