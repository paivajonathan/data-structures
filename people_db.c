#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const size_t DEFAULT_CAPACITY = 3;

typedef struct {
	char name[50];
	char cpf[12];
	char phone[12];
	char gender;
	int age;
} Person;

Person **people;
size_t length = 0;
size_t capacity = 0;

/**
 * Waits user's confirmation to continue the program.
*/
void wait_user_input(void);

/**
 * Shows the interactive menu that the user will see.
*/
void print_menu(void);

/**
 * Shows all information about a person giving their specific index in the array.
 * @param index The index that'll be used to access the person in the array.
*/
void print_person(int index);

/* ========== START OF ARRAY UTILS ========== */

/**
 * Checks if an error occurred while dynamically changing the size of the array.
*/
void check_error(void);

/**
 * Allocates the specific size, defined in "DEFAULT_CAPACITY",
 * the array will start with.
*/
void initialize_array(void);

/**
 * Used after an array entry receives NULL, which means it was deleted.
 * Reorganizes the array to push the NULL value to the end,
 * finding its index and swapping positions until necessary.
*/
void organize_array(void);

/**
 * Increases the size of the array, when
 * there's no space left to insert new entries.
*/
void grow_array_if_needed(void);

/**
 * Decreases the size of the array, when there's too much space that
 * won't be used yet.
*/
void shrink_array_if_needed(void);

/**
 * Liberates the memory that was used by a specific Person entry,
 * and sets the value in that position to NULL.
*/
void delete_from_array(int index);

/**
 * Liberates all memory that was being used by the array.
 * Also resets all values to NULL or zero.
*/
void destroy_array(void);

/* ========== END OF ARRAY UTILS ========== */

/* ========== START OF CRUD FUNCTIONS ========== */

/**
 * Inserts a Person in the end of the array, using the length variable.
*/
void insert_person(void);

/**
 * Shows information about all Person entries that were inserted in the array.
*/
void select_people(void);

/**
 * Finds using CPF struct member and shows information about a specific Person.
 * @return The index of the Person entry in the array, or -1.
*/
int select_person(void);

/**
 * Gets the index of a Person entry using their CPF,
 * and updates its informations.
*/
void update_person(void);

/**
 * Gets the index of a Person entry using its CPF,
 * and removes it from the people array.
*/
void delete_person(void);

/* ========== END OF CRUD FUNCTIONS ========== */

/* ========== START OF DATA STRUCTURE FUNCTIONS ========== */

/**
 * Removes the last person from the people array,
 * to simulate the behavior of a stack data structure.
*/
void call_person_stack(void);

/* ========== END OF DATA STRUCTURE FUNCTIONS ========== */

int main(void)
{
	initialize_array();
	int answer = 0;

	while(answer != -1)
	{
		print_menu();
		scanf(" %d", &answer);
		getchar();

		if (answer == -1) break;

		switch(answer)
		{
			case 1:
				insert_person();
				break;
			case 2:
				update_person();
				break;
			case 3:
				delete_person();
				break;
			case 4:
				select_person();
				break;
			case 5:
				select_people();
				break;
			case 6:
				call_person_stack();
				break;
			default:
				system("clear");
				printf("Type a valid value!\n");
				wait_user_input();
				break;
		}

		answer = 0;
	}

	printf("The program has been terminated!\n");
	destroy_array();
	return 0;
}

void wait_user_input(void)
{
	printf("Press enter to continue...\n");
	getchar();
}

void print_menu(void)
{
	system("clear");
	printf("What action do you want to do?\n");
	printf("Type 1 to insert a person.\n");
	printf("Type 2 to update a person.\n");
	printf("Type 3 to delete a person.\n");
	printf("Type 4 to select a person.\n");
	printf("Type 5 to select all people.\n");
	printf("Type 6 to call the last person.\n");
	printf("Type -1 to exit the program.\n");
}

void print_person(int index)
{
	printf("\n%d° person:\n", index + 1);
	printf("Name: %s\n", people[index]->name);
	printf("CPF: %s\n", people[index]->cpf);
	printf("Age: %d\n", people[index]->age);
	printf("Gender: %c\n", people[index]->gender);
	printf("Phone: %s\n\n", people[index]->phone);
}

void check_error(void)
{
	if (people != NULL) return;
	
	printf("A memory error occurred!\n");
	exit(1);
}

void initialize_array(void)
{
	if (capacity != 0) return;
	
	printf("Initializing array!\n");
	people = calloc(DEFAULT_CAPACITY, sizeof(Person *));
	check_error();
	capacity = DEFAULT_CAPACITY;
}

void organize_array(void)
{
	int null_index = -1;
	Person *aux_person;

	for (int i = 0; i < length; i++)
	{
		if (people[i] == NULL)
		{
			null_index = i;
			break;
		}
	}

	if (null_index == -1) return;

	for (int i = null_index; i < length; i++)
	{
		aux_person = people[i + 1];
		people[i + 1] = people[i];
		people[i] = aux_person;
	}
}

void grow_array_if_needed(void)
{
	if (length == capacity)
	{
		system("clear");
		printf("Dynamically growing array size!\n");
		capacity += DEFAULT_CAPACITY;
		people = realloc(people, capacity * sizeof(Person *));
		check_error();
	}
}

void shrink_array_if_needed(void)
{
	if (length > 0 && length == capacity - DEFAULT_CAPACITY)
	{
		system("clear");
		printf("Dynamically shrinking database size!\n");
		capacity -= DEFAULT_CAPACITY;
		people = realloc(people, capacity * sizeof(Person *));
		check_error();
		wait_user_input();
	}
}

void delete_from_array(int index)
{
	free(people[index]);
	people[index] = NULL;
	organize_array();
	length--;
	shrink_array_if_needed();
}

void destroy_array(void)
{
	for (int i = 0; i < length; i++)
	{
		free(people[i]);
		people[i] = NULL;
	}

	free(people);
	people = NULL;
	capacity = 0;
	length = 0;
}

void insert_person(void)
{
	system("clear");
	grow_array_if_needed();

	Person *person = malloc(sizeof(Person));
	if (person == NULL)
	{
		printf("An error occurred! Person couldn't be created!\n");
		exit(1);
	}
	
	printf("Inserting person...\n");
	wait_user_input();
	system("clear");
	
	printf("Type their name:\n");
	scanf("%[^\n]s", person->name);
	getchar();

	printf("Type their cpf:\n");
	scanf("%s", person->cpf);
	getchar();
	
	printf("Type their age:\n");
	scanf(" %d", &person->age);
	getchar();
	
	printf("Type their gender:\n");
	scanf(" %c", &person->gender);
	getchar();
	
	printf("Type their phone:\n");
	scanf("%s", person->phone);
	getchar();

	people[length] = person;
	length++;

	printf("Person successfully registered!\n");
	wait_user_input();
}

void select_people(void)
{
	system("clear");

	if (!length)
	{
		printf("There's no person registered yet!\n");
		wait_user_input();
		return;
	}

	for (int i = 0; i < length; i++)
	{
		print_person(i);
	}

	printf("Capacity: %lu, Length: %lu\n", capacity, length);
	wait_user_input();
}

int select_person(void)
{
	system("clear");

	if (!length)
	{
		printf("There's no person registered yet!\n");
		wait_user_input();
		return -1;
	}

	char cpf[12];
	printf("Type the person's CPF:\n");
	scanf("%s", cpf);
	getchar();

	for (int i = 0; i < length; i++)
	{
		if (strcmp(cpf, people[i]->cpf) == 0)
		{
			printf("Person found!\n");
			print_person(i);
			wait_user_input();
			return i;
		}
	}

	printf("No person found with that CPF!\n");
	wait_user_input();
	return -1;
}

void update_person(void)
{
	int index = select_person();

	if (index == -1) return;

	system("clear");
	printf("Updating person...\n");
	wait_user_input();

	system("clear");
	printf("Type their new name:\n");
	scanf("%[^\n]s", people[index]->name);
	getchar();

	printf("Type their new cpf:\n");
	scanf("%s", people[index]->cpf);
	getchar();
	
	printf("Type their new age:\n");
	scanf(" %d", &people[index]->age);
	getchar();
	
	printf("Type their new gender:\n");
	scanf(" %c", &people[index]->gender);
	getchar();
	
	printf("Type their new phone:\n");
	scanf("%s", people[index]->phone);
	getchar();

	printf("Person's informations successfully changed!\n");
	wait_user_input();
}

void delete_person(void)
{
	int index = select_person();

	if (index == -1) return;

	system("clear");
	printf("Deleting person...\n");
	wait_user_input();

	delete_from_array(index);

	system("clear");
	printf("Person successfully deleted!\n");
	wait_user_input();
}

void call_person_stack(void)
{
	system("clear");

	if (!length)
	{
		printf("There's no person to call yet!\n");
		wait_user_input();
		return;
	}

	size_t index = length - 1;

	printf("Calling last person!\n");
	print_person(index);
	wait_user_input();

	delete_from_array(index);
}
