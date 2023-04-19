#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie node structure
typedef struct Trie {
    int count; 
    struct Trie *children[26];
} Trie;

// Create a new Trie node to create the Trie
struct Trie* createNode() {
    struct Trie *pNode = NULL;
    pNode = (struct Trie *)calloc(1,sizeof(struct Trie));
    return pNode;
}

// Inserting into the Trie
void insert(struct Trie **ppTrie, char *word) {
    if (*ppTrie == NULL) {
        *ppTrie = createNode();
    }

    Trie *temp = *ppTrie;
    int length = strlen(word);
    for (int i = 0; i < length; i++) {
        int index = word[i] - 'a';
        if (temp->children[index] == NULL) {
            temp->children[index] = calloc(1, sizeof(Trie));
        }
        temp = temp->children[index];
    }
    temp->count++;
}

// Find the number of occurrences of a word in the Trie
int numberOfOccurrences(struct Trie *pTrie, char *word) {
    struct Trie *temp = pTrie;
    int length = strlen(word);
    for (int i = 0; i < length; i++) {
        int index = word[i] - 'a';
        if (temp->children[index] == NULL) {
            return 0;
        }
        temp = temp->children[index];
    }
    return temp->count;
}

// Deallocate the Trie
struct Trie *deallocateTrie(struct Trie *pTrie) {
    if (pTrie != NULL) {
        for (int i = 0; i < 26; i++) {
            pTrie->children[i] = deallocateTrie(pTrie->children[i]);
        }
        free(pTrie);
    }
    return NULL;
}

int main(void) {
    struct Trie *trie = NULL;

    // Insert words into the Trie
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    int numWords = sizeof(pWords) / sizeof(char *);
    for (int i = 0; i < numWords; i++) {
        insert(&trie, pWords[i]);
    }

    // Find the number of occurrences of each word in the Trie
    for (int i = 0; i < numWords; i++) {
        printf("%s : %d\n", pWords[i], numberOfOccurrences(trie, pWords[i]));
    }

    // Deallocate the Trie
    trie = deallocateTrie(trie);
    if (trie != NULL) {
        printf("There is an error in this program\n");
    }

    return 0;
}

