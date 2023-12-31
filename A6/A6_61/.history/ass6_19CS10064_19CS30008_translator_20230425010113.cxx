/**
* Vanshita Garg | 19CS10064
* Ashutosh Kumar Singh | 19CS30008
* Compilers Laboratory
* Assignment 6
*
* Source file for translation
*/

#include "ass6_19CS10064_19CS30008_translator.h"
#include <iomanip>
using namespace std;

// Initialize the global variables
int nextinstr = 0;

// Intiailize the static variables
int symbolTable::tempCount = 0;
map<string,vector<string>>funcParam;
map<string,string> returnType;

quadArray quadList;
symbolTable globalST;
symbolTable* ST;


// Implementations of constructors and functions for the symbolValue class
void symbolValue::setInitVal(int val) {
    c = i = val;
    p = NULL;
}

void symbolValue::setInitVal(char val) {
    c = i = val;
    p = NULL;
}



// Implementations of constructors and functions for the symbol class
symbol::symbol(): nestedTable(NULL) {}


// Implementations of constructors and functions for the symbolTable class
symbolTable::symbolTable(): offset(0) {}

symbol* symbolTable::lookup(string name, DataType t, int pc) {
    if(table.count(name) == 0) {
        symbol* sym = new symbol();
        sym->name = name;
        sym->type.type = t;
        sym->offset = offset;
        sym->initVal = NULL;

        if(pc == 0) {
            sym->size = sizeOfType(t);
            offset += sym->size;
        }
        else {
            sym->size = __POINTER_SIZE;
            sym->type.nextType = t;
            sym->type.pointers = pc;
            sym->type.type = ARRAY;
        }
        if(checkType(sym->type) == "int" || checkType(sym->type).substr(0,4) == "int[") offset += offset%4;
        symbols.push_back(sym);
        table[name] = sym;
    }
    return table[name];
}

symbol* symbolTable::searchGlobal(string name) {
    return (table.count(name) ? table[name] : NULL);
}

string symbolTable::gentemp(DataType t) {
    // Create the name for the temporary
    string tempName = "t" + to_string(symbolTable::tempCount++);
    
    // Initialize the required attributes
    symbol* sym = new symbol();
    sym->name = tempName;
    sym->size = sizeOfType(t);
    sym->offset = offset;
    sym->type.type = t;
    sym->initVal = NULL;

    offset += sym->size;
    symbols.push_back(sym);
    table[tempName] = sym;  // Add the temporary to the symbol table

    return tempName;
}

void symbolTable::print(string tableName) {
    for(int i = 0; i < 120; i++) {
        cout << '-';
    }
    cout << endl;
    cout << "Symbol Table: " << setfill(' ') << left << setw(50) << tableName << endl;
    for(int i = 0; i < 120; i++)
        cout << '-';
    cout << endl;

    // Table Headers
    cout << setfill(' ') << left << setw(25) <<  "Name";
    cout << left << setw(25) << "Type";
    cout << left << setw(20) << "Initial Value";
    cout << left << setw(15) << "Size";
    cout << left << setw(15) << "Offset";
    cout << left << "Nested" << endl;

    for(int i = 0; i < 120; i++)
        cout << '-';
    cout << endl;

    // For storing nested symbol tables
    vector<pair<string, symbolTable*>> tableList;

    // Print the symbols in the symbol table
    for(int i = 0; i < (int)symbols.size(); i++) {
        symbol* sym = symbols[i];
        string tp = "";
        if(sym->type.type == ARRAY)
        {
            tp += "array(";
            vector<int> dim = sym->type.dims;
            for(int i = 0; i < (int)dim.size(); i++) {
                if(dim[i])
                    tp += to_string(dim[i]);
            }
            if(sym->type.nextType == CHAR)
                tp += ",char)";
            else if(sym->type.nextType == INT)
                tp += ",int)";
        }
        else if(sym->type.type == FUNCTION)
        {
            tp.push_back('(');
            for(int i = 0;i<funcParam[sym->name].size();i++)
            {
                tp += funcParam[sym->name][i];
                if(i != funcParam[sym->name].size() - 1)
                    tp.push_back(',');
            }
            tp.push_back(')');
            tp += "-->";
            tp += returnType[sym->name];
        }
        else tp += checkType(sym->type);
        cout << left << setw(25) << sym->name;
        cout << left << setw(25) << tp;
        cout << left << setw(20) << getInitVal(sym);
        cout << left << setw(15) << sym->size;
        cout << left << setw(15) << sym->offset;
        cout << left;

        if(sym->nestedTable != NULL) {
            string nestedTableName = tableName + "." + sym->name;
            cout << nestedTableName << endl;
            tableList.push_back({nestedTableName, sym->nestedTable});
        }
        else
            cout << "NULL" << endl;
    }

    for(int i = 0; i < 120; i++)
        cout << '-';
    cout << endl << endl;

    // Recursively call the print function for the nested symbol tables
    for(vector<pair<string, symbolTable*>>::iterator it = tableList.begin(); it != tableList.end(); it++) {
        pair<string, symbolTable*> p = (*it);
        p.second->print(p.first);
    }

}


// Implementations of constructors and functions for the quad class
quad::quad(string res_, string arg1_, string arg2_, opcode op_): op(op_), arg1(arg1_), arg2(arg2_), result(res_) {}

string quad::print() {
    string out = "";
    if(op >= ADD && op <= BW_XOR) {                 // Binary operators
        out += (result + " = " + arg1 + " ");
        switch(op) {
            case ADD: out += "+"; break;
            case SUB: out += "-"; break;
            case MULT: out += "*"; break;
            case DIV: out += "/"; break;
            case MOD: out += "%"; break;
            case BW_AND: out += "&"; break;
        }
        out += (" " + arg2);
    }
    else if(op >= BW_U_NOT && op <= U_NEG) {        // Unary operators
        out += (result + " = ");
        switch(op) {
            case U_PLUS: out += "+"; break;
            case U_MINUS: out += "-"; break;
            case REFERENCE: out += "&"; break;
            case DEREFERENCE: out += "*"; break;
            case U_NEG: out += "!"; break;
        }
        out += arg1;
    }
    else if(op >= GOTO_EQ && op <= IF_FALSE_GOTO) { // Conditional operators
        out += ("if " + arg1 + " ");
        switch(op) {
            case GOTO_EQ: out += "=="; break;
            case GOTO_NEQ: out += "!="; break;
            case GOTO_GT: out += ">"; break;
            case GOTO_GTE: out += ">="; break;
            case GOTO_LT: out += "<"; break;
            case GOTO_LTE: out += "<="; break;
            case IF_GOTO: out += "!= 0"; break;
            case IF_FALSE_GOTO: out += "== 0"; break;
        }
        out += (" " + arg2 + " goto " + result);
    }
    else if(op >= CtoI && op <= CtoF) {             // Type Conversion functions
        out += (result + " = ");
        switch(op) {
            case CtoI: out += "CharToInt"; break;
            case ItoC: out += "IntToChar"; break;
        }
        out += ("(" + arg1 + ")");
    }

    else if(op == ASSIGN)                       // Assignment operator
        out += (result + " = " + arg1);
    else if(op == GOTO)                         // Goto
        out += ("goto " + result);
    else if(op == RETURN)                       // Return from a function
        out += ("return " + result);
    else if(op == PARAM)                        // Parameters for a function
        out += ("param " + result);
    else if(op == CALL) {                       // Call a function
        if(arg2.size() > 0)
            out += (arg2 + " = ");
        out += ("call " + result + ", " + arg1);
    }
    else if(op == ARR_IDX_ARG)                  // Array indexing
        out += (result + " = " + arg1 + "[" + arg2 + "]");
    else if(op == ARR_IDX_RES)                  // Array indexing
        out += (result + "[" + arg2 + "] = " + arg1);
    else if(op == FUNC_BEG)                     // Function begin
        out += (result + ": ");
    else if(op == FUNC_END) {                   // Function end
        out += ("function " + result + " ends");
    }
    else if(op == L_DEREF)                      // Dereference
        out += ("*" + result + " = " + arg1);

    return out;
}


// Implementations of constructors and functions for the quadArray class
void quadArray::print() {
    for(int i = 0; i < 120; i++)
        cout << '-';
    cout << endl;
    cout << "THREE ADDRESS CODE (TAC):" << endl;
    for(int i = 0; i < 120; i++)
        cout << '-';
    cout << endl;

    // Print each of the quads one by one
    for(int i = 0; i < (int)quads.size(); i++) {
        if(quads[i].op != FUNC_BEG && quads[i].op != FUNC_END)
            cout << left << setw(4) << i << ":    ";
        else if(quads[i].op == FUNC_BEG)
            cout << endl << left << setw(4) << i << ": ";
        else if(quads[i].op == FUNC_END)
            cout << left << setw(4) << i << ": ";
        cout << quads[i].print() << endl;
    }
    cout << endl;
}


// Implementations of constructors and functions for the expression class
expression::expression(): fold(0), folder(NULL) {}


// Overloaded emit functions
void emit(string result, string arg1, string arg2, opcode op) {
    quad q(result, arg1, arg2, op);
    quadList.quads.push_back(q);
    nextinstr++;
}

void emit(string result, int constant, opcode op) {
    quad q(result, to_string(constant), "", op);
    quadList.quads.push_back(q);
    nextinstr++;
}

void emit(string result, char constant, opcode op) {
    quad q(result, to_string(constant), "", op);
    quadList.quads.push_back(q);
    nextinstr++;
}


// Implementation of the makelist function
list<int> makelist(int i) {
    list<int> l(1, i);
    return l;
}

// Implementation of the merge function
list<int> merge(list<int> list1, list<int> list2) {
    list1.merge(list2);
    return list1;
}

// Implementation of the backpatch function
void backpatch(list<int> l, int address) {
    string str = to_string(address);
    for(list<int>::iterator it = l.begin(); it != l.end(); it++) {
        quadList.quads[*it].result = str;
    }
}


// Implementation of the overloaded convertToType functions
void convertToType(expression* arg, expression* res, DataType toType) {
    if(res->type == toType)
        return;

    if(res->type == INT) {
        if(toType == CHAR)
            emit(arg->loc, res->loc, "", ItoC);
    }
    else if(res->type == CHAR) {
        if(toType == INT)
            emit(arg->loc, res->loc, "", CtoI);
    }
}

void convertToType(string t, DataType to, string f, DataType from) {
    if(to == from)
        return;
    
    if(from == INT) {
        if(to == CHAR)
            emit(t, f, "", ItoC);
    }
    else if(from == CHAR) {
        if(to == INT)
            emit(t, f, "", CtoI);
    }
}

// Implementation of the convertIntToBool function
void convertIntToBool(expression* expr) {
    if(expr->type != BOOL) {
        expr->type = BOOL;
        expr->falselist = makelist(nextinstr);    // Add falselist for boolean expressions
        emit("", expr->loc, "", IF_FALSE_GOTO);
        expr->truelist = makelist(nextinstr);     // Add truelist for boolean expressions
        emit("", "", "", GOTO);
    }
}

// Implementation of the sizeOfType function
int sizeOfType(DataType t) {
    if(t == VOID)
        return __VOID_SIZE;
    else if(t == CHAR)
        return __CHARACTER_SIZE;
    else if(t == INT)
        return __INTEGER_SIZE;
    else if(t == POINTER)
        return __POINTER_SIZE;
    else if(t == FUNCTION)
        return __FUNCTION_SIZE;
    else
        return 0;
}

// Implementation of the checkType function
string checkType(symbolType t) {
    if(t.type == VOID)
        return "void";
    else if(t.type == CHAR)
        return "char";
    else if(t.type == INT)
        return "int";
    else if(t.type == FUNCTION)
        return "function";

    else if(t.type == POINTER) {        // Depending on type of pointer
        string tp = "";
        if(t.nextType == CHAR)
            tp += "char*";
        else if(t.nextType == INT)
            tp += "int*";
        tp += string(t.pointers, '*');
        return tp;
    }

    else if(t.type == ARRAY) {          // Depending on type of array
        string tp = "";
        if(t.nextType == CHAR)
            tp += "char";
        else if(t.nextType == INT)
            tp += "int";
        vector<int> dim = t.dims;
        for(int i = 0; i < (int)dim.size(); i++) {
            if(dim[i])
                tp += "[" + to_string(dim[i]) + "]";
            else
                tp += "[]";
        }
        if((int)dim.size() == 0)
            tp += "[]";
        return tp;
    }

    else
        return "unknown";
}

// Implementation of the getInitVal function
string getInitVal(symbol* sym) {
    if(sym->initVal != NULL) {
        if(sym->type.type == INT)
            return to_string(sym->initVal->i);
        else if(sym->type.type == CHAR)
            return to_string(sym->initVal->c);
        else
            return "-";
    }
    else
        return "-";
}
