/*
Author: Quianna Numa
Title:  Lab Assignment 10 - Tries
Date:   04/15/2024
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie
{
    int count;
    struct Trie *children[26];
};

struct Trie *createTrie();
void insert(struct Trie *pTrie, char *word);
int numberOfOccurances(struct Trie *pTrie, char *word);
struct Trie *deallocateTrie(struct Trie *pTrie);
int readDictionary(char *filename, char **pInWords);

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
    struct Trie *current = pTrie;
    int len = strlen(word);
    for (int i = 0; i < len; i++) {
        int index = word[i] - 'a';
        if (current->children[index] == NULL) {
            current->children[index] = createTrie();
        }
        current = current->children[index];
    }
    // Mark the end of the word
    current->count++;
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
    struct Trie *current = pTrie;

    if (current == NULL)
        return 0;
    
    int occurences = 0;
    int len = strlen(word);

    for (int i = 0; i < len; i++)
    {
        int index = word[i] - 'a';
        if (current->children[index] == NULL) 
            return 0;
        current = current->children[index];
    }

    return current->count;
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
    if (pTrie == NULL)
        return NULL;

    for (int i = 0; i < 26; i++)
        deallocateTrie(pTrie->children[i]); // Recursively deallocate children

    free(pTrie); // Free current node
    return NULL;
}

// Initializes a trie structure
struct Trie *createTrie()
{
    // Create the struct, not a word.
    struct Trie* myTree = malloc(sizeof(struct Trie));
    myTree->count = 0;

    // Set each pointer to NULLL.
    int i;
    for (i=0; i<26; i++)
        myTree->children[i] = NULL;

    // Return a pointer to the new root.
    return myTree;
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
    FILE *ifp = fopen(filename, "r");
    int n;

    //  number of words in the dictionary
    fscanf(ifp, "%d", &n);

    // Read in each word and insert it.
    for (int i=0; i<n; i++) 
    {
        char word[100];
        fscanf(ifp, "%s", word);

        //  allocate memory for word
        pInWords[i] = malloc(strlen(word) * sizeof(char));
        strcpy(pInWords[i], word);
    }

    return n;
}

int main(void)
{
	char *inWords[256];
	
	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	for (int i=0;i<numWords;++i)
	{
		printf("%s\n",inWords[i]);
	}
	
	struct Trie *pTrie = createTrie();
	for (int i=0;i<numWords;i++)
	{
		insert(pTrie, inWords[i]);
	}
	// parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i=0;i<5;i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");
	return 0;
}