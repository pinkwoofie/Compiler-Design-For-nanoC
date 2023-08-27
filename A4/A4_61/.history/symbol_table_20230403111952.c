#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// #define MAX_SYMBOLS 1000

// typedef enum { VARIABLE, FUNCTION } SymbolType;

// typedef struct {
//     char* name;
//     SymbolType type;
//     int scope;
//     int value;
// } Symbol;

// typedef struct {
//     Symbol symbols[MAX_SYMBOLS];
//     int num_symbols;
//     int scopes[MAX_SYMBOLS];
//     int num_scopes;
// } SymbolTable;

// SymbolTable symbolTable;

// void init_symbol_table() {
//     symbolTable.num_symbols = 0;
//     symbolTable.num_scopes = 0;
//     symbolTable.scopes[0] = 0; // Initialize the symbol table with a global scope
// }

// int enter_scope() {
//     // Create a new scope and return its level
//     int level = symbolTable.num_scopes;
//     symbolTable.scopes[level] = symbolTable.num_symbols;
//     symbolTable.num_scopes++;
//     return level;
// }

// void exit_scope() {
//     // Remove the current scope and return to the previous one
//     int current_scope = symbolTable.num_scopes - 1;
//     int previous_scope = symbolTable.scopes[current_scope - 1];
//     symbolTable.num_symbols = previous_scope;
//     symbolTable.num_scopes--;
// }

// int current_scope() {
//     // Return the current scope level
//     return symbolTable.num_scopes - 1;
// }

// Symbol* lookup_symbol(char* name, int scope) {
//     // Search for a symbol with the given name in the given scope and all outer scopes
//     int i, j;
//     for (i = scope; i >= 0; i--) {
//         int start = i == 0 ? 0 : symbolTable.scopes[i - 1];
//         int end = symbolTable.scopes[i];
//         for (j = start; j < end; j++) {
//             if (strcmp(symbolTable.symbols[j].name, name) == 0) {
//                 return &symbolTable.symbols[j];
//             }
//         }
//     }
//     // Symbol not found
//     return NULL;
// }

// Symbol* insert_symbol(char* name, SymbolType type, int scope) {
//     // Create a new symbol and add it to the symbol table
//     if (symbolTable.num_symbols >= MAX_SYMBOLS) {
//         printf("Error: symbol table overflow\n");
//         exit(1);
//     }
//     Symbol* symbol = &symbolTable.symbols[symbolTable.num_symbols];
//     symbol->name = strdup(name);
//     symbol->type = type;
//     symbol->scope = scope;
//     symbol->value = 0;
//     symbolTable.num_symbols++;
//     return symbol;
// }

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_TABLE_SIZE 1000

typedef struct symbol {
    char *name;
    int value;
    int scope;
    struct symbol *next;
    struct symbol *prev;
} symbol;

symbol *hash_table[HASH_TABLE_SIZE];
symbol *current_scope = NULL;

unsigned int jenkins_hash(char *key, size_t len, unsigned int initval) {
    unsigned int hash = initval;
    size_t i;

    for (i = 0; i < len; i++) {
        hash += key[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }

    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);

    return hash;
}

symbol *add_symbol(char *name) {
    int index = jenkins_hash(name, strlen(name), 0) % HASH_TABLE_SIZE;
    symbol *s = malloc(sizeof(symbol));
    s->name = strdup(name);
    s->value = 0;
    s->scope = current_scope->scope;
    s->prev = NULL;
    s->next = hash_table[index];
    if (hash_table[index] != NULL) {
        hash_table[index]->prev = s;
    }
    hash_table[index] = s;
    return s;
}

symbol *lookup(char *name) {
    symbol *s = current_scope;
    while (s != NULL) {
        int index = jenkins_hash(name, strlen(name), 0) % HASH_TABLE_SIZE;
        symbol *curr = hash_table[index];
        while (curr != NULL) {
            if (strcmp(curr->name, name) == 0 && curr->scope <= s->scope) {
                return curr;
            }
            curr = curr->next;
        }
        s = s->prev;
    }
    return NULL;
}

void enter_scope() {
    symbol *s = malloc(sizeof(symbol));
    s->name = NULL;
    s->value = 0;
    s->scope = current_scope != NULL ? current_scope->scope + 1 : 0;
    s->prev = current_scope;
    s->next = NULL;
    current_scope = s;
}

void exit_scope() {
    symbol *s = current_scope;
    while (s != NULL) {
        symbol *next = s->next;
        if (s->name != NULL) {
            int index = jenkins_hash(s->name, strlen(s->name), 0) % HASH_TABLE_SIZE;
            if (s->prev != NULL) {
                s->prev->next = s->next;
            } else {
                hash_table[index] = s->next;
            }
            if (s->next != NULL) {
                s->next->prev = s->prev;
            }
            free(s->name);
            free(s);
        }
        s = next;
    }
    current_scope = current_scope->prev;
}


#endif // SYMBOL_TABLE_H
