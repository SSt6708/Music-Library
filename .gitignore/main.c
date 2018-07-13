//
// APS105 Lab 8 Lab8.c
//
// This is a program written to maintain a personal music library, 
// using a linked list to hold the songs in the library.
//
// Author: <Your Name Goes Here>
// Student Number: <Your Student Number Goes Here>
//

#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

// A node in the linked list

// Each string in the node is declared as a character pointer variable,
// so they need to be dynamically allocated using the malloc() function,
// and deallocated using the free() function after use.

typedef struct node {
    char *artist ;
    char *songName ;
    char *genre ;
    struct node *nextNode ;
} Node;

// Declarations of linked list functions
//
// DECLARE YOUR LINKED-LIST FUNCTIONS HERE
//



// Declarations of support functions
// See below the main function for descriptions of what these functions do

void inputStringFromUser( char prompt[], char s[], int arraySize ) ;
void songNameDuplicate( char songName[] ) ;
void songNameFound( char songName[] ) ;
void songNameNotFound( char songName[] ) ;
void songNameDeleted( char songName[] ) ;
void artistFound( char artist[] ) ;
void artistNotFound( char artist[] ) ;
void printMusicLibraryEmpty( void ) ;
void printMusicLibraryTitle( void ) ;

const int MAX_LENGTH = 1024;
Node *head = NULL;  



bool checkifDuplicate( char song[]){ 
    Node *current = head;
    while( current != NULL){
        if ( strcmp(current->songName, song) == 0) 
            return true; 
            else 
                current= current->nextNode; 
    } 
    return false;  
} 

void insert( char song[], char art[], char gen[]){ 
    Node *ins= (Node*) malloc( sizeof(Node)); 
    ins->songName =  (char*) malloc( MAX_LENGTH * sizeof(char));
    ins->artist =  (char*) malloc( MAX_LENGTH * sizeof(char));
    ins->genre =  (char*) malloc( MAX_LENGTH * sizeof(char)); 
    
    strcpy( ins->songName, song);
    strcpy( ins->artist, art);
    strcpy( ins->genre, gen); 
    
    Node*current = head; 
    Node* previous = head; 
    
    if(!head) 
        head= ins; 
        else if (strcmp(ins->songName,head->songName)<0){ //if not yet entered before
            head= ins; 
            head->nextNode=current;  
        } 
        else {  
            current= current->nextNode; //check if its NUll or not
            while(current!=NULL){  
                if (strcmp( current->songName,ins->songName)<0){ 
                    previous=previous->nextNode; 
                    current=current->nextNode;
                } 
                else{ 
                    previous->nextNode=ins; 
                    ins->nextNode=current; 
                    return; 
                } 
            }
            previous->nextNode= ins;
            ins->nextNode=current; 
        }
    }
        

void printList(void){ 
    Node*current=head;
if(!head)
    printMusicLibraryEmpty(); 
    else {
        printMusicLibraryTitle(); 
        
        while(current!=NULL){ //goes through every node to print
            printf("\n");
            printf("%s\n", current->songName);
            printf("%s\n", current->artist);
            printf("%s\n", current->genre); 
            
            current=current->nextNode;
        }

    }
}

void searching(char song[]){ 
    Node*current=head; 
    while(current!=NULL){ 
        if(strcmp(song, current->songName)==0){ 
            songNameFound( song ); 
            printf("\n");
            printf("%s\n",current->songName);
            printf("%s\n",current->artist);
            printf("%s\n",current->genre);  
            return;
        }
            else 
                current=current->nextNode; 
    }
} 

void deleteSong( char song[]){ 
    Node *current=head; 
    Node *previous=head; 
    Node *ptr;  
    // deleting first node
    if(strcmp(song,head->songName)==0){ 
        ptr=head; 
		head=head->nextNode;
        free(ptr->songName); 
        free(ptr->artist); 
        free(ptr->genre);
        free(ptr);
         
    } 
    else{ 
        current= head->nextNode;
        
    while(current!=NULL){ 
        if(strcmp(song, current->songName)==0){ 
            previous->nextNode=current->nextNode;
			free(current->songName); 
            free(current->artist); 
            free(current->genre);
            free(current); 
			return;
        }
            else {
                previous=previous->nextNode;
                current=current->nextNode; //look for every node 
			}
		}
	} 
}

void quittiing(void){ 
    Node*current=head; 
    while(current!=NULL){ 
            songNameDeleted( current->songName );
            free(current->songName); 
            free(current->artist); 
            free(current->genre);
            free(current);
            current=current->nextNode; 
    } 
    printMusicLibraryEmpty();
}

int main( void ) {
    // Declare the head of the linked list.
    //   ADD YOUR STATEMENT(S) HERE
 
    // Announce the start of the program
    printf( "Personal Music Library.\n\n" ) ;
    printf( "%s", "Commands are I (insert), D (delete), S (search by song name),\n"
         "P (print), Q (quit).\n" ) ;
    
    char response ;
    char input[ MAX_LENGTH + 1 ] ;
    do {
        inputStringFromUser( "\nCommand", input, MAX_LENGTH ) ;

        // Response is the first character entered by user.
        // Convert to uppercase to simplify later comparisons.
        response = toupper( input[0] ) ;

        if( response == 'I' ) {
            // Insert a song into the linked list.
            // Maintain the list in alphabetical order by song name.
            //   ADD STATEMENT(S) HERE
            char song[MAX_LENGTH+1], artist[MAX_LENGTH+1], genre[MAX_LENGTH+1],prompt[MAX_LENGTH+1];
            // USE THE FOLLOWING STRINGS WHEN PROMPTING FOR DATA:
                char *promptName = "Song name" ;
                char *promptArtist =  "Artist" ;
                char *promptGenre = "Genre" ;
                 
                inputStringFromUser(promptName, song, MAX_LENGTH); 
                inputStringFromUser(promptArtist, artist, MAX_LENGTH);
                inputStringFromUser(promptGenre, genre, MAX_LENGTH); 
                
                if(checkifDuplicate(song)) 
                    songNameDuplicate( song); 
                    else 
                        insert( song, artist, genre); 
                    
        }
        else if( response == 'D' ) {
            // Delete a song from the list.
            char song[MAX_LENGTH+1];
            char *prompt = "\nEnter the name of the song to be deleted" ;
            inputStringFromUser(prompt, song, MAX_LENGTH); 
            
            if(checkifDuplicate(song)){
            deleteSong(song); 
            songNameDeleted(song); 
            } 
            else 
                songNameNotFound( song);
            //   ADD STATEMENT(S) HERE

        }
        else if( response == 'S' ) {
            // Search for a song by its name.
            char song[MAX_LENGTH+1];
            char *prompt = "\nEnter the name of the song to search for" ;
            inputStringFromUser(prompt, song, MAX_LENGTH);
                
                if(checkifDuplicate(song))
                searching(song); 
                else 
                    songNameNotFound(song);
            //   ADD STATEMENT(S) HERE

        }
        else if( response == 'P' ) { 
            printList();
            // Print the music library.

            //   ADD STATEMENT(S) HERE

        }
        else if( response == 'Q' ) {
            ; // do nothing, we'll catch this below
        }
        else {
            // do this if no command matched ...
            printf( "\nInvalid command.\n" ) ;
        }
    } while( response != 'Q' ) ;
            quittiing();
    // Delete the entire linked list.
    //   ADD STATEMENT(S) HERE

    // Print the linked list to confirm deletion.
    //   ADD STATEMENT(S) HERE

    return 0 ;
}

// Support Function Definitions

// Prompt the user for a string safely, without buffer overflow
void inputStringFromUser(char prompt[], char s[], int maxStrLength) {
    int i = 0;
    char c;
    
    printf( "%s --> ", prompt ) ;
    while( i < maxStrLength && (c = getchar()) != '\n' )
        s[i++] = c ;
    s[i] = '\0' ;
}

// Function to call when the user is trying to insert a song name 
// that is already in the personal music library.
void songNameDuplicate( char songName[] ) {
    printf( "\nA song with the name '%s' is already in the music library.\n"
            "No new song entered.\n", songName);
}

// Function to call when a song name was found in the personal music library.
void songNameFound( char songName[] ) {
    printf( "\nThe song name '%s' was found in the music library.\n",
           songName ) ;
}

// Function to call when a song name was not found in the personal music library.
void songNameNotFound( char songName[] ) {
    printf( "\nThe song name '%s' was not found in the music library.\n",
           songName);
}

// Function to call when a song name that is to be deleted
// was found in the personal music library.
void songNameDeleted( char songName[] ) {
    printf( "\nDeleting a song with name '%s' from the music library.\n",
           songName);
}

// Function to call when printing an empty music library.
void printMusicLibraryEmpty(void) {
    printf( "\nThe music library is empty.\n" ) ;
}

// Function to call to print a title when the entire music library is printed.
void printMusicLibraryTitle(void) {
    printf( "\nMy Personal Music Library: \n" ) ;
}

// Add your functions below this line.

//   ADD STATEMENT(S) HERE
