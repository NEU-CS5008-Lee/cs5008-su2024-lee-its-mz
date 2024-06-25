// name: Mingzhe Ou
// email: ou.mi@northeastern.edu

// Hash table with doubly linked list for chaning/
#include <stdio.h>
#include <stdlib.h> 

struct bucket* hashTable = NULL; 
int BUCKET_SIZE = 10; 

// node struct
struct node {

    // Add your code here
    int key;
    int value;
    struct node* next;
    struct node* previous;
};

// bucket struct
struct bucket{

    // Add your code here
    struct node* head;
    struct node* tail;
    //int count;

};

// create a new node
struct node* createNode(int key, int value){

    // Add your code here
    struct node* newNode = (struct node*)malloc(sizeof(struct node));

    newNode->key = key;
    newNode->value = value;
    newNode->next = NULL;
    newNode->previous = NULL;

    return newNode;
}

//  hash function with %
int hashFunction(int key){
    return key % BUCKET_SIZE;
}

//  insert a new key
void add(int key, int value){
    int hashIndex = hashFunction(key);
    
    // Add your code here
    struct node* newNode = createNode(key, value);

    if(hashTable[hashIndex].head == NULL){
        hashTable[hashIndex].head = newNode;
        hashTable[hashIndex].tail = newNode;
    }else{
        hashTable[hashIndex].tail->next = newNode;
        newNode->previous = hashTable[hashIndex].tail;
        hashTable[hashIndex].tail = newNode;
    }

}

// remove a key
void remove_key(int key){
    int hashIndex = hashFunction(key);

    // Add your code here
    struct node* node_to_remove = hashTable[hashIndex].head;

    while(node_to_remove != NULL){
        if(node_to_remove->key == key){
            if(node_to_remove->previous != NULL){ // head of DLL
                node_to_remove->previous->next = node_to_remove->next;
            }else{ // if not the head of DLL
                hashTable[hashIndex].head = node_to_remove->next;
            }

            if(node_to_remove->next != NULL){
                node_to_remove->next->previous = node_to_remove->previous;
            }else{
                hashTable[hashIndex].tail = node_to_remove->previous;
            }

            free(node_to_remove);
            //hashTable[hashIndex].count--;
            return;
        }
        node_to_remove = node_to_remove->next;
    }

}

// search a value using a key
void search(int key){
    int hashIndex = hashFunction(key);
    struct node* iterator = hashTable[hashIndex].head;

    // Add your code here
    while(iterator != NULL){
        if(iterator->key == key){
            //printf("Key: %d, Value: %d\n", key, iterator->value);
            return;
        }
        iterator = iterator->next;
    }
    //printf("Key: %d not found\n", key);
}

void display(){
    struct node* iterator;

    printf("\n========= display start ========= \n");
    for (int i = 0; i<BUCKET_SIZE; i++){
        iterator = hashTable[i].head;
        printf("Bucket[%d] : ", i);
        while (iterator != NULL)
        {
            printf("(key: %d, val: %d)  <-> ", iterator->key, iterator->value);
            iterator = iterator->next;
        }
        printf("\n");
    }
    printf("\n========= display complete ========= \n");
}

int main(){
    hashTable = (struct bucket *)malloc(BUCKET_SIZE * sizeof(struct bucket));

    for (int i = 0; i < BUCKET_SIZE; i++) {
        hashTable[i].head = NULL;
        hashTable[i].tail = NULL;
    }
    
    add(0, 1);
    add(1, 10);
    add(11, 12);
    add(21, 14);
    add(31, 16);
    add(5, 18);
    add(7, 19);

    display();

    remove_key(31);
    remove_key(11);

    display();

    search(11);
    search(1);

    // for (int i = 0; i < BUCKET_SIZE; i++) {
    //     struct node* current = hashTable[i].head;
    //     while (current != NULL) {
    //         struct node* temp = current;
    //         current = current->next;
    //         free(temp);
    //     }
    // }
    // free(hashTable);

    // return 0;
}
