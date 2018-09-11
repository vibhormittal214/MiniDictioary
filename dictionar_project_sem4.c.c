#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define ARRAY_SIZE(a) sizeof(a)/sizeof(a[0])
#define ALPHABET_SIZE (26)
#define CHAR_TO_INDEX(c) ((int)c - (int)'a')
// trie node
struct TrieNode1
{
    struct TrieNode1 *children[ALPHABET_SIZE];
    struct TrieNode1 *meaning[100];
    bool isEndOfWord;//has the word ended
};
typedef struct TrieNode1 TrieNode;
// Returns new trie node initializing all of them to null
TrieNode *getNode(void)
{
    TrieNode *pNode = NULL;

    pNode = (TrieNode *)malloc(sizeof(TrieNode));

    if (pNode)
    {
        int i;

        pNode->isEndOfWord = false;

        for (i = 0; i < ALPHABET_SIZE; i++)
            pNode->children[i] = NULL;
    }

    return pNode;
}

// If not present, inserts key into trie
// If the key is prefix of trie node, just marks leaf node
void insert(TrieNode *root, const char *key,char *mean)
{
    int level;
    int length = strlen(key);
    int index;

    TrieNode *pWORD = root;

    for (level = 0; level < length; level++)
    {
        index = CHAR_TO_INDEX(key[level]);
        if (!pWORD->children[index])
            pWORD->children[index] = getNode();
        if(level==length-1)
        {
            strcpy(pWORD->children[index]->meaning,mean);
        }
        pWORD = pWORD->children[index];
    }

    // mark last node as leaf
    pWORD->isEndOfWord = true;
}

// Returns true if key presents in trie, else false
void search(TrieNode *root, const char *key)
{
    int level;
    int length = strlen(key);
    int index;
    char *meanning[100];
    TrieNode *pCrawl = root;
    for (level = 0; level < length; level++)
    {
        index = CHAR_TO_INDEX(key[level]);
        if(level==length-1)
        {
            strcpy(meanning,pCrawl->children[index]->meaning);
        }

        if (!pCrawl->children[index])
            break;


        pCrawl = pCrawl->children[index];
    }
    if(pCrawl != NULL && pCrawl->isEndOfWord)
    {
        printf("\n THE MEANING OF THE WORD IS-->  ");
        printf("%s",meanning);
    }
    else
    {
        printf("\n SORRY NO WORD FOUND");
    }
}

// Driver
int main()
{
    // Input keys (use only 'a' through 'z' and lower case)
    char keys[][26] = {"car","cart","camera","hello","apple"};
    char mean[][50]={"a vehicle","an object to carry things","a device to take photos","used as greeting","a fruit"};
    char word[500];
    char ch='y';
    TrieNode *root = getNode();
    // Construct trie
    int i;
    for (i = 0; i < ARRAY_SIZE(keys); i++)
        insert(root, keys[i],mean[i]);
    printf("\n THE LOADING OF THE DICTIONARY HAS BEEN COMPLETED.");
    printf("\n YOU CAN CONTINUE WITH FINDING THE MEANINGS");
    printf("\n");
    while(ch=='y'||ch=='Y')
    {
       printf("\n Enter the word to be searched   ");
       printf("\n");
       scanf("%s",word);
       for(i = 0; word[i]; i++)
       {
            word[i] = tolower(word[i]);
       }
       search(root,word);
       printf("\n");
       printf("\n TO FIND MORE WORDS ENTER-->Y ELSE ENTER ANY OTHER CHARACTER   ");
       scanf(" %c", &ch);
    }
    printf("\n THANKS FOR USING THE DICTIONARY");
  return 0;
}
