#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 64
#define HASH_FUNCTION(x) ((x) * 2654435761UL)

typedef struct Node {
    char* key;
    char* value;
    struct Node* next;
} Node;

typedef struct HashTable {
    Node** table;
} HashTable;

HashTable* createHashTable() {
    HashTable* table = malloc(sizeof(HashTable));
    table->table = calloc(TABLE_SIZE, sizeof(Node*));
    return table;
}

void insert(HashTable* table, char* key, char* value) {
    unsigned int index = HASH_FUNCTION(key) % TABLE_SIZE;
    Node* node = table->table[index];

    while (node != NULL) {
        if (strcmp(node->key, key) == 0) {
            node->value = value;
            return;
        }
        node = node->next;
    }

    node = malloc(sizeof(Node));
    node->key = key;
    node->value = value;
    node->next = table->table[index];
    table->table[index] = node;
}

char* get(HashTable* table, char* key) {
    unsigned int index = HASH_FUNCTION(key) % TABLE_SIZE;
    Node* node = table->table[index];

    while (node != NULL) {
        if (strcmp(node->key, key) == 0) {
            return node->value;
        }
        node = node->next;
    }

    return NULL;
}

void printTable(HashTable* table) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* node = table->table[i];

        printf("Index %d:", i);
        while (node != NULL) {
            printf(" %s -> %s", node->key, node->value);
            node = node->next;
        }
        printf("\n");
    }
}

void freeTable(HashTable* table) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* node = table->table[i];
        while (node != NULL) {
            Node* next = node->next;
            free(node->key);
            free(node->value);
            free(node);
            node = next;
        }
    }
    free(table->table);
    free(table);
}

int main() {
    HashTable* table = createHashTable();
    insert(table, "key1", "value1");
    insert(table, "key2", "value2");
    printTable(table);
    printf("Value for key1: %s\n", get(table, "key1"));
    freeTable(table);
    return 0;
}