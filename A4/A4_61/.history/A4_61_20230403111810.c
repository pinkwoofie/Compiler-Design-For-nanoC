%{
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

%}

%token INTEGER
%token PLUS
%token MINUS
%token LPAREN
%token RPAREN
%token END

%left PLUS MINUS

%%

statement:
    expression END
    | END
    ;

expression:
    INTEGER
    | expression PLUS expression
    | expression MINUS expression
    | LPAREN expression RPAREN
    ;

%%

int main() {
    enter_scope();

    yyparse();

    exit_scope();

    return 0;
