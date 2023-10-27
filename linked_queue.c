#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifdef _WIN32
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif

typedef struct Person
{
	char name[51];
	char cpf[12];
	char phone[12];
	char gender;
	int age;
    struct Person* next;
} Person;

Person* head = NULL;

void print_person(Person* person)
{
	printf("\nName: %s\n", person->name);
	printf("CPF: %s\n", person->cpf);
	printf("Phone %s\n", person->phone);
	printf("Gender: %c\n", person->gender);
	printf("Age: %d\n\n", person->age);
}

void show_people(void)
{
    system(CLEAR);

    if (head == NULL)
    {
        printf("There's no person registered yet!\n");
        getchar();
        return;
    }

    Person* current_person = head;

    while (current_person != NULL)
    {
        print_person(current_person);
        current_person = current_person->next;
    }

    getchar();
}

void enqueue(Person* next_person)
{
    if (head == NULL)
    {
        head = next_person;
        return;
    }

    Person* current_person = head;

    while (current_person->next != NULL)
    {
        current_person = current_person->next;
    }

    current_person->next = next_person;
}

void register_person(void)
{
    system(CLEAR);
    Person* new_person = malloc(sizeof(Person));
    
    if (new_person == NULL)
    {
        printf("An error occurred while creating a new_person!\n");
        return;
    }

    printf("Type their name:\n");
    scanf("%[^\n]s", new_person->name);
    getchar();

    printf("Type their CPF:\n");
    scanf("%s", new_person->cpf);
    getchar();

    printf("Type their phone number:\n");
    scanf("%s", new_person->phone);
    getchar();

    printf("Type their gender:\n");
    scanf(" %c", &new_person->gender);
    getchar();

    printf("Type their age:\n");
    scanf(" %d", &new_person->age);
    getchar();

    new_person->next = NULL;
    enqueue(new_person);
}

void dequeue(void)
{
    system(CLEAR);
    if (head == NULL)
    {
        printf("There's no person registered yet!\n");
        getchar();
        return;
    }

    print_person(head);

    Person* previous_head = head;
    head = head->next;
    free(previous_head);
    previous_head = NULL;
    
    printf("First person deleted with success!\n");
    getchar();
}

void destroy_queue(void)
{
    Person* previous_head;

    while(head != NULL)
    {
        previous_head = head;
        head = head->next;
        free(previous_head);
        previous_head = NULL;
    }
}

void show_menu(void)
{
    system(CLEAR);
    printf("1 to register a person.\n");
    printf("2 to show all the registered people.\n");
    printf("3 to delete the first one.\n");
    printf("-1 to leave.\n");
}

int main(void)
{
    int answer = 0;

    while(answer != -1)
    {
        show_menu();
        scanf(" %d", &answer);
        getchar();

        if (answer == -1) break;

        switch(answer)
        {
            case 1:
                register_person();
                break;
            case 2:
                show_people();
                break;
            case 3:
                dequeue();
                break;
            default:
                printf("Type a valid number!\n");
                getchar();
                break;
        }

        answer = 0;
    }

    destroy_queue();
    return 0;
}