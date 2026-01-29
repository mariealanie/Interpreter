#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <stack>
#include <queue>


using namespace std;

enum type_of_lex {
    LEX_NULL, LEX_AND, LEX_BOOL, LEX_ELSE, LEX_GOTO, LEX_IF, LEX_FALSE,
//  "",       and,     boolean,  else,     goto,     if,     false,
    
    LEX_INT, LEX_NOT, LEX_OR, LEX_PROGRAM, LEX_READ, LEX_STRING, LEX_TRUE, 
//  int,     not,     or,     program,     read,     string,     true,

    LEX_WHILE, LEX_WRITE, 
//  while,     write     

    LEX_SEMICOLON, LEX_COMMA, LEX_COLON, LEX_LPAR, LEX_RPAR, LEX_LBRACKET, LEX_RBRACKET, LEX_ASSIGN, LEX_EQUAL, 
//  ;              ,          :          (            )      {             }             =           == 
    LEX_PLUS, LEX_MINUS, LEX_MULT, LEX_DIV, LEX_MOD, LEX_LESS, LEX_GREATER, LEX_LEQ, LEX_GEQ, LEX_NEQ, 
//  +         -          *         /        %        <         >            <=       >=       !=        
     
    LEX_NUM,
    LEX_ID, 
    LEX_WORD,
    LEX_FIN,

    LEX_BIN, //мусорная штука

    POLIZ_LABEL, 
    POLIZ_ADDRESS, 
    POLIZ_GO, 
    POLIZ_FGO};
    


class Lex { // делаем пары - лексема<->тип лексемы
    friend class Scanner;
    type_of_lex t_lex;
    int v_lex;
    string content;

    public:
    Lex ( type_of_lex t = LEX_NULL, int v = 0, string s = "") {
        t_lex = t; v_lex = v; content = s;
    }
    type_of_lex get_type()const { return t_lex; }
    int get_value()const { return v_lex; }
    string get_content()const { return content; }
    
    friend ostream& operator << (ostream &s, Lex l);
};

class Ident { // описание переменных и констант
    string name;
    bool declare;
    type_of_lex type;
    bool assign;
    int value;
    string content; // если переменная типа string
    bool indicator; // если переменная типа bool
    public:
    Ident() { 
        declare = false; assign = false; 
    }
    Ident(string n) {
        name=n; declare = false; assign = false; 
    }
    
    bool operator== (const string& s) const {
        return name == s; 
    }
    string get_name() { return name; }
    bool get_declare() { return declare; }
    void set_declare() { declare = true; }
    type_of_lex get_type() { return type; }
    void set_type(type_of_lex t) { type = t; }
    bool get_assign() { return assign; }
    void set_assign(){ assign = true; }
    int get_value() { return value; }
    void set_value(int v){ value = v; }

    string get_content() { return content; }
    void set_content(string s){ content = s; }
    bool get_ind() { return indicator; }
    void set_ind(bool b){ indicator = b; }
};

vector <Ident> TID; //таблица переменных и констант
int put (const string & buf) { // либо определяем, что переменная уже была
                               // либо помещаем в таблицу новую
    vector <Ident>::iterator k;
    if ( (k = find(TID.begin(), TID.end(), buf)) != TID.end()) {
        int index = distance(TID.begin(), k);
        return index;
    }
    TID.push_back ( Ident(buf) );
    return TID.size() - 1;
}

class Scanner { //сканер файла
    friend class Lex;
    char c;
    int look (const string& buf, const char ** list){
        int i = 0;
        while (list [i]) {
            if ( buf == list [i] ) 
            return i;
            i++;
        }
        return 0;
    }
    void gc() { c = fgetc(fp); 
        }
    public:
		static int str_counter;
        static FILE * fp;
        static const char * TW[],* TD[];
        Scanner (const char * program){
            fp = fopen( program, "r" );
            if (fp==NULL) throw "can't open file";
        }
        Lex get_lex();
    };
    FILE* Scanner::fp = NULL;
    
    const char* Scanner:: TW [] = { //таблица служебных слов
    
    "", "and","boolean","else", "goto", "if", "false",
//  0   1     2         3       4       5     6
    "int","not","or","program","read","string","true",
//  7     8     9    10        11      12      13
    "while","write", NULL
//  14      15
    };
    const char* Scanner:: TD [] = { //таблица разделителей
    ";", ",", ":", "(", ")", "{", "}", "=", "==", 
//  0     1    2    3    4    5    6    7    8    9
    "+", "-", "*", "/", "%", "<", ">", "<=", ">=", "!=", NULL
//  10   11   12   13   14   15   16   17    18    19
    };

int Scanner::str_counter = 1;

ostream& operator << (ostream &s, Lex l)
    {       
		vector<string> types{"LEX_NULL", "LEX_AND", "LEX_BOOL", "LEX_ELSE", "LEX_GOTO", "LEX_IF", "LEX_FALSE",
//  "",       and,     boolean,  else,     goto,     if,     false,
    
    "LEX_INT", "LEX_NOT", "LEX_OR", "LEX_PROGRAM", "LEX_READ", "LEX_STRING", "LEX_TRUE", 
//  int,     not,     or,     program,     read,     string,     true,

    "LEX_WHILE", "LEX_WRITE", 
//  while,     write     

    "LEX_SEMICOLON", "LEX_COMMA", "LEX_COLON", "LEX_LPAR", "LEX_RPAR", "LEX_LBRACKET", "LEX_RBRACKET", "LEX_ASSIGN", "LEX_EQUAL", 
//  ;              ,          :          (            )      {             }             =           == 
    "LEX_PLUS", "LEX_MINUS", "LEX_MULT", "LEX_DIV", "LEX_MOD", "LEX_LESS", "LEX_GREATER", "LEX_LEQ", "LEX_GEQ", "LEX_NEQ", 
//  +         -          *         /        %        <         >            <=       >=       !=        
     
    "LEX_NUM",
    "LEX_ID", 
    "LEX_WORD",
    "LEX_FIN",

    "LEX_BIN", //мусорная штука

    "POLIZ_LABEL", 
    "POLIZ_ADDRESS", 
    "POLIZ_GO", 
    "POLIZ_FGO"}; 
        s << "( " << types[l.t_lex] << " , " << l.v_lex << " );";
        return s;
    }



Lex Scanner:: get_lex (){
    enum state{H,IDENT, NUMB, COM, ALE, STR, NEQ };
    state CS = H; string buf; int d, j;
    
    do { 
        gc();
        switch(CS) {
        case H:
            if(c ==' ' || c =='\n' || c=='\r' || c =='\t'){
				if ( c == '\n') str_counter++;
			}
            else
            if(isalpha(c)) {buf.push_back(c); CS = IDENT;}
            else
            if ( isdigit(c) ) { d = c - '0'; CS = NUMB; }
            else
            if ( c== '/' ) {
                buf.push_back(c);
                gc();
                if ( c == '*') {buf.clear(); CS = COM;} 
                else {
                    ungetc(c, fp);
                    j = look (buf, TD);
                    buf.clear();
                    return Lex((type_of_lex) (j+(int) LEX_SEMICOLON),j); // если нет
				}
            }
            else
            if (c== '=' || c== '<' || c== '>') {
                buf.push_back(c); CS = ALE; 
            }
            else
            if (c=='"'){ CS = STR; }
            else
            if (c == '!') {
                buf.push_back(c); CS = NEQ; 
            }
            else 
            if (c == ';' || c == ',' || c == ':' || c == '(' || c == ')' ||
                c == '{' || c == '}' || c == '+' || c == '-' || c == '*' || c == '%'){ 
                buf.push_back(c);
                if ( (j = look ( buf, TD)) )
                    buf.clear();
                    return Lex((type_of_lex) (j+(int) LEX_SEMICOLON),j);
            }
            else
            if (feof(fp)){
                return Lex(LEX_FIN);
            }
            else {
                    throw c;       
            }
            break;
        
        case IDENT:
            if ( isalpha(c) || isdigit(c)) {buf.push_back(c);} 
            else{ 
                ungetc(c, fp);
                CS = H;
                if ( j = look (buf, TW) ) {//проверка на служебное слово
                    buf.clear();
                    return Lex ((type_of_lex) j, j);
                }
                else {
                    j = put (buf); // не нашли -> название переменной
                    buf.clear();
                    return Lex (LEX_ID, j);
                }
            }
            break;
        
        case NUMB:
            if ( isdigit(c) ) {d = d * 10 + (c - '0');}
			else if (isalpha(c) ){
				throw "!Ошибка при лексическом анализе! Некорректный идентификатор";
			}
            else { 
                ungetc(c,fp); 
                CS = H;
                return Lex (LEX_NUM, d);
            }
            break;

        case COM:
            if (c == '\n'){
                str_counter++;
            }
            if ( c == '*' ) {
                gc();
                
                if (c == '/'){
                    CS = H;
                }
                else{
                    ungetc(c, fp);
                }
            }
            else
            if (feof(fp)) throw "!Ошибка при лексическом анализе! Незакрытый комментарий"; 
            break;

        case ALE:
            if (c=='='){ 
                buf.push_back(c); j = look( buf, TD);
                buf.clear(); CS=H;
                return Lex ((type_of_lex)(j+(int) LEX_SEMICOLON),j);
            }
            else {
                ungetc(c, fp); j = look (buf, TD); 
                buf.clear(); CS = H;
                return Lex((type_of_lex) (j+(int) LEX_SEMICOLON),j); 
            }
            break;

        case NEQ: 
            if (c == '=') {
                buf.push_back(c); j = look ( buf, TD );
                buf.clear(); CS = H;
                return Lex ( LEX_NEQ, j ); 
            }
            else throw "!Ошибка при лексическом анализе! Отдельный восклицательный знак";
        case STR:
            if (c != '"'){
                buf.push_back(c);
                if (feof(fp)){throw "!Ошибка при лексическом анализе! Незакрытая строка";}
            }
            else {
                CS=H; 
                int size = buf.size(); 
                string content = buf;
                buf.clear(); 
                return Lex(LEX_WORD, size, content);
            }

            break;
        } //end of switch
    } while (true);
} // end of getlex()


class Parser {
    Lex curr_lex;
    type_of_lex c_type;
    int c_val;
    string c_content;
    Scanner scan;
    stack <type_of_lex> st_lex;
    vector <string> marks_vector;

    // Prog → program LEX_LBRACKET Def Opers LEX_RBRACKET
    void Prog(); 

    // Def → { [ int | boolean | string ] Id {, Id }; }
    void Def(); 

    // Id → LEX_ID | LEX_ID = [+ | - | eps] LEX_NUM | LEX_WORD | true | false
    void Id(type_of_lex type);

    //Opers  → { Oper }
    void Opers();

    // Oper → if (Equ) Oper [else Oper | eps] | while (Equ) Oper | read (LEX_ID); | write(Equ {, Equ}); | LEX_LBRACKET Opers LEX_RBRACKET | LEX_ID : Oper | goto LEX_ID; | Equ;  
    void Oper();

    Lex bin_lex;
    // Equ → все выражения ( a == b, a <= b + 1) - запускаем стек-машину
    Lex Equ(Lex temp_lex, type_of_lex stop_lex1, type_of_lex stop_lex2); 

    type_of_lex Equ_Type (Lex curr_lex);

    void gl(){
        curr_lex = scan.get_lex();
        c_type = curr_lex.get_type();
        c_val = curr_lex.get_value();
        c_content = curr_lex.get_content();

    }
    public:
        vector <Lex> total_poliz;
        Parser (const char *program):scan(program){}
        vector<Lex> analyze();
};
   
vector<Lex> Parser::analyze () {
    gl();
    Prog();
    if (c_type != LEX_FIN)
        throw curr_lex;
    int counter = 0;
    Lex lex;
    for (int i = 0; i < total_poliz.size(); i++){
        lex = total_poliz[i];
        if (lex.get_type() == POLIZ_LABEL && lex.get_content() != ""){
            if (find(marks_vector.begin(), marks_vector.end(), lex.get_content()) == marks_vector.end())
                throw "!Ошибка при семантическом анализе!  Необъявленная метка";
                total_poliz[i] = Lex(POLIZ_LABEL, TID[lex.get_value()].get_value());
        }
    }

    
    cout << endl << "--- Общий ПОЛИЗ выражений программы---" << endl;
    for (Lex l : total_poliz){
        
		cout << counter << " " << l << endl;
        counter++;
    }

    cout << endl << "OK" << endl;
    
    return total_poliz;
}

void Parser::Prog () {
    if (c_type == LEX_PROGRAM) gl();
        else throw curr_lex;
    if (c_type == LEX_LBRACKET) gl();
        else throw curr_lex;

    Def();
    Opers();
    if (c_type == LEX_RBRACKET) gl();
        else throw curr_lex;
}


void Parser::Def () { 
    while (c_type == LEX_INT || c_type == LEX_BOOL || c_type == LEX_STRING){
        type_of_lex type = c_type;
        gl();
        Id(type);
        while(c_type == LEX_COMMA){
            gl();
            Id(type);
        }
        if (c_type == LEX_SEMICOLON) gl();
            else throw curr_lex;
    }
}
void Parser::Id(type_of_lex type){
    if (c_type == LEX_ID){
        int id = c_val;
        if (TID[id].get_declare()) throw "!Ошибка при семантическом анализе! Переопределение переменной";
        else{
            TID[id].set_declare();
            TID[id].set_type(type); 
        }
        gl();
        if (c_type == LEX_ASSIGN){
            gl();
            TID[id].set_assign();
            
            if (type == LEX_INT){
                
                int val = c_val;
                int mult = 1;
                if (c_type == LEX_PLUS) {gl(); val = c_val;}
                else if (c_type == LEX_MINUS) {mult = -1; gl(); val = c_val;}

                if (c_type == LEX_NUM){
                    TID[id].set_value(mult*val);
                    gl();
                }
                else throw curr_lex;

            }
            else if (type == LEX_BOOL){
                
                if (c_type == LEX_TRUE ){
                    
                    TID[id].set_value(1);
                    TID[id].set_ind(true);
                    gl();
                }
                else if (c_type == LEX_FALSE ){
                    
                    TID[id].set_value(0);
                    TID[id].set_ind(false);
                    gl();
                }
                else throw curr_lex;
            }
            else if (type == LEX_STRING && c_type == LEX_WORD){
                
                TID[id].set_value(c_val);
                TID[id].set_content(c_content);
                gl();
            } 
            else throw "!Ошибка при семантическом анализе! Несовместимые типы при описании";
        }

    }
    else throw curr_lex;
}

void Parser::Opers(){
    while (c_type != LEX_RBRACKET){
        Oper();
    }
}

void Parser::Oper(){
    int pl0, pl1, pl2, pl3;
    if (c_type == LEX_FIN) throw "!Ошибка при синтаксическом анализе! Незакрытый блок программы";
    else {
        if (c_type == LEX_IF){
            gl();
            if (c_type == LEX_LPAR){
                gl();
                Equ(bin_lex, LEX_RPAR, LEX_NULL);//проверка на то что это условие включена в Equ
                pl2 = total_poliz.size();
                total_poliz.push_back( Lex() );
                total_poliz.push_back( Lex(POLIZ_FGO));
                if (c_type == LEX_RPAR){
                    gl();
                    Oper();
                    pl3 = total_poliz.size();
                    total_poliz.push_back(Lex());
                    total_poliz.push_back(Lex(POLIZ_GO));
                    total_poliz[pl2] = Lex(POLIZ_LABEL, total_poliz.size());
                    if (c_type == LEX_ELSE){
                        gl();
                        Oper();
                    }
                    total_poliz[pl3] = Lex(POLIZ_LABEL, total_poliz.size());
                    // если else пусто, метка будет указывать на элемент сразу после POLIZ_GO
                }
                else throw "!Ошибка при синтаксическом анализе! Незакрытая скобка - IF";
            }
            else throw curr_lex;
        }

        else if (c_type == LEX_WHILE){
            gl();
            pl0 = total_poliz.size();
            if (c_type == LEX_LPAR){
                gl();
                Equ(bin_lex, LEX_RPAR, LEX_NULL);

                pl1 = total_poliz.size();
                total_poliz.push_back(Lex());
                total_poliz.push_back(Lex(POLIZ_FGO));

                if (c_type == LEX_RPAR){
                    gl();
                    Oper();
                    total_poliz.push_back(Lex(POLIZ_LABEL, pl0));
                    total_poliz.push_back(Lex(POLIZ_GO));
                    total_poliz[pl1] = Lex(POLIZ_LABEL, total_poliz.size());
                }
                else throw "!Ошибка при синтаксическом анализе! Незакрытая скобка - WHILE"; 
            }
            else throw curr_lex;
        }

        else if (c_type == LEX_READ){
            gl();
            if (c_type == LEX_LPAR){
                gl();
                if (c_type == LEX_ID){
                    if (!TID[c_val].get_declare()) throw "!Ошибка при семантическом анализе!  Использование необъявленной переменной - READ";
                    TID[c_val].set_assign();
                    total_poliz.push_back(curr_lex);
                    gl();
                    if (c_type == LEX_RPAR){
                        gl();
                        if (c_type == LEX_SEMICOLON){
                            gl();
                            total_poliz.push_back(Lex(LEX_READ));
                        }
                        else throw curr_lex;
                    }
                    else throw "!Ошибка при синтаксическом анализе! Незакрытая скобка - READ"; 
                }
                else throw curr_lex;
                
                
            }
            else throw curr_lex;
        }

        else if (c_type == LEX_WRITE){
            int counter = 1; //счетчик сколько значений достанем из стека
            gl();
            if (c_type == LEX_LPAR){
                gl();
                Equ(bin_lex, LEX_RPAR, LEX_COMMA);

                while (c_type == LEX_COMMA){
                    gl();
                    Equ(bin_lex, LEX_RPAR, LEX_COMMA);
                    counter++;
                }
                if (c_type == LEX_RPAR){
                    gl();
                    if (c_type == LEX_SEMICOLON){
                        gl();
                        total_poliz.push_back(Lex(LEX_WRITE, counter));
                    }
                    else throw curr_lex;
                }
                else throw "!Ошибка при синтаксическом анализе! Незакрытая скобка - WRITE"; 
            }
            else throw curr_lex;
        }

        else if (c_type == LEX_LBRACKET){
            gl();
            Opers();
            gl();
        }

        else if (c_type == LEX_ID){
            Lex temp_lex = curr_lex;
            int id = c_val;
            gl();
            if (c_type == LEX_COLON){
                if (TID[id].get_declare()) throw "!Ошибка при семантическом анализе!  Объявленная переменная не может быть меткой";
                TID[id].set_value(total_poliz.size());
                if (find(marks_vector.begin(), marks_vector.end(), TID[id].get_name()) != marks_vector.end())
                    throw "!Ошибка при семантическом анализе!  Переопределение метки";
                marks_vector.push_back(TID[id].get_name());
                gl();
                Oper();
            }
            else {
				if (!TID[id].get_declare()) throw "!Ошибка при семантическом анализе!  Использование необъявленной переменной";
                Equ(temp_lex, LEX_SEMICOLON, LEX_NULL);
                if (c_type == LEX_SEMICOLON){
                    gl();
                }
                else throw curr_lex;
            }
        }

        else if (c_type == LEX_GOTO){
            gl();
            if (c_type == LEX_ID){
                if (TID[curr_lex.get_value()].get_declare()) throw "!Ошибка при семантическом анализе!  Объявленная переменная не может быть меткой";
                total_poliz.push_back(Lex(POLIZ_LABEL, curr_lex.get_value(), TID[c_val].get_name()));
                total_poliz.push_back(Lex(POLIZ_GO));    
                gl();
                if (c_type == LEX_SEMICOLON){
                    gl();
                }
                else throw curr_lex;
            }
            else throw curr_lex;
        }
        else {
            Equ(bin_lex, LEX_SEMICOLON, LEX_NULL);
            if (c_type == LEX_SEMICOLON){
                gl();
            }
            else throw curr_lex;
        }
    }
}

int op_priority(type_of_lex type){
    if (type == LEX_NOT){
        return 7;
    }
    else if (type == LEX_MULT || type == LEX_DIV || type == LEX_MOD){
        return 6;
    }
    else if (type == LEX_PLUS || type == LEX_MINUS){
        return 5;
    }
    else if (type == LEX_EQUAL || type == LEX_NEQ || 
             type == LEX_GREATER || type == LEX_LESS|| 
             type == LEX_GEQ || type == LEX_LEQ){
        return 4;
    }
    else if (type == LEX_AND || type == LEX_OR){
        return 3;
    }
    else if (type == LEX_ASSIGN){
        return 2;
    }
    else if (type == LEX_RPAR){
        return 1;
    }
    else if (type == LEX_LPAR){
        return 0;
    }
    else throw "!Ошибка при синтаксическом анализе!  Некорректная лексема в выражении" ;
}

/*
        LEX_NOT, 
    //7 not     

        LEX_MULT, LEX_DIV, LEX_MOD,
    //6 *         /        %
    
        LEX_PLUS, LEX_MINUS, 
    //5 +         -  

        LEX_EQUAL, LEX_LESS, LEX_GREATER, LEX_LEQ, LEX_GEQ, LEX_NEQ, 
    //4 ==         <         >            <=       >=       !=  
                
        LEX_AND, LEX_OR,  
    //3 and,     or,  

        LEX_ASSIGN,
    //2 =   
        
        LEX_RPAR,
    //1  )     

        LEX_LPAR,  
    //0 (

*/

type_of_lex Parser::Equ_Type (Lex lex){
    if (lex.get_type() == LEX_TRUE || lex.get_type() == LEX_FALSE) {
        return LEX_BOOL;
    }
    else if (lex.get_type() == LEX_NUM){
        return LEX_INT;
    }
    else if (lex.get_type() == LEX_WORD){
        return LEX_STRING;
    }
    else if (lex.get_type() == LEX_ID){
        return TID[lex.get_value()].get_type();
    }
    return LEX_NULL;
}

Lex Parser::Equ(Lex temp_lex, type_of_lex stop_lex1, type_of_lex stop_lex2){

    if (c_type == stop_lex1 || c_type == stop_lex2) throw "!Ошибка при синтаксическом анализе!  Пустое условие/выражение";
    stack <Lex> poliz_ops;
    queue <Lex> poliz_string;

    if (temp_lex.get_type() != LEX_NULL) {
        total_poliz.push_back(temp_lex);
        poliz_string.push(temp_lex);
    }

    int close_counter = 0; //число открытых скобок 
                           //если 0 значит блок условия закрыт
                           //для выражений вне условий - бессмысленно
                           //т.к. надо ждать ;
    if (stop_lex1 == LEX_RPAR) close_counter++;
    
    bool stop = false, empty_pars = false;
    int priority, last_priority = -1;

    while (!stop){
        if (Equ_Type(curr_lex) != LEX_NULL){
                empty_pars = false;
                if (c_type == LEX_ID && (!TID[c_val].get_declare())) throw "!Ошибка при семантическом анализе! Использование необъявленной переменной в выражении";
                total_poliz.push_back(curr_lex);
                poliz_string.push(curr_lex);
                gl();
            }

        else if ( c_type == stop_lex2 || (c_type == stop_lex1 && stop_lex1 != LEX_RPAR)){
            if (c_type == stop_lex2) close_counter--;
            stop=true;
            
        }

        else { 
            priority = op_priority(c_type);

            if (priority == 0){ //открывающая скобка
                empty_pars = true;
                poliz_ops.push(curr_lex);
                close_counter++;
                gl();
            }

            else if (priority == 1){ //закрывающая скобка
                close_counter--;
                if (close_counter < 0) throw "!Ошибка при синтаксическом анализе!  Лишняя закрывающая скобка";
                else if (close_counter == 0 && stop_lex1 == LEX_RPAR){
                    stop=true;
                }
                else {
                    Lex temp_lex = poliz_ops.top();
                    if (op_priority(temp_lex.get_type()) == 0 && empty_pars == true) 
                        throw "!Ошибка при синтаксическом анализе!  Пустые скобки в выражении";
                    while (op_priority(temp_lex.get_type()) != 0){
                        if (poliz_ops.empty()) throw "!Ошибка при синтаксическом анализе!  Незакрытая скобка в выражении";
                        
                        total_poliz.push_back(temp_lex);
                        poliz_string.push(temp_lex);

                        poliz_ops.pop();
                        temp_lex = poliz_ops.top();
                    }
                    poliz_ops.pop(); // удаляем открывающую скобку
                    if (poliz_ops.empty()) last_priority = -1;
                    else last_priority = op_priority(poliz_ops.top().get_type());
                    gl();
                }
            }
			else if (priority == 2 && last_priority > 2){
				 throw "!Ошибка при семантическом анализе!   Попытка присвоить значение в не переменную";
                    
			}
            else if (priority > last_priority 
                        || (priority == 2 && last_priority == 2) // для присваивания
                        || poliz_ops.empty())
                {
                    empty_pars = false;
                    poliz_ops.push(curr_lex);
                    last_priority = priority;
                    gl();
                }

            else if(priority <= last_priority){
                empty_pars = false;
                Lex temp_lex = poliz_ops.top();
                while (op_priority(temp_lex.get_type()) >= priority && (!poliz_ops.empty())){
                    
                    total_poliz.push_back(temp_lex);
                    poliz_string.push(temp_lex);

                    poliz_ops.pop();
                    if (!poliz_ops.empty()) temp_lex = poliz_ops.top();
                }

                poliz_ops.push(curr_lex);
                last_priority = priority;
                gl();

            }

        }    
    }
    if (close_counter != 0) throw "!Ошибка при синтаксическом анализе!  Несоответсвие скобок";

    while (!poliz_ops.empty()){
        total_poliz.push_back(poliz_ops.top());
        poliz_string.push(poliz_ops.top());
        poliz_ops.pop();
    }
    

    stack <Lex> poliz_calculator;
        
    while (!poliz_string.empty()){               
    
        Lex temp_lex = poliz_string.front();
        poliz_string.pop();

        if (Equ_Type(temp_lex) != LEX_NULL) poliz_calculator.push(temp_lex);

        else if (temp_lex.get_type() == LEX_NOT){

            if (poliz_calculator.empty()) throw "!Ошибка при семантическом анализе! NOT без аргумента";
            temp_lex = poliz_calculator.top();

            if (Equ_Type(temp_lex) == LEX_BOOL){
                if (temp_lex.get_type() == LEX_ID){
                    if (TID[temp_lex.get_value()].get_assign());
                    else throw "!Ошибка при семантическом анализе! Переменная не проинициализирована - NOT";
                }
            }
            else throw "!Ошибка при семантическом анализе!  Некорректный аргумент для NOT";
        }

        else if (poliz_calculator.size() < 2) throw "!Ошибка при семантическом анализе!  Недостаточно аргументов для команды";
        else{ 
            Lex lex1 = poliz_calculator.top();
            poliz_calculator.pop();
            Lex lex2 = poliz_calculator.top();

            switch (op_priority(temp_lex.get_type()))
            {
            case 6: // * / %
                if (Equ_Type(lex1) == LEX_INT && Equ_Type(lex2) == LEX_INT){
                    if (lex1.get_type() == LEX_ID){
                        if (TID[lex1.get_value()].get_assign());
                        else throw "!Ошибка при семантическом анализе! Переменная не проинициализирована - *, /, %";
                    }
                    if (lex2.get_type() == LEX_ID){
                        if (TID[lex2.get_value()].get_assign());
                        else throw "!Ошибка при семантическом анализе! Переменная не проинициализирована - *, /, %";
                    }
                }

                else throw "!Ошибка при семантическом анализе!  Некорректные аргументы для *, /, %";
                break;
            
            case 5: // + - 
                if (Equ_Type(lex1) == Equ_Type(lex2) && Equ_Type(lex1) != LEX_BOOL) {
                    if (temp_lex.get_type() == LEX_MINUS && Equ_Type(lex1) == LEX_STRING)
                        throw "!Ошибка при семантическом анализе!  Строки нельзя вычитать";
                    
                    if (lex1.get_type() == LEX_ID){
                        if (TID[lex1.get_value()].get_assign());
                        else throw "!Ошибка при семантическом анализе! Переменная не проинициализирована - +, -";
                    }
                    if (lex2.get_type() == LEX_ID){
                        if (TID[lex2.get_value()].get_assign());
                        else throw "!Ошибка при семантическом анализе! Переменная не проинициализирована - +, -";
                    }
                    
                }
                else throw "!Ошибка при семантическом анализе!  Некорректные аргументы для +, -";
                break;

            case 4: // == < > <= >= !=   
                if (Equ_Type(lex1) == Equ_Type(lex2)) {
                    if (Equ_Type(lex1) == LEX_STRING && (temp_lex.get_type() == LEX_LEQ || temp_lex.get_type() == LEX_GEQ) )
                        throw "!Ошибка при семантическом анализе!  Для строк не определены <= и >=";
                    
                    if (lex1.get_type() == LEX_ID){
                        if (TID[lex1.get_value()].get_assign());
                        else throw "!Ошибка при семантическом анализе! Переменная не проинициализирована - ==, <, >, <=, >=, !=";
                    }
                    if (lex2.get_type() == LEX_ID){
                        if (TID[lex2.get_value()].get_assign());
                        else throw "!Ошибка при семантическом анализе! Переменная не проинициализирована - ==, <, >, <=, >=, !=";
                    }
                    poliz_calculator.pop();
                    poliz_calculator.push(Lex(LEX_TRUE, 13));
                }
                else throw "!Ошибка при семантическом анализе!  Некорректные аргументы для ==, <, >, <=, >=, !=";
                break;

            case 3: // and or
                if (Equ_Type(lex1) == Equ_Type(lex2) && Equ_Type(lex1) == LEX_BOOL){
                    if (lex1.get_type() == LEX_ID){
                        if (TID[lex1.get_value()].get_assign());
                        else throw "!Ошибка при семантическом анализе! Переменная не проинициализирована - and, or";
                    }
                    if (lex2.get_type() == LEX_ID){
                        if (TID[lex2.get_value()].get_assign());
                        else throw "!Ошибка при семантическом анализе! Переменная не проинициализирована - and, or";
                    }
                }
                else throw "!Ошибка при семантическом анализе!  Некорректные аргументы для and, or";
                break;

            case 2: // =
                if (Equ_Type(lex1) == Equ_Type(lex2)){
                    if (lex1.get_type() == LEX_ID){
                        if (TID[lex1.get_value()].get_assign());
                        else throw "!Ошибка при семантическом анализе! Переменная не проинициализирована - =";
                    }
                    if (lex2.get_type() == LEX_ID){
                        TID[lex2.get_value()].set_assign();
                    }
                    else throw "!Ошибка при семантическом анализе! Попытка записи не в переменную";
                    
                }
                else throw "!Ошибка при семантическом анализе!  Некорректные аргументы для =";
                break;
            

            default:
            throw "!Ошибка при семантическом анализе!  Некорректное выражение";

            }
        }
    }
     
    if (poliz_calculator.size() == 0){
        throw "!Ошибка при семантическом анализе!  После анализа выражения в стеке ПОЛИЗа не осталось ни одного значения";
    }
    else if (poliz_calculator.size() > 1){
        throw "!Ошибка при семантическом анализе!  После анализа выражения в стеке ПОЛИЗа осталось больше одного значения";
    }
    else {
        if (stop_lex1 == LEX_RPAR && stop_lex2 == LEX_NULL){
            if (Equ_Type(poliz_calculator.top()) != LEX_BOOL){
                throw "!Ошибка при семантическом анализе!  Некорректное выражение в условии";
            }
        }
        if (poliz_calculator.top().get_type() == LEX_ID){
            if (TID[poliz_calculator.top().get_value()].get_assign());
            else throw "!Ошибка при семантическом анализе! Переменная не проинициализирована в выражении";
        }
        Lex result = poliz_calculator.top();
        poliz_calculator.pop();
        return result;
    }
    
}


class Executer
{
public:
    
    stack <Lex> args;
    bool get_bool_data(Lex lex){
        if (lex.get_type() == LEX_ID) 
            return TID[lex.get_value()].get_ind();
        else if (lex.get_type() == LEX_TRUE)
            return true;
        return false;
    }
    int get_int_data(Lex lex){
        if (lex.get_type() == LEX_ID) 
            return TID[lex.get_value()].get_value();
        return lex.get_value();
    }
    string get_string_data(Lex lex){
        if (lex.get_type() == LEX_ID) 
            return TID[lex.get_value()].get_content();
        return lex.get_content();
    }
    void from_st(Lex &lex){
        lex = args.top();
        args.pop();
    }

    void push_st_bool(bool result){
        if (result)
            args.push(Lex(LEX_TRUE));
        else
            args.push(Lex(LEX_FALSE));
    }
    void push_st_int(int result){
        args.push(Lex(LEX_NUM, result));
    }
    void push_st_string(string result){
        args.push(Lex(LEX_WORD, 0, result));
    }
    type_of_lex arg_type(Lex lex){
        if (lex.get_type() == LEX_ID){
            return TID[lex.get_value()].get_type();
        }
        else if (lex.get_type() == LEX_TRUE || lex.get_type() == LEX_FALSE){
            return LEX_BOOL;
        }
        else if (lex.get_type() == LEX_NUM){
            return LEX_INT;
        }
        else return LEX_STRING;
    }
    

    void execute(vector <Lex> &poliz){
        Lex curr_elem;
        int index=0, size = poliz.size();
        Lex lex1, lex2;
        bool result;

        while (index < size)
        {
            curr_elem = poliz[index];
            index++;
            //cout << curr_elem << endl;
            try
            {           
            switch (curr_elem.get_type())
            {
                case LEX_FALSE:
                case LEX_TRUE:
                case LEX_NUM:
                case LEX_ID: 
                case LEX_WORD:
                case POLIZ_LABEL:

                    args.push(curr_elem);    
                    break;
                
                case LEX_AND:

                    from_st(lex1);
                    from_st(lex2);
                    result = get_bool_data(lex1) && get_bool_data(lex2);
                    push_st_bool(result);
                    break;
                
                case LEX_NOT:

                    from_st(lex1);
                    result = ! get_bool_data(lex1);
                    push_st_bool(result);
                    break;

                case LEX_OR:

                    from_st(lex1);
                    from_st(lex2);
                    result = get_bool_data(lex1) || get_bool_data(lex2);
                    push_st_bool(result);
                    break;
                
                case LEX_READ:

                    from_st(lex1);
                    if (TID[lex1.get_value()].get_type() == LEX_INT){
                        int in_vol;
                        cin >>in_vol;
                        TID[lex1.get_value()].set_value(in_vol);
                    }    
                    else if (TID[lex1.get_value()].get_type() == LEX_STRING){
                        string in_str;
                        cin >>in_str;
                        TID[lex1.get_value()].set_content(in_str);
                    }
                    break;

                case LEX_WRITE:{

                    int count = curr_elem.get_value();
                    int count1 = count;
                    stack <Lex> new_args;

                    while (count>0)
                    {
                        from_st(lex1);
                        new_args.push(lex1);
                        count--;
                    }
                    while (count1>0)
                    {
                        lex1 = new_args.top();
                        new_args.pop();
                        count1--;

                        if (lex1.get_type() == LEX_ID){
                            switch (TID[lex1.get_value()].get_type())
                            {
                            case LEX_INT:
                                cout << TID[lex1.get_value()].get_value();
                                break;

                            case LEX_BOOL:
                                if (TID[lex1.get_value()].get_ind())
                                    cout << "true";
                                else 
                                    cout << "false";
                                break;
                                
                            case LEX_STRING:
                                cout << TID[lex1.get_value()].get_content();
                                break;
                            }
                        }
                        else if (lex1.get_type() == LEX_TRUE){
                            cout << "true"; 
                        }
                        else if (lex1.get_type() == LEX_FALSE){
                            cout << "false"; 
                        }
                        else if (lex1.get_type() == LEX_NUM){
                            cout << lex1.get_value(); 
                        }
                        else if (lex1.get_type() == LEX_WORD){
                            cout << lex1.get_content(); 
                        }
                    }
                    cout << endl;
                    break;
                }

                case LEX_ASSIGN:

                    from_st(lex1); // изначально на вершине стека - ОТКУДА пишем
                    from_st(lex2); // глубже - КУДА пишем
                    
                    cout << lex1 << endl;
                    cout << lex2 << endl;
                    
                    TID[lex2.get_value()].set_value(get_int_data(lex1));
                    TID[lex2.get_value()].set_ind(get_bool_data(lex1));
                    TID[lex2.get_value()].set_content(get_string_data(lex1));
                    args.push(lex2);
                    break;
                
                case LEX_EQUAL:

                    from_st(lex2);
                    from_st(lex1);

                    if (arg_type(lex1) == LEX_INT){
                        push_st_bool(get_int_data(lex1) == get_int_data(lex2));
                    }
                    else if (arg_type(lex1) == LEX_BOOL){
                        push_st_bool(get_bool_data(lex1) == get_bool_data(lex2));
                    }
                    else push_st_bool(get_string_data(lex1) == get_string_data(lex2));
                    break;
                
                case LEX_NEQ:

                    from_st(lex2);
                    from_st(lex1);

                    if (arg_type(lex1) == LEX_INT){
                        push_st_bool(get_int_data(lex1) != get_int_data(lex2));
                    }
                    else if (arg_type(lex1) == LEX_BOOL){
                        push_st_bool(get_bool_data(lex1) != get_bool_data(lex2));
                    }
                    else push_st_bool(get_string_data(lex1) != get_string_data(lex2));
                    break;
                
                case LEX_LESS:

                    from_st(lex2);
                    from_st(lex1);

                    if (arg_type(lex1) == LEX_INT){
                        push_st_bool(get_int_data(lex1) < get_int_data(lex2));
                    }
                    else push_st_bool(get_string_data(lex1) < get_string_data(lex2));
                    break;
                
                
                case LEX_GREATER:

                    from_st(lex2);
                    from_st(lex1);

                    if (arg_type(lex1) == LEX_INT){
                        push_st_bool(get_int_data(lex1) > get_int_data(lex2));
                    }
                    else push_st_bool(get_string_data(lex1) > get_string_data(lex2));
                    break;
                
                
                case LEX_LEQ:

                    from_st(lex2);
                    from_st(lex1);

                    push_st_bool(get_int_data(lex1) <= get_int_data(lex2));
                    break;
                    
                case LEX_GEQ:

                    from_st(lex2);
                    from_st(lex1);

                    push_st_bool(get_int_data(lex1) >= get_int_data(lex2));
                    break;
                        
                    
                case LEX_PLUS:

                    from_st(lex2);
                    from_st(lex1);
                    if (arg_type(lex1) == LEX_INT){
                        push_st_int(get_int_data(lex1) + get_int_data(lex2));
                    }
                    else push_st_string(get_string_data(lex1) + get_string_data(lex2));
                    break;
                
                case LEX_MINUS:

                    from_st(lex2);
                    from_st(lex1);

                    push_st_int(get_int_data(lex1) - get_int_data(lex2));
                    
                    break;

                case LEX_MULT:

                    from_st(lex2);
                    from_st(lex1);

                    push_st_int(get_int_data(lex1) * get_int_data(lex2));
                    
                    break;

                case LEX_DIV:

                    from_st(lex2);
                    from_st(lex1);

                    push_st_int(get_int_data(lex1) / get_int_data(lex2));
                    
                    break;

                case LEX_MOD:

                    from_st(lex2);
                    from_st(lex1);

                    push_st_int(get_int_data(lex1) % get_int_data(lex2));
                    
                    break;
                case POLIZ_GO:
                    from_st(lex1);
                    if (lex1.get_type() != POLIZ_LABEL) throw "!Ошибка при интерпретации!  Некорректная полиз-метка для безусловного перехода";
                    index = lex1.get_value();
                    break;
                
                case POLIZ_FGO:
                    from_st(lex1); // метка
                    from_st(lex2); // условие
                    if (lex1.get_type() != POLIZ_LABEL || arg_type(lex2) != LEX_BOOL) 
                        throw "!Ошибка при интерпретации!  Некорректные аргументы для перехода по лжи";
                    if (!get_bool_data(lex2)) index = lex1.get_value();

                    break;
                
                default:
                    throw curr_elem;
                    break;
            }
        }
        catch (Lex lex) {
            //cout << "Неучтенная лексема " << lex << endl;
        }
        }
        
    }
};




int main(){
    try
    {   
        Parser analyser("a.txt");
        Executer exec;
        vector<Lex> poliz;
        while (!feof(Scanner::fp)){
            poliz = analyser.analyze();
        }
        exec.execute(poliz);
        
        // cout << endl << "---Таблица всех идентификаторов---" << endl;
        // for (int i=0; i < TID.size(); i++){
        //     cout << TID[i].get_name() << " " << TID[i].get_value() << " " << TID[i].get_ind() << " "<<TID[i].get_content() << endl; 
        // }
        
    }
    catch(const char* message)
    {
		
        cerr << endl << Scanner::str_counter <<  " : " << message << endl;
    }
    catch(string message)
    {
        cerr << endl << Scanner::str_counter <<  " : " << message << endl;
    }
    catch(char c)
    {
        cerr << endl << Scanner::str_counter <<  " : " << "!Ошибка при лексическом анализе! Недопустимый символ: " << c << endl;
    }

    catch(Lex lex){
        cerr << endl << Scanner::str_counter <<  " : " << "!Ошибка при синтаксическом анализе! Недопустимая лексема: " << lex << endl;
    }

    return 0;
}
