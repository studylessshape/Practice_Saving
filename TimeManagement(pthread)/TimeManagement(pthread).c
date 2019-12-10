#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
#include<time.h>
#include<pthread.h>
#include<windows.h>
//define structure
struct Time
{
    int hour;
    int minute;
};
typedef struct Detail
{
    int serial_number;
    char event[1000];
    struct Time start_time;
    char place[1000];
    struct Time continue_time;
    struct Detail* next;
}Detail;
//linked list 2 is used to print event by name
struct Detail_name
{
    int serial_number;
    char event[1000];
    struct Time start_time;
    char place[1000];
    struct Time continue_time;
    struct Detail_name* next;
};
//global variable
struct Detail* first_event = NULL;
int exit_signal = 0;
//function define
void printMenu();
void addEvent(struct Detail** first_event);
void inputEvent(struct Detail* event);
void deleteEvent(struct Detail** first_event, int judge);
void numberReset(struct Detail *first_event);
void searchEvent_Time(struct Detail* first_event);
void searchMode_Time(struct Detail* first_event, int search_time);
void searchEvent_Name(struct Detail* first_event);
void searchMode_Name(struct Detail* first_event, char search_name[]);
void searchMode_Print(struct Detail* search_event);
void modifyEvent(struct Detail* first_event, int judge);
void printfAllEvent_Time(struct Detail* first_event);
void printfAllEvent_Name(struct Detail* first_event);
void blurStructure(struct Detail* first_event, struct Detail_name** first);
void Mod_Name_releaseEvent(struct Detail_name** first);
void Mod_Name_printEvent(struct Detail_name* first);
int printfAllEvent_Number(struct Detail* first_event);
void EventSave(Detail *first_event);
void EventLoad(Detail **first_event);
void releaseDetail(struct Detail** first_event);
//pthread function
//alarm system
void* alarmSystem(void* args)
{
    int count = 0;//avoid output too many times
    time_t t;
    struct tm *lt;
    struct Detail* current;
    //first = (struct Detail*)args;

    while(1)
    {
        time(&t);
        lt = localtime(&t);
        /*
           test section
        */
        if(exit_signal == 1)
            break;
        //printf("test pthread!\n");
        if(lt->tm_hour == 13 && lt->tm_min == 22 && count == 0)
        {
            printf("|>Today your all event...\n\a");
            printfAllEvent_Time(first_event);
            count ++;
            printf("|--------------End--------------|\n");
        }

        /*
            test section
        */
        if(lt->tm_hour == 7 && lt->tm_min == 30 && count == 0)
        {
            printf("|>Today your all event...\n\a");
            printfAllEvent_Time(first_event);
            count++;
            system("pause");
        }
        current = first_event;
        while(current != NULL)
        {
            if(current->start_time.hour == lt->tm_hour && current->start_time.minute == lt->tm_min)
            {
                printf("\n|>Event \"%s\" should be done now!\n\a", current->event);
                printf("|-Place: %s\n", current->place);
                printf("|-Event Time: ");
                if(current->start_time.hour < 10)
                {
                    printf("0");
                }
                printf("%d:", current->start_time.hour);
                if(current->start_time.minute < 10)
                {
                    printf("0");
                }
                printf("%d\n", current->start_time.minute);
                printf("|-Continue time: %dh, %dm\n", current->continue_time.hour, current->continue_time.minute);
                system("pause");
            }
            current = current->next;
        }
    }
    return NULL;
}
//main function zone
int main()
{
    pthread_t alarm_system;
    //struct Detail* first_event = NULL;
    char input, buffer;
    int judge;

    printMenu();
    EventLoad(&first_event);
    //first_event = (struct Detail*)malloc(sizeof(struct Detail));
    pthread_create(&alarm_system, NULL, alarmSystem, first_event);
    while (1)
    {

        printf("> ");
        input = getchar();
        while((buffer = getchar()) != '\n' && buffer != EOF);
        switch (input)
        {
        case '1':
            addEvent(&first_event);
            numberReset(first_event);
            break;
        case '2':
            printf("\t|---------------Delete---------------|\n");
            judge = printfAllEvent_Number(first_event);
            deleteEvent(&first_event, judge);
            numberReset(first_event);
            printf("\t|-------------Delete End-------------|\n");
            break;
        case '3':
            printf("\t|---------------Search by Time---------------|\n");
            searchEvent_Time(first_event);
            printf("\t|--------------Search Time End---------------|\n");
            break;
        case '4':
            printf("\t|---------------Search by Name---------------|\n");
            searchEvent_Name(first_event);
            printf("\t|--------------Search Name End---------------|\n");
            break;
        case '5':
            printf("\t|---------------Modify---------------|\n");
            judge = printfAllEvent_Number(first_event);
            modifyEvent(first_event, judge);
            break;
        case '6':
            printf("\t|---------------Events Below---------------|\n");
            printfAllEvent_Time(first_event);
            printf("\t|--------------------End-------------------|\n");
            break;
        case '7':
            printf("\t|---------------Events Below---------------|\n");
            printfAllEvent_Name(first_event);
            printf("\t|--------------------End-------------------|\n");
            break;
        case '8':
            printf("\t|---------------Events Saving--------------|\n");
            EventSave(first_event);
            printf("\t|--------------------End-------------------|\n");
            break;
        case '9':
            printf("\t|--------------Events Loading--------------|\n");
            EventLoad(&first_event);
            printf("\t|--------------------End-------------------|\n");
            break;
        case '0':
            releaseDetail(&first_event);
            system("pause");
            exit_signal = 1;
            return 0;
            break;
        case '?':
            printMenu();
            break;
        default:
            printf("|>Wrong order!Please try again!\n");
            break;
        }
        setbuf(stdin, NULL);
    }
    pthread_join(alarm_system, NULL);
    return 0;
}

//function zone
//print menu
void printMenu()
{
    system("cls");
    printf("\t||||||||||||||||||)Menu(||||||||||||||||||\n");
    printf("\t __________________^^^^__________________\n");
    printf("\t|        Please Enter Your Choice!       |\n");
    printf("\t|   1.Add event         2.Delete event   |\n");
    printf("\t|                                        |\n");
    printf("\t|   3.Search event      4.Search event   |\n");
    printf("\t|     (time)              (name)         |\n");
    printf("\t|   5.Modify event      6.Show all events|\n");
    printf("\t|                         (time)         |\n");
    printf("\t|   7.Show all events   8.Save all event |\n");
    printf("\t|     (name)                             |\n");
    printf("\t|   9.Load events       0.Exit system    |\n");
    printf("\t|________________________________________|\n");
    printf("|>Your choice is(input '?' can watch menu again)\n");
}
//add event
void addEvent(struct Detail** first_event)
{
    struct Detail* previous_event;
    struct Detail* current_event;
    struct Detail* new_event;
    current_event = *first_event;
    previous_event = NULL;
    printf("\t|---------------Add---------------|\n");
    printf("|>Are you sure you want to add the event(Y/N)?\n");

    char input, buffer;
    int judge = -1;

    while (1)
    {
        printf("> ");
        //setbuf(stdin, NULL);
        input = getchar();
        while((buffer = getchar()) != '\n' && buffer != EOF);
        switch (input)
        {
        case 'Y':
        case 'y':
            judge = 1;
            break;
        case 'N':
        case 'n':
            judge = 0;
            break;
        default:
            printf("|>Wrong order!\n");
            break;
        }
        if (judge == 0 || judge == 1)
            break;
    }
    if (judge == 1)
    {
        //Allocate memory
        new_event = (struct Detail*)malloc(sizeof(struct Detail));
        if (new_event == NULL)
        {
            printf("|>Memory allocation failed!\n");
            exit(1);
        }
        else
        {
            inputEvent(new_event);
        }
    }
    else if (judge == 0)
    {
        printf("|>It has return menu!\n");
        printf("|>You can try to input number to order!\n");
        return;
    }
    //add relative position
    while(current_event != NULL && ((current_event->start_time.hour < new_event->start_time.hour)||((current_event->start_time.hour == new_event->start_time.hour)&&(current_event->start_time.minute < new_event->start_time.minute))))
    {
        previous_event = current_event;
        current_event = current_event->next;
    }
    new_event->next = current_event;

    if (previous_event == NULL)
    {
        *first_event = new_event;
    }
    else
    {
        previous_event->next = new_event;
        while (current_event != NULL)
        {
            //change event number
            current_event->serial_number++;
            current_event = current_event->next;
        }
    }
    printf("|>Add the event success!\n");
    printf("|>Has returned to menu!\n");
    printf("\t|-------------End Add-------------|\n");
}
//input event
void inputEvent(struct Detail* new_event)
{
    int judge = 0, x;
    char buffer;
    //getchar();
    setbuf(stdin, NULL);
    printf("|>Event: ");
    gets(new_event->event);
    //while((buffer = getchar()) != '\n' && buffer != EOF);
    //getchar();
    setbuf(stdin, NULL);
    printf("|>Place: ");
    gets(new_event->place);
    //while((buffer = getchar()) != '\n' && buffer != EOF);
    printf("|>Start time(format xx:xx): ");
    while (judge != 1)
    {
        x = scanf("%d:%d", &new_event->start_time.hour, &new_event->start_time.minute);

        if(!x)
        {
            setbuf(stdin, NULL);
            printf("|>Wrong format!Please try again!\n>");
        }
        else if ((new_event->start_time.hour >= 0 && new_event->start_time.hour <= 24) && (new_event->start_time.minute >= 0 && new_event->start_time.minute <=60))
        {
            judge = 1;
            break;
        }
        else
        {
            setbuf(stdin, NULL);
            printf("|>Wrong format!Please try again!\n>");
        }
        judge = 0;
    }
    while((buffer = getchar()) != '\n' && buffer != EOF);
    /*
    if (new_event->start_time.hour >= 24)
        new_event->start_time.hour = 0;
    if (new_event->start_time.minute >= 60)
        new_event->start_time.minute = 0;
    */
    judge = 0;
    printf("|>Duration(format xx:xx): ");
    while (judge != 1)
    {
        setbuf(stdin, NULL);
        x = scanf("%d:%d", &new_event->continue_time.hour, &new_event->continue_time.minute);
        if(!x)
        {
            setbuf(stdin, NULL);
            printf("|>Wrong format!Please try again!\n>");
        }
        else if ((new_event->continue_time.hour >= 0 && new_event->continue_time.hour <=24) && (new_event->continue_time.minute >= 0 && new_event->continue_time.minute <= 60))
        {
            judge = 1;
            break;
        }
        else
        {
            printf("|>Wrong format!Please try again!\n>");
        }
        judge = 0;
    }
    if (new_event->continue_time.hour > 24)
        new_event->continue_time.hour = 0;
    if (new_event->continue_time.minute > 60)
        new_event->continue_time.minute = 0;
    while((buffer = getchar()) != '\n' && buffer != EOF);
};
//delete event
void deleteEvent(struct Detail** first_event, int judge)
{
    int input_judge;
    if (judge == 0)
        return;
    else if (judge == 1)
    {
        printf("|>All events are there!\n");
        printf("|>Input number to delete(0 to exit):\n");
        unsigned int n;//event number
        while(1)
        {
            printf("> ");
            input_judge = scanf("%u", &n);
            if(!input_judge)
            {
                setbuf(stdin, NULL);
                printf("|>Wrong format!Please try again!\n>");
            }
            else if(n == 0)
            {
                return;
            }
            else
            {
                break;
            }
        }

        struct Detail* previous_event;
        struct Detail* current_event;
        current_event = *first_event;
        previous_event = NULL;

        while (current_event != NULL && current_event->serial_number != n)
        {
            previous_event = current_event;
            current_event = current_event->next;
        }
        if (current_event == NULL)
        {
            printf("|>Can't find this event!\n");
            printf("|>Has returned to menu!\n");
        }
        else
        {
            if (previous_event == NULL)
                *first_event = current_event->next;
            else
            {
                previous_event->next = current_event->next;
            }
            free(current_event);
            printf("|>Delete success!\n");
        }
    }
    printf("\t|-------------End Delete-------------|\n");
}
//reset number
void numberReset(struct Detail *first_event)
{
    int number = 1;
    struct Detail *event;
    event = first_event;
    while(event != NULL)
    {
        event->serial_number = number;
        number++;
        event = event->next;
    }
}
//search event by time
void searchEvent_Time(struct Detail* first_event)
{
    int input_judge;
    if(first_event == NULL)
    {
        printf("|>Don't have any event!\n");
    }
    else
    {
        int search_time = -2;

        while(search_time != -1)
        {
            printf("|>Input time(hour) to search!\n|(input -1 can exit)\n");
            printf(">");
            input_judge = scanf("%d", &search_time);
            if(!input_judge)
            {
                setbuf(stdin, NULL);
                printf("|>Wrong format!Please try again!\n>");
            }
            else if(search_time == -1)
            {
                break;
            }
            else
            {
                printf("|-----------------Search start-----------------|\n");
                searchMode_Time(first_event, search_time);
                printf("|----------------Search %d end-----------------|\n", search_time);
            }
        }
    }
}
//search event by time search mode
void searchMode_Time(struct Detail* first_event, int search_time)
{
    struct Detail* search_event;
    search_event = first_event;
    int count = 0;
    while(search_event != NULL)
    {
        if((search_event->start_time.hour == search_time)||(search_event->continue_time.hour == search_time))
        {
            searchMode_Print(search_event);
            count++;
        }
        search_event = search_event->next;
    }
    if(count == 0)
    {
        printf("|>Sorry, find nothing....\n");
    }
    else
    {
        printf("|>Find %d events!\n", count);
    }
}
//search event by name
void searchEvent_Name(struct Detail* first_event)
{
    if(first_event == NULL)
    {
        printf("|>Don't have any event!\n");
    }
    else
    {
        char search_name[1000]= {0};

        while(strcmp(search_name, "-1") != 0)
        {
            printf("|>Input name to search!\n|(input -1 can exit)\n");
            printf(">");
            scanf("%s", search_name);
            printf("|-----------------Search start-----------------|\n");
            searchMode_Name(first_event, search_name);
            printf("|---------------Search '%s' end----------------|\n", search_name);
        }
    }
}
//search name mode
void searchMode_Name(struct Detail* first_event, char search_name[])
{
    struct Detail* search_event;
    search_event = first_event;
    int count = 0;
    int length_event, length_count = 0;
    //int length_search;
    //length_search = strlen(search_name);
    while(search_event != NULL)
    {
        length_event = strlen(search_event->event);
        if(strstr(search_event->event, search_name) != NULL)
        {
            searchMode_Print(search_event);
            count++;
        }
        else
        {
            for(int i = 0; i < length_event; i ++)
            {
                if(search_event->event[i] == search_name[length_count])
                {
                    searchMode_Print(search_event);
                    count++;
                    break;
                }
                length_count++;
            }
        }
        length_count = 0;
        search_event = search_event->next;
    }
    if(count == 0)
    {
        printf("|>Sorry, find nothing....\n");
    }
    else
    {
        printf("|>Find %d events!\n", count);
    }
}
//search print mode
void searchMode_Print(struct Detail* search_event)
{
    printf("|>Number: %d\n", search_event->serial_number);
    printf("|-Event: %s\n", search_event->event);
    printf("|-Place: %s\n", search_event->place);
    printf("|-Start time: ");
    if(search_event->start_time.hour < 10)
        printf("0");
    printf("%d:", search_event->start_time.hour);
    if(search_event->start_time.minute < 10)
        printf("0");
    printf("%d\n", search_event->start_time.minute);
    printf("|-Continue time: %dh, %dm\n", search_event->continue_time.hour, search_event->continue_time.minute);
}
//modify event
void modifyEvent(struct Detail* first_event, int judge)
{
    struct Detail *modify_event;
    int input, input_judge;
    if(judge == 0)
    {
        return;
    }
    else if(judge == 1)
    {
        printf("|>What's event you want to modify?\n");
        printf("|>Input event's number(input -1 to exit)\n");
        while(1)
        {
            printf("> ");
            modify_event = first_event;
            input_judge = scanf("%d", &input);
            if(!input_judge)
            {
                setbuf(stdin, NULL);
                printf("|>Wrong format!Please try again!\n>");
            }
            else if(input == -1)
            {
                return;
            }
            else
            {
                while(modify_event != NULL && modify_event->serial_number != input)
                {
                    if(modify_event->serial_number == input)
                        break;
                    else
                    {
                        modify_event = modify_event->next;
                    }
                }
                if(modify_event == NULL)
                {
                    printf("|>Can't find this event!\n");
                    printf("|>Please try other numbers(input -1 to exit)\n");
                }
                else
                {
                    printf("|--------------Event %d--------------|\n", modify_event->serial_number);
                    printf("|>1.Event: %s\n", modify_event->event);
                    printf("|-2.Place: %s\n", modify_event->place);
                    printf("|-3.Start time: ");
                    if(modify_event->start_time.hour < 10)
                        printf("0");
                    printf("%d:", modify_event->start_time.hour);
                    if(modify_event->start_time.minute < 10)
                        printf("0");
                    printf("%d\n", modify_event->start_time.minute);
                    printf("|-4.Continue time: %dh, %dm\n", modify_event->continue_time.hour, modify_event->continue_time.minute);
                    while(1)
                    {
                        printf("|>Choose message to modify\n");
                        printf("|-Input -1 to exit\n");
                        printf(">");
                        while(1)
                        {
                            scanf("%d", &input);
                            if(!input_judge)
                            {
                                setbuf(stdin, NULL);
                                printf("|>Wrong format!Please try again!\n>");
                            }
                            else
                            {
                                break;
                            }
                        }
                        printf("|>Modify ...\n>");
                        switch(input)
                        {
                        case 1 :
                            scanf("%s", modify_event->event);
                            break;
                        case 2 :
                            scanf("%s", modify_event->place);
                            break;
                        case 3 :
                            printf("(Format is xx:xx): ");
                            while(1)
                            {
                                input_judge = scanf("%d:%d", &modify_event->start_time.hour, &modify_event->start_time.minute);
                                if(!input_judge)
                                {
                                    setbuf(stdin, NULL);
                                    printf("|>Wrong format!Please try again!\n>");
                                }
                                else
                                {
                                    break;
                                }
                            }
                            break;
                        case 4 :
                            printf("(Format is xx:xx): ");
                            while(1)
                            {
                                input_judge = scanf("%d:%d", &modify_event->continue_time.hour, &modify_event->continue_time.minute);
                                if(!input_judge)
                                {
                                    setbuf(stdin, NULL);
                                    printf("|>Wrong format!Please try again!\n>");
                                }
                            }
                            break;
                        case -1 :
                            break;
                        default :
                            printf("|>Wrong!\n");
                            break;
                        }
                        if(input == -1)
                        {
                            printf("|>Has returned to menu!\n");
                            printf("\t|-------------End Modify-------------|\n");
                            return;
                        }
                        printf("|>Modify success!\n");
                    }
                }
            }
        }
    }
    printf("\t|-------------End Modify-------------|\n");
}
//printf all event
void printfAllEvent_Time(struct Detail* first_event)
{
    struct Detail* current_event;
    current_event = first_event;
    if (current_event == NULL)
    {
        printf("|>Don't have event!\n");
    }
    else
    {
        while (current_event != NULL)
        {
            printf(">--------------------------------------\n");
            printf("|>Num: %d\n", current_event->serial_number);
            printf("|-Event: %s\n", current_event->event);
            printf("|-Place: %s\n", current_event->place);
            printf("|-Start Time: ");
            if (current_event->start_time.hour < 10)
                printf("0");

            printf("%d:", current_event->start_time.hour);
            if (current_event->start_time.minute < 10)
                printf("0");

            printf("%d\n", current_event->start_time.minute);
            printf("|-Duration is: %dh, %dm\n", current_event->continue_time.hour, current_event->continue_time.minute);
            printf(">--------------------------------------\n");
            current_event = current_event->next;
        }
    }
}

void printfAllEvent_Name(struct Detail* first_event)
{
    struct Detail_name* first = NULL;
    if(first_event == NULL)
    {
        printf("|>Don't have event!\n");
        return;
    }
    first = (struct Detail_name*)malloc(sizeof(struct Detail_name));
    if(first == NULL)
    {
        printf("|>Memory allocation failed!");
        exit(0);
    }
    else
    {
        first->serial_number = first_event->serial_number;
        first->continue_time = first_event->continue_time;
        first->start_time = first_event->start_time;
        strcpy(first->event, first_event->event);
        strcpy(first->place, first_event->place);
        blurStructure(first_event, &first);
        Mod_Name_printEvent(first);
        Mod_Name_releaseEvent(&first);
    }
    return;
}

void blurStructure(struct Detail* first_event, struct Detail_name** first)
{
    struct Detail* current;
    struct Detail_name* current_name;
    struct Detail_name* previous_name;
    struct Detail_name* meduim_name;
    current = first_event->next;
    while(current != NULL)
    {
        current_name = *first;
        previous_name = NULL;
        meduim_name = NULL;
        while(current_name != NULL && (strcmp(current_name->event, current->event) < 0))
        {
            previous_name = current_name;
            current_name = current_name->next;
        }
        meduim_name = (struct Detail_name*)malloc(sizeof(struct Detail_name));
        meduim_name->serial_number = current->serial_number;
        meduim_name->continue_time = current->continue_time;
        meduim_name->start_time = current->start_time;
        strcpy(meduim_name->event, current->event);
        strcpy(meduim_name->place, current->place);
        meduim_name->next = current_name;
        if (previous_name == NULL)
        {
            *first = meduim_name;
        }
        else
        {

            previous_name->next = meduim_name;
        }
        current = current->next;
    }
}

void Mod_Name_printEvent(struct Detail_name* first)
{
    struct Detail_name* current;
    current = first;
    while (current != NULL)
    {
        printf(">--------------------------------------\n");
        printf("|>Num: %d\n", current->serial_number);
        printf("|-Event: %s\n", current->event);
        printf("|-Place: %s\n", current->place);
        printf("|-Start Time: ");
        if (current->start_time.hour < 10)
            printf("0");

        printf("%d:", current->start_time.hour);
        if (current->start_time.minute < 10)
            printf("0");

        printf("%d\n", current->start_time.minute);
        printf("|-Duration is: %dh, %dm\n", current->continue_time.hour, current->continue_time.minute);
        printf(">--------------------------------------\n");
        current = current->next;
    }
}

void Mod_Name_releaseEvent(struct Detail_name** first)
{
    struct Detail_name* event;
    while (*first != NULL)
    {
        event = *first;
        *first = (*first)->next;
        free(event);
    }
}

int printfAllEvent_Number(struct Detail* first_event)
{
    int judge;
    struct Detail* current_event;
    current_event = first_event;
    if (current_event == NULL)
    {
        judge = 0;
        printf("|>Don't have event!\n");
        return judge;
    }
    else
    {
        judge = 1;
        while (current_event != NULL)
        {
            printf(">--------------------------------------\n");
            printf("|>Num: %d\n", current_event->serial_number);
            printf("|-Event: %s\n", current_event->event);
            printf("|-Place: %s\n", current_event->place);
            printf("|-Start Time: ");
            if (current_event->start_time.hour < 10)
                printf("0");

            printf("%d:", current_event->start_time.hour);
            if (current_event->start_time.minute < 10)
                printf("0");

            printf("%d\n", current_event->start_time.minute);
            printf("|-Duration is: %dh, %dm\n", current_event->continue_time.hour, current_event->continue_time.minute);
            printf(">--------------------------------------\n");
            current_event = current_event->next;
        }
        return judge;
    }
}
//Save Event
void EventSave(Detail *first_event)
{
    FILE *Save;
    Detail *current = first_event;
    if(current == NULL)
    {
        printf("Don't have Event!\n");
        return;
    }
    if((Save = fopen("Save.txt", "w")) == NULL)
    {
        printf("Save Failed!\n");
        return;
    }
    printf("Saving");
    while(current != NULL)
    {
        fprintf(Save, "%d %s %d %d %s %d %d", current->serial_number, current->event, current->start_time.hour, current->start_time.minute, current->place, current->continue_time.hour, current->continue_time.minute);
        fprintf(Save, "%c", ' ');
        printf(".");
        current = current->next;
    }
    printf("\n");
    fclose(Save);
}
void EventLoad(Detail **first_event)
{
    Detail *current = NULL;
    Detail *read = NULL;
    int count = 0;
    FILE *Load;
    if((Load = fopen("Save.txt", "r")) == NULL)
    {
        printf("Open File Failed!\n");
        return;
    }
    rewind(Load);
    while(1)
    {
        read = (Detail *)malloc(sizeof(Detail));
        if(!read)
        {
            printf("Error!\n");
            exit(-1);
        }
        if(7 != fscanf(Load, "%d %s %d %d %s %d %d", &read->serial_number, read->event, &read->start_time.hour, &read->start_time.minute, read->place, &read->continue_time.hour, &read->continue_time.minute))
        {
            free(read);
            break;
        }
        else
        {
            count++;
            if(count == 1)
            {
                *first_event = read;
                current = *first_event;
            }
            else
            {
                current->next = read;
                current = current->next;
                current->next = NULL;
            }
        }
    }
    fclose(Load);
}
//release memory
void releaseDetail(struct Detail** first_event)
{
    struct Detail* event;
    while (*first_event != NULL)
    {
        event = *first_event;
        *first_event = (*first_event)->next;
        free(event);
    }
}
