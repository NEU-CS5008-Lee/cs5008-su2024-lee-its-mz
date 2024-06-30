// name: Mingzhe Ou
// email: ou.mi@northeastern.edu

// please start with a copy of your hw7.c, rename it to hw.8
// and then complete the assignment


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#define MAXSTRING 200
#define TABLESIZE 400

// finite state machine states
#define STARTSTATE 0
#define S1 1
#define S2 2
#define S3 3
#define S4 4
#define S5 5
#define S6 6
#define ACCEPTSTATE 10
#define ERRORSTATE 11

typedef struct Node {
  char city[MAXSTRING];
  int population;
  struct Node* next;
} Node;

Node* hashTable1[TABLESIZE];
Node* hashTable2[TABLESIZE];
Node* hashTable3[TABLESIZE];

// check if a character c is a digit
bool isDigit(char c) {
  if ('0' <= c && c <= '9') {
    return true;
  } else {
    return false;
  }
}

// append character c to string s
void appendChar(char* s, char c) {
  char charToStr[2];           // convert char to string
    charToStr[0] = c;
    charToStr[1] = '\0';          // put NUL to terminate string of one character
    strcat(s, charToStr);
}

int hashFunction1(char* str) {
  return strlen(str) % TABLESIZE;
}

int hashFunction2(char* str) {
  int sum = 0;
  while (*str) {
    sum += *str++;
  }
  return sum % TABLESIZE;
}

int hashFunction3(char* str) {
  if (strlen(str) < 2) return 0;
  return (str[0] * str[1]) % TABLESIZE;
}

void insert(Node* hashTable[], char* city, int population, int (*hashFunc)(char*)) {
  int index = hashFunc(city);
  Node* newNode = (Node*)malloc(sizeof(Node));
  strcpy(newNode->city, city);
  newNode->population = population;
  newNode->next = hashTable[index];
  hashTable[index] = newNode;
}

void printHashTable(Node* hashTable[]) {
  for (int i = 0; i < TABLESIZE; i++) {
    printf("[%d]: ", i);
    Node* current = hashTable[i];
    while (current) {
      printf("(%s, %d) -> ", current->city, current->population);
      current = current->next;
    }
    printf("\n");
  }
}


int main () {

  char inputLine[MAXSTRING];   // temporary string to hold input line
  char cityStr[MAXSTRING];     // city name
  int  lineNum;                // line number (city rank)
  int  popInt;                 // population
  int  state;                  // FSM state
  int  nextChar;               // index of next character in input string
  char temp[MAXSTRING];        // temp string to build up extracted strings from input characters
  
  for (int i = 0; i < TABLESIZE; i++) {
    hashTable1[i] = NULL;
    hashTable2[i] = NULL;
    hashTable3[i] = NULL;
  }
 
  FILE* fp;
  fp = fopen("pop.csv","r");

  if (fp != NULL) {
    fgets(inputLine, MAXSTRING, fp); // prime the pump for the first line

    // ***** BEGIN FINTITE STATE MACHINE *****
    
    // STARTSTATE: digit -> S1
    // S1: digit -> S1; , -> S2
    // S2: " -> S3
    // S3: !" -> S3; " -> S4
    // S4: , -> S5
    // S5: " -> S6; ( -> ACCEPTSTATE
    // S6: digit -> S6; , -> S6; " -> ACCEPTSTATE; 
    // ACCEPTSTATE: done!
    // else go to ERRORSTATE
    //
    while (feof(fp) == 0){

      nextChar = 0;
      state = STARTSTATE; 
      strcpy(temp,"");       // temp = ""

      if (nextChar >= strlen(inputLine)){
	// if no input string then go to ERRORSTATE
	state = ERRORSTATE;
      } 

      while ((state != ERRORSTATE) && (state != ACCEPTSTATE)) {
	switch (state) {
	  case STARTSTATE:
	    // look a digit to confirm a valid line
	    if (isDigit(inputLine[nextChar])) {
	      state = S1;
	      appendChar(temp, inputLine[nextChar]);
	    } else {
	      state = ERRORSTATE;
	    }  
	    break;


	  // ADD YOUR CODE HERE
    case S1:
      if (isDigit(inputLine[nextChar])) {
        state = S1;
        appendChar(temp, inputLine[nextChar]);
      } else if (inputLine[nextChar] == ',') {
        state = S2;
        lineNum = atoi(temp);
        strcpy(temp, "");
      } else {
        state = ERRORSTATE;
      }
      break;

      case S2:
      if (inputLine[nextChar] == '"') {
        state = S3;
      } else {
        state = ERRORSTATE;
      }
      break;

    case S3:
      if (inputLine[nextChar] == '"') {
        state = S4;
        strcpy(cityStr, temp);
        strcpy(temp, "");
      } else {
        appendChar(temp, inputLine[nextChar]);
      }
      break;

    case S4:
      if (inputLine[nextChar] == ',') {
        state = S5;
      } else {
        state = ERRORSTATE;
      }
      break;

    case S5:
      if (inputLine[nextChar] == '"') {
        state = S6;
      } else if (inputLine[nextChar] == '(') {
        state = ACCEPTSTATE;
        popInt = 0;  
      } else {
        state = ERRORSTATE;
      }
      break;

    case S6:
      if (isDigit(inputLine[nextChar])) {
        appendChar(temp, inputLine[nextChar]);
      } else if (inputLine[nextChar] == '"') {
        state = ACCEPTSTATE;
        popInt = atoi(temp);  
      } else if (inputLine[nextChar] != ',') {  
        state = ERRORSTATE;
      }
      break;


	  case ACCEPTSTATE:
	    // nothing to do - we are done!
	    break;
	    
	  default:
	    state = ERRORSTATE;
	    break;
	} // end switch

	// advance input
	nextChar++;
	
    }	// end while state machine loop

      // ***** END FINITE STATE MACHINE *****
	  
    if (state == ACCEPTSTATE) {
        insert(hashTable1, cityStr, popInt, hashFunction1);
        insert(hashTable2, cityStr, popInt, hashFunction2);
        insert(hashTable3, cityStr, popInt, hashFunction3);
    }

      // process the line - print out raw line and the parsed fields
      printf("> %.60s\n", inputLine);
      printf("[%.30s]: %d\n", cityStr, popInt);

      // get next line
      fgets(inputLine, MAXSTRING, fp);
      
    } // end while file input loop
    

    fclose(fp);

    printf("Hash Table 1:\n");
    printHashTable(hashTable1);
    printf("\nHash Table 2:\n");
    printHashTable(hashTable2);
    printf("\nHash Table 3:\n");
    printHashTable(hashTable3);
  
  } else {
    printf("File not found!\n");
  }
  
  return 0;
}
