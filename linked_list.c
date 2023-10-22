#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifdef _WIN32
    #define CLEAR "cls"
#else //In any other OS
    #define CLEAR "clear"
#endif

typedef struct Person {
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

void show_all(void) {
    system(CLEAR);

    if (head == NULL) {
        printf("There's no person registered yet!\n");
        getchar();
        return;
    }

    Person* person = head;

    while (person != NULL) {
        print_person(person);
        person = person->next;
    }

    getchar();
}

void link_list(Person* next_person) {
    if (head == NULL) {
        head = next_person;
        return;
    }

    Person* person = head;

    while (person->next != NULL) {
        person = person->next;
    }

    person->next = next_person;
}

void register_person(void) {
    system(CLEAR);
    Person* person = malloc(sizeof(Person));
    
    if (person == NULL) return;

    printf("Type their name:\n");
    scanf("%[^\n]s", person->name);
    getchar();

    printf("Type their CPF:\n");
    scanf("%s", person->cpf);
    getchar();

    printf("Type their phone number:\n");
    scanf("%s", person->phone);
    getchar();

    printf("Type their gender:\n");
    scanf(" %c", &person->gender);
    getchar();

    printf("Type their age:\n");
    scanf(" %d", &person->age);
    getchar();

    person->next = NULL;
    link_list(person);
}

void delete_first(void) {
    system(CLEAR);
    if (head == NULL) {
        printf("There's no person registered yet!\n");
        getchar();
        return;
    }

    Person* first_person = head;

    if (first_person->next == NULL) {
        free(first_person);
        first_person = NULL;
        head = NULL;
    } else {
        head = first_person->next;
        free(first_person);
        first_person = NULL;
    }
    
    printf("First person deleted with success!\n");
    getchar();
}

void show_menu(void) {
    system(CLEAR);
    printf("1 to register a person.\n");
    printf("2 to show all the registered people.\n");
    printf("3 to delete the first one.\n");
    printf("-1 to leave.\n");
}

int main(void) {
    int answer = 0;

    while(answer != -1) {
        show_menu();
        scanf(" %d", &answer);
        getchar();

        if (answer == -1) break;

        switch(answer) {
            case 1:
                register_person();
                break;
            case 2:
                show_all();
                break;
            case 3:
                delete_first();
                break;
            default:
                printf("Type a valid number!\n");
                getchar();
                break;
        }

        answer = 0;
    }

    return 0;
}