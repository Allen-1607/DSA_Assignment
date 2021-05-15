#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CAPACITY 50000
#define USER_FILE "USER_DETAILS.dat"

unsigned long hash_function(char* str) {
    unsigned long i = 0;
    for (int j=0; str[j]; j++)
        i += str[j];
    return i % CAPACITY;
}

typedef struct Ht_item Ht_item;

// Define the Hash Table Item here
struct Ht_item {
    char key[32];
    char name[32];
    char age[32];
    char location[32];
    char password[32];
    char User[32];
    Ht_item* next;
};

typedef struct HashTable HashTable;

// Define the Hash Table here
struct HashTable {
    // Contains an array of pointers
    // to items
    Ht_item** items;
    int size;
    int count;
};


Ht_item* create_item(char* key, char* name, char* age, char* location, char* password,char* User) {
    // Creates a pointer to a new hash table item
    Ht_item* item = (Ht_item*) malloc (sizeof(Ht_item));
    strcpy(item->key, key);
    strcpy(item->name, name);
    strcpy(item->age, age);
    strcpy(item->location, location);
    strcpy(item->User,User);
    strcpy(item->password, password);

    return item;
}

HashTable* create_table(int size) {
    // Creates a new HashTable
    HashTable* table = (HashTable*) malloc (sizeof(HashTable));
    table->size = size;
    table->count = 0;
    table->items = (Ht_item**) calloc (table->size, sizeof(Ht_item*));
    return table;
}

void free_item(Ht_item* item) {
    free(item);
}

void free_hashtable(HashTable* table) {
    // Frees the table
    for (int i=0; i<table->size; i++) {
        Ht_item* item = table->items[i];
        if (item != NULL)
            free_item(item);
    }
    free(table->items);
    free(table);
}

void ht_insert(HashTable* table, char* key, char* name , char* age, char* location, char* password, char* User) {
    // Create the item
    Ht_item* item = create_item(key, name, age, location, password, User);

    // Compute the index
    int index = hash_function(key);
    printf("Index:%d\n",index);

    Ht_item* current_item = table->items[index];

    if (current_item == NULL) {
        // Key does not exist.
        if (table->count == table->size) {
            // Hash Table Full
            printf("Insert Error: Hash Table is full\n");
            // Remove the create item
            free_item(item);
            return;
        }

        // Insert directly
        table->items[index] = item;
        table->items[index]->next = NULL;
        table->count++;
    }

    else {
            // Scenario 1: We only need to update value
            if (strcmp(current_item->key, key) == 0) {
                /*free(table->items[index]->name);
                free(table->items[index]->age);
                free(table->items[index]->location);*/
                strcpy(table->items[index]->name, name);
                strcpy(table->items[index]->age, age);
                strcpy(table->items[index]->location, location);
                strcpy(table->items[index]->password,password);
                strcpy(table->items[index]->User,User);
                free_item(item);
                return;
            }

        else {
            // Scenario 2: Collision
            handle_collision(table, index, item);
            return;
        }
    }
}

void handle_collision(HashTable* table, unsigned long index, Ht_item* item) {
Ht_item* head = table->items[index];

if(head->next==NULL)
{
    Ht_item* temp = (Ht_item*) calloc(1,sizeof(Ht_item));
    temp=item;
    head->next = temp;
    temp->next=NULL;


}
else{
    Ht_item* temp = (Ht_item*) calloc(1,sizeof(Ht_item));
    temp = item;
    while(head->next)
    {
        head=head->next;
    }
    temp->next=NULL;
    head->next=temp;

}

 }

void ht_search(HashTable* table, char* key) {
    // Searches the key in the hashtable
    // and returns NULL if it doesn't exist
    int index = hash_function(key);
    Ht_item* item = table->items[index];
if(item==NULL)
{
    printf("The key does not exist\n");
}
    // Ensure that we move to items which are not NULL
    while (item != NULL) {
        if (strcmp(item->key, key) == 0)
            {
                printf("Key:%s  Name:%s  Age:%s  Location:%s\n",item->key,item->name,item->age,item->location);
            }

        item = item->next;
    }
    return NULL;
}


void print_hashtable(HashTable* table) {
    printf("\n-------------------\n");
    for (int i=0; i<table->size; i++) {

            if(table->items[i])
            {
                Ht_item* head = table->items[i];
         printf("@%d: ", i);
         while(head)
         {

            //printf("%s => Name:%s Age:%s Location:%s Username:%s | ", head->key, head->name, head->age, head->location, head->password);

            printf("Key:%s ",head->key);
             printf("Name:%s ",head->name);
              printf("Age:%s ",head->age);
               printf("Location:%s ",head->location);
              // printf("Username:%s\n",head->user);
               // printf("Password:%s\n",head->password);
                printf("Username:%s ||",head->User);

            head = head->next;
         }

            printf("\n");
            }



        }
        printf("-------------------------\n");


}

void ht_delete(HashTable* table, char* key) {
    // Deletes an item from the table
    int index = hash_function(key);
    Ht_item* item = table->items[index];
    Ht_item* prev= (Ht_item*) calloc(1,sizeof(Ht_item));
    prev = item;
    if (item == NULL) {
        // Does not exist. Return
        printf("Item does not exist\n");
        return;
    }
    else if(strcmp(item->key, key) == 0 && item->next==NULL){
            printf("Element with key:%s deleted\n",item->key);
        table->items[index] = NULL;
            free_item(item);
            table->count--;
            return;
    }
    else if(strcmp(item->key, key) == 0 && item->next!=NULL){
        table->items[index]=item->next;
        printf("Element with key:%s deleted\n",item->key);
    }
    else{
        while(item)
        {

            if(strcmp(item->key, key) == 0)
            {
                printf("Element found\n");
                printf("Prev key:%s\n",prev->key);
                printf("item key:%s\n",item->key);
                prev->next = item->next;
                printf("Element with key:%s deleted\n",item->key);

            }
            prev = item;
            item=item->next;
        }
    }

}


void getName(char *str)
{
    int temp;
    char Name[32];
printf("Enter your Name : \n");
fflush(stdin);
gets(Name);
for (temp = 0; temp < strlen(Name); temp++) {
            if (!((Name[temp] > 64 && Name[temp] < 91) || (Name[temp] > 96 && Name[temp] < 123)
                  || Name[temp] == 46 || Name[temp] == 32)){
                  printf("Invalid Name , please enter again :\n");
				  getName(Name);
            }
		    else{
		      break;
		     }
	}
	//printf("Your Name:%s \n",Name);
    strcpy(str,Name);
}

void getAge(char* str)
{
    int temp;
    char age[10];
printf("Enter your Age : \n");
fflush(stdin);
gets(age);

for (temp = 0; temp < strlen(age); temp++) {
            if (!((age[temp] > 47 && age[temp] < 58) )){
                  printf("Invalid Age , please enter again :\n");
				  getAge(age);

            }
		    else{

		      break;
		     }
	}
   // printf("Age:%s \n",age);
	strcpy(str,age);


}

void getLocation(char* str)
{
    int temp;
    char Location[32];
printf("Enter your Location : \n");
fflush(stdin);
gets(Location);
for (temp = 0; temp < strlen(Location); temp++) {
            if (!((Location[temp] > 64 && Location[temp] < 91) || (Location[temp] > 96 && Location[temp] < 123)
                  || Location[temp] == 46 || Location[temp] == 32)){
                  printf("Invalid Location , please enter again :\n");
				  getLocation(Location);
            }
		    else{
		      break;
		     }
	}
	//printf("Your Name:%s \n",Name);
    strcpy(str,Location);
}

void getPassword(char* str)
{
    char pasword[10], ch;
 int i;
 printf("Enter the password <any 8 characters>: ");
  for(i=0;i<8;i++)
 {
  ch = getch();
  pasword[i] = ch;
  ch = '*' ;
  printf("%c",ch);
 }
 printf("\n");
pasword[i] = '\0';
 strcpy(str,pasword);


}
void getUsername(char* str1)
{
    int temp;
    char username[32];
    printf("Enter your phone number as username<10 Digits>:\n");
    fflush(stdin);
    gets(username);
    for (temp = 0; temp < strlen(username); temp++) {
            if (!((username[temp] > 47 && username[temp] < 58) )){
                  printf("Invalid Number , please enter again :\n");
				  getUsername(username);

            }
		    else{

		      break;
		     }
	}
    strcpy(str1,username);
    printf("Username:%s\n",str1);
}

void store_data(HashTable* table){
FILE *userPtr;
struct Ht_item user_store;
Ht_item *local_head;

//HashTable *head ;
userPtr = fopen(USER_FILE, "wb");
for (int i=0; i<table->size; i++) {

if (userPtr == NULL) {
        printf("Could not save the data!");
        return;
    }

            if(table->items[i])
            {
                local_head = table->items[i];
               //
     while (local_head != NULL) {
        //temp = local_head;
    char key[32];
    char name[32];
    char age[32];
    char location[32];
    char password[32];
    char User[32];
    strcpy(key,local_head->key);
    strcpy(name,local_head->name);
    strcpy(age,local_head->age);
    strcpy(location,local_head->location);
    strcpy(password,local_head->password);
    strcpy(User,local_head->User);
        //printf("Entered while of store_data\n");

    strcpy(user_store.key,key);
    strcpy(user_store.name,name);
    strcpy(user_store.age,age);
    strcpy(user_store.location,location);
    strcpy(user_store.password,password);
    strcpy(user_store.User,User);
        //struct Ht_item user_store={key,"Allen","20","SC","All@n#0","9988776655"};
        printf("Name:%s\n",local_head->name);
        fwrite(&user_store, sizeof(user_store), 1, userPtr);
        local_head = local_head->next;
        //free(user_store);
        printf("Stored Successfully\n");
}

            }

}
fclose(userPtr);
}

void read_data(HashTable* table)
{
 FILE *userPtr;
 Ht_item user_read;
 userPtr = fopen(USER_FILE, "rb");
 if (userPtr == NULL){
        printf("No records found\n");
 return;
 }
 while (fread(&user_read, sizeof(user_read), 1, userPtr)) {
        /*printf("Name:%s\n",user_read.name);
        printf("Age:%s\n",user_read.age);
        printf("Location:%s\n",user_read.location);
        printf("Username:%s\n",user_read.User); */

 ht_insert(table,user_read.key,user_read.name,user_read.age,user_read.location,user_read.password,user_read.User);
 }
}


int main() {
    HashTable* ht = create_table(CAPACITY);
    //printf("%s",getName());
   /* char* password[10];
    char* username[11];
   char name[32];
    char location[32];
char age[10];
getName(name);
getAge(age);
 getLocation(location);
printf("Name:%s\n",name);
printf("Age:%s\n",age);
printf("Location:%s\n",location);
ht_insert(ht,"1",name,age,location);
print_hashtable(ht); */
  /* ht_insert(ht, "Hel", "Name", "20", "Secunderabad","All@n#0","9988776655");

     ht_insert(ht, "Cau", "Allen", "20", "Secunderabad","Allen$11","8877665544");

     ht_search(ht,"Cau");
     printf("Before Delete");
     print_hashtable(ht);
    ht_delete(ht, "1");
      print_hashtable(ht);
    ht_delete(ht, "Cau");
      print_hashtable(ht);
    ht_delete(ht,"Hel");
    printf("After delete");
    print_hashtable(ht); */
   // getUsername(username);
   //getPassword(password);
   //printf("Your Username: %s\n",username);
   //printf("Your Password: %s\n",password);

   int m1choice;
do{
printf("--------------------------------------------\n\n");
		printf("-----Welcome to the Social Network-----\n");
		printf("\n\t1 - Log In\n");
		printf("\n\t2 - Sign Up\n");
		printf("\n\t3 - Exit\n");
    	printf("\n\t4 - Delete\n");
		printf("\n\tYour choice: ");
		fflush(stdin);
		scanf("%d",&m1choice);

		switch(m1choice){
            case(1):{
                read_data(ht);
                print_hashtable(ht);
                break;
                    }
            case(2):{
                        char key[32]="2";
                        char user[32];
                        char password[32];
                        char name[32];
                        char age[32];
                        char location[32];
                       getUsername(user);
                        getPassword(password);
                        getName(name);
                        getAge(age);
                        getLocation(location);
                        ht_insert(ht,user,name,age,location,password,user);
                        print_hashtable(ht);
                        break;
                    }
            case(3):{

                        store_data(ht);
                        printf("Thank you! Logging Off your Social Network.\n");
                        break;
                    }
            case(4):{
                    char user[32];
                    printf("Enter the username you want to delete:\n");
                    fflush(stdin);
                    gets(user);
                    ht_delete(ht,user);
                    print_hashtable(ht);
                    break;
            }
            default: printf("Invalid Input. Try Again!\n");
		}
}while(m1choice!=3);


   // free_hashtable(ht);

    return 0;
}




