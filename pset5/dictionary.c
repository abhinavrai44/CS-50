/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "dictionary.h"

// trie structure to store words
typedef struct trie
{
    bool wordcheck;
    struct trie* children[27];
} 
trie;

trie* firstnode;

//no of words stored in dictionary
int wordcount = 0;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
	// TODO
	
	// set a trie* to point to firstNode
	trie* currentnode = firstnode;
	
	//loop through word
	int i = 0;
	while(word[i] != '\0')
		{
	        char character = word[i];
        
        	// find apostrophes
	        if (word[i] == '\'')
		        {
	            	character = 122 + 1;
		        }
		
	        int index = tolower(character) - 97; 	//index to check for child node
	       
        	// go to childIndex if not NULL, else return false
	        if (currentnode->children[index] != NULL)
	        	{
		        currentnode = currentnode->children[index];
			i++;
			}  
	        else
		        {
      	            	return false;
		        } 
		} 
		// close for loop
    
	// if word exists, return true.
    	if (currentnode->wordcheck == true)
		{
	        return true;
		}
	else
		{
		return false;
		}
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
	// TODO	
	FILE *f = fopen(dictionary, "r");
	if (f == NULL)
		{
		return false;
		}
	
	firstnode = malloc(sizeof(trie));	    
	int character = 0;

	trie* currentnode = NULL;
	//loop through dictionary until end of file EOF
        while(fgetc(f) != EOF)
        	{
        	fseek(f, -1, SEEK_CUR);

	        // set cursor to firstNode
	        currentnode = firstnode;

		//loop until end of word
	        for (character = fgetc(f); character != '\n'; character = fgetc(f))
		        {    
		        // if apostrophes, set character to z+1
		        if (character == '\'')
		                {
		                character = 123;
			        }

               		// If the character is not in trie...
	                if (currentnode->children[character - 97] == NULL)
				{
		                // ... malloc a new node and go there
		                currentnode->children[character - 97] = malloc(sizeof(trie));
		                currentnode = currentnode->children[character - 97];
			        }
		        else // ... but if it is, go to the existing node
			        {
		                currentnode = currentnode->children[character - 97];
			        }
			}
		
		currentnode->wordcheck = true;
	        wordcount++;
		}

	fclose(f);
	return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // TODO
    return wordcount;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
	// TODO
	// free each of the children if not NULL
	for(int i = 0; i < 27; i++)
	    	{
		trie* currentnode = firstnode;
	        if (currentnode->children[i] != NULL)
		        {
		        free(currentnode->children[i]);  
		        }      
		}
	return true;   
}
