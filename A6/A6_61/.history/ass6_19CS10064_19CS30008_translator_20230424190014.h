/**
* Vanshita Garg | 19CS10064
* Ashutosh Kumar Singh | 19CS30008
* Compilers Laboratory
* Assignment 6
*
* Header file for translation
*/

#ifndef __TRANSLATOR_H
#define __TRANSLATOR_H

#include <iostream>
#include <vector>
#include <list>
#include <map>
using namespace std;

/*
    Sizes for basic data types, according to x86_64 architecture.
    To target a different platform, the sizes can be changed here itself.

    List of sizes
    -------------
    void        0 bytes
    function    0 bytes
    char        1 byte
    int         4 bytes
    pointer     8 bytes
    float       8 bytes

*/

#define __VOID_SIZE 0
#define __FUNCTION_SIZE 0
#define __CHARACTER_SIZE 1
#define __INTEGER_SIZE 4
#define __POINTER_SIZE 4
#define __FLOAT_SIZE 8

/*
    An enum for all data types
*/
typedef enum {
    VOID,
    BOOL,
    CHAR,
    INT,
    FLOAT,
    ARRAY,
    POINTER,
    FUNCTION
} DataType;

/*
    An enum for all opcodes
*/
typedef enum  {
    ADD, SUB, MULT, DIV, MOD, SL, SR, 
    BW_AND, BW_OR, BW_XOR, 
    BW_U_NOT ,U_PLUS, U_MINUS, REFERENCE, DEREFERENCE, U_NEG, 
    GOTO_EQ, GOTO_NEQ, GOTO_GT, GOTO_GTE, GOTO_LT, GOTO_LTE, IF_GOTO, IF_FALSE_GOTO, 
    CtoI, ItoC, FtoI, ItoF, FtoC ,CtoF, 
    ASSIGN, GOTO, RETURN, PARAM, CALL, ARR_IDX_ARG, ARR_IDX_RES, FUNC_BEG, FUNC_END, L_DEREF
} opcode;


/*
    Forward Class Declarations
    --------------------------
    symbol          Represents an element(entry) in the symbol table
    symbolType      Represents the type of an element in the symbol table
    symbolValue     Represents the value stored by a symbol in the symbol table
    symbolTable     Represents the symbol table data structure itself
    quad            Denotes a quad in the Three Address Code translation
    quadArray       Denotes the entire list of quads for lazy spitting
*/
class symbol;
class symbolType;
class symbolValue;
class symbolTable;

class quad;
class quadArray;


/*
    External variables and methods generated by bison
*/
extern char* yytext;
extern int yyparse();


/*
    Class to represent the type of an element in the symbol table
    class symbolType
    ----------------
    Member Variables:
        pointers: int               Useful for pointer types
        type: DataType              The type of the symbol
        nextType: symbolType        For arrays and pointers, it points to the type of the elements of the array or the pointer
        dims: vector<int>           For arrays, it stores the dimensions of the array
*/
class symbolType {
public:
    int pointers;
    DataType type;
    DataType nextType;
    vector<int> dims;
};


/*
    Class to represent the value of an element in the symbol table
    class symbolValue
    ------------------
    Member Variables:
        i: int                 For integers, it stores the value
        f: float               For floats, it stores the value
        c: char                For characters, it stores the value
        p: void*               For pointers, it stores the value
*/
class symbolValue {
public:
    int i;
    char c;
    float f;
    void* p;

    void setInitVal(int val);
    void setInitVal(char val);
    void setInitVal(float val);
};


/*
    Class to represent an element(entry) in the symbol table
    class symbol
    ------------
    Member Variables:
        name: string                The name of the symbol
        type: symbolType            Type of the symbol
        initVal: symbolValue*       Initial value of the symbol, if any
        size: int                   Size of the symbol(element)
        offset: int                 Offset of the symbol in the symbol table
        nestedTable: symbolTable*   Pointer to a nested symbol table, if any (useful for functions and blocks)
    Member Methods:
        symbol()
        - Constructor
*/
class symbol {
public:
    string name;
    symbolType type;
    symbolValue* initVal;
    int size;
    int offset;
    symbolTable* nestedTable;

    symbol();
};


/*
    Class to represent the symbol table data structure
    class symbolTable
    ------------
    Member Variables:
        table: map<string, symbol*>     List of symbols hashed using their names
        symbols: vector<symbol*>        List of all symbols present in the symbol table
        tempCount: int                  Count of temporary variables generated for the symbol table
        parent: symbolTable*            Pointer to the parent of the symbol table, NULL for the global symbol table
    Member Methods:
        symbolTable()
        - Constructor
        lookup(string name, DataType t = INT, int pc = 0): symbol*
        - A method to lookup an id (given its name or lexeme) in the symbol table. If the id exists, the entry is returned, otherwise a new entry is created.
        searchGlobal(string name): symbol*
        - A method to search for an id in the global symbol table. If the id exists, the entry is returned, otherwise NULL is returned.
        gentemp(DataType t = INT): string
        - A method to generate a new temporary, insert it to the symbol table, and return a pointer to the entry
        print(): void
        - Prints the symbol table in a suitable fashion
*/
class symbolTable {
public:
    map<string, symbol*> table;
    vector<symbol*> symbols;
    int offset;
    static int tempCount;

    symbolTable();
    symbol* lookup(string name, DataType t = INT, int pc = 0);
    symbol* searchGlobal(string name);
    string gentemp(DataType t = INT);

    void print(string tableName);
};


/*
    Class to denote a quad in the Three Address Code translation
    class quad
    ------------
    Member Variables:
        op: string          Operator in the three address code
        arg1: string        First argument in the three address code
        arg2: string        Second argument in the three address code
        result: string      Result of the three address code
    Member Methods:
    quad(string, string, string, opcode)
    - Constructor
    print(): void
    - Returns a formatted string to help in printing the quad
*/
class quad {
public:
    opcode op;
    string arg1;
    string arg2;
    string result;

    quad(string, string, string, opcode);

    string print();
};


/*
    Class to denote the entire list of quads for lazy spitting
    class quadArray
    ------------
    Member Variables:
        quads: vector<quads>    A vector of all the quads generated
    Member Methods:
        print(): void
        - Prints the entire list of quads
*/
class quadArray {
public:
    vector<quad> quads;

    void print();
};


/*
    Class to represent a parameter
    class param
    ------------
    Member Variables:
        name: string        Name of the parameter
        type: DataType      Type of the parameter
*/
class param {
public:
    string name;
    symbolType type;
};


/*
    Class to denote an expression
    class expression
    ------------
    Member Variables:
        instr: int                  The instruction number of the expression
        type: DataType              Type of the expression
        loc: string                 The symbol table entry 
        truelist: list<int>         Truelist for boolean expressions
        falselist: list<int>        Falselist for boolean expressions
        nextlist: list<int>         Nextlist for statement expressions
        fold: int                   Useful for arrays and pointers
        folder: string*             Useful for arrays and pointers
    Member Methods:
        expression()
        - Constructor
*/
class expression {
public:
    int instr;
    DataType type;
    string loc;
    list<int> truelist;
    list<int> falselist;
    list<int> nextlist;
    int fold;
    string* folder;

    expression();
};


/*
    Class to represent a declaration
    class declaration
    ------------
    Member Variables:
        name: string                Name of the declaration
        pointers: int               Number of pointers
        type: DataType              Type of the declaration
        li: vector<int>             List of instructions for the declaration
        initVal: expression*        Initial value of the declaration
        pc: int                     Useful for pointers and arrays
*/
class declaration {
public:
    string name;
    int pointers;
    DataType type;
    DataType nextType;
    vector<int> li;
    expression* initVal;
    int pc;
};


/*
    An overloaded method to add a (newly generated) quad of the form: result = arg1 op arg2 where op usually is a binary operator. 
    If arg2 is missing, op is unary. If op also is missing, this is a copy instruction.
    It is overloaded for different types of quads (int, float or string)
*/
void emit(string result, string arg1, string arg2, opcode op);
void emit(string result, int constant, opcode op);
void emit(string result, char constant, opcode op);
void emit(string result, float constant, opcode op);


/*
    A global function to create a new list containing only i, an index into the array of quads, 
    and to return a pointer to the newly created list
*/
list<int> makelist(int i);

/*
    A global function to concatenate two lists list1 and list2 and to return a pointer to the concatenated list
*/
list<int> merge(list<int> list1, list<int> list2);

/*
    A global function to insert address as the target label for each of the quads on the list l
*/
void backpatch(list<int> l, int address);

/*
    Converts a symbol of one type to another and returns a pointer to the converted symbol
*/
void convertToType(expression* arg, expression* res, DataType toType);

void convertToType(string t, DataType to, string f, DataType from);

/*
    Converts an int to a bool and adds required attributes
*/
void convertIntToBool(expression* expr);

/*
    Auxiliary function to get the size of a type
*/
int sizeOfType(DataType t);

/*
    Auxiliary function to print a type
*/
string checkType(symbolType t);

/*
    Auxiliary function to get the initial value of a symbol
*/
string getInitVal(symbol* sym);

#endif