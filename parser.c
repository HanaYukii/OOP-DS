%{
struct type
{
  char* str;
};
#define YYSTYPE type

#include <stdio.h>
#include <stdlib.h>
#include<bits/stdc++.h>
#define pb push_back
#define tclr tmp=(symbol){"","",0,"",""};
using namespace std;
extern "C"
{
  int yyerror(char *msg);
  extern int yylex(void);
}

extern int linenum;
extern FILE *yyin;
extern char *yytext;
extern char buf[256];
extern int yylex();
extern int Else;
extern int Opt_Symbol;
extern int nowlv;
int yylex();
int yyerror( char *msg );
/*struct type{
  char *str;
}*/
struct symbol{
  string name;
  string stype;
  int lv;
  string types;
  string att;
};

symbol tmp;
vector< vector < symbol > >symboltable;
vector<symbol>atable;
vector<symbol>ttable;
void printTable(vector<symbol> table){
  printf("=======================================================================================\n"); 
  printf("Name");
  printf("%*c", 29, ' ');
  printf("Kind");
  printf("%*c", 7, ' ');
  printf("Level"); 
  printf("%*c", 7, ' ');
  printf("Type");
  printf("%*c", 15, ' ');
  printf("Attribute");
  printf("%*c", 15, ' ');
  printf("\n");
  printf("---------------------------------------------------------------------------------------\n");
  for(int i=0;i<table.size();i++){
    cout << setiosflags( ios::left ) << setw(33) << table[i].name 
    << setw(11) << table[i].types 
    << setw(12) << table[i].lv 
    << setw(19) << table[i].stype 
    << setw(15) << table[i].att;
    printf("\n");
    
  }
  printf("=======================================================================================\n");
}
void elseprint(){
  if(Else){
      printTable(symboltable[(int)symboltable.size()-1]);
      symboltable.pop_back();
      Else=0;
  }
}
void Insert(symbol x,int lv,int c){
  vector<symbol>start;
  if(lv>(int)symboltable.size()-1){
    symboltable.pb(start);
  }
  else if(lv<symboltable.size()-1){
    if(Opt_Symbol)
      printTable(symboltable[lv+1]);
    symboltable.pop_back();
  }
  if(c){
    symboltable[lv].pb(x);
  }
  else{
    symboltable[lv].insert(symboltable[lv].begin(),x);
  }
}
bool dupl(symbol tmp,int lv){
  int f=0;
  for(int i=0;i<symboltable[lv].size();i++){
    if(symboltable[lv][i].name==tmp.name){
      f=1;
    }
  }
  if(f){
    cout<<"##########Error at Line " << linenum << ": " <<tmp.name << " redeclared##########" << endl;
  }
  return f^1;
}
%}

%token  ID
%token  INT_CONST
%token  FLOAT_CONST
%token  SCIENTIFIC
%token  STR_CONST

%token  LE_OP
%token  NE_OP
%token  GE_OP
%token  EQ_OP
%token  AND_OP
%token  OR_OP

%token  READ
%token  BOOLEAN
%token  WHILE
%token  DO
%token  IF
%token  ELSE
%token  TRUE
%token  FALSE
%token  FOR
%token  INT
%token  PRINT
%token  BOOL
%token  VOID
%token  FLOAT
%token  DOUBLE
%token  STRING
%token  CONTINUE
%token  BREAK
%token  RETURN
%token  CONST

%token  L_PAREN
%token  R_PAREN
%token  COMMA
%token  SEMICOLON
%token  ML_BRACE
%token  MR_BRACE
%token  L_BRACE
%token  R_BRACE
%token  ADD_OP
%token  SUB_OP
%token  MUL_OP
%token  DIV_OP
%token  MOD_OP
%token  ASSIGN_OP
%token  LT_OP
%token  GT_OP
%token  NOT_OP

/*  Program 
    Function 
    Array 
    Const 
    IF 
    ELSE 
    RETURN 
    FOR 
    WHILE
*/
%start program
%%

program : decl_list funct_def decl_and_def_list {
            int la=symboltable.size();
            for(int i=la-1;i>=0;i--){
              if(Opt_Symbol) {
                printTable(symboltable[i]);
              }
            }
        }
        ;

decl_list : decl_list var_decl
          | decl_list const_decl
          | decl_list funct_decl
          | 
          ;


decl_and_def_list : decl_and_def_list var_decl
                  | decl_and_def_list const_decl
                  | decl_and_def_list funct_decl
                  | decl_and_def_list funct_def
                  | 
                  ;

funct_def : scalar_type ID L_PAREN R_PAREN compound_statement
          {
              string str1($1.str),str2($2.str);
              tmp.name=str2;tmp.stype=str1;
              tmp.types="function";
              tmp.lv=nowlv;
              Insert(tmp,nowlv,1);
              tclr;
          }
          | scalar_type ID L_PAREN parameter_list R_PAREN  compound_statement
          {
              for(int i=(int)atable.size()-1;i>=0;i--){
                Insert(atable[i],level+1,0);
              }
              atable.clear();
              string str1($1.str),str2($2.str),str3($4.str);
              tmp.name=str2;tmp.stype=str1;
              tmp.types="function";
              tmp.lv=nowlv;
              tmp.att=str3;
              Insert(tmp,nowlv,1);
              tclr;
          }
          | VOID ID L_PAREN R_PAREN compound_statement
          {
              string str1($2.str);
              tmp.name=str1;
              tmp.stype="void";
              tmp.types="function"; 
              tmp.lv=nowlv;
              Insert(tmp,nowlv,1);
          }
          | VOID ID L_PAREN parameter_list R_PAREN compound_statement
          {
              for(int i=(int)atable.size()-1;i>=0;i--){
                Insert(atable[i],level+1,0);
              }
              atable.clear();
              string str1($4.str),str2($2.str);
              tmp.name=str2;tmp.stype="void";
              tmp.types="function";
              tmp.lv=nowlv;
              tmp.att=str1;
              Insert(tmp,nowlv,1);
              tclr
          }
          ;

funct_decl : scalar_type ID L_PAREN R_PAREN SEMICOLON
          {
              string str1($1.str),str2($2.str);
              tmp.name=str2;tmp.stype=str1;
              tmp.types="function";
              tmp.lv=nowlv;
              Insert(tmp,nowlv,1);
              tclr;
          }
           | scalar_type ID L_PAREN parameter_list R_PAREN SEMICOLON
           {
              string str1($1.str),str2($2.str),str3($4.str);
              tmp.name=str2;tmp.stype=str1;tmp.att=str3;
              tmp.types="function";
              tmp.lv=nowlv;
              Insert(tmp,nowlv,1);
              tclr;
              atable.clear();
           }
           | VOID ID L_PAREN R_PAREN SEMICOLON
           {
              string str1($2.str);
              tmp.name=str1;
              tmp.stype="void";
              tmp.types="function"; 
              tmp.lv=nowlv;
              Insert(tmp,nowlv,1);
           }
           | VOID ID L_PAREN parameter_list R_PAREN SEMICOLON
           {
              string str1($2.str),str2($4.str);
              tmp.name=str1;
              tmp.att=str2;
              tmp.stype="void";
              tmp.types="function"; 
              tmp.lv=nowlv;
              Insert(tmp,nowlv,1);
              atable.clear();
           }
           ;

parameter_list : parameter_list COMMA scalar_type ID
                { 
                    string tp($3.str),id($4.str);
                    tp=","+tp;
                    strcat($$.str,tp.c_str());
                    symbol arg;
                    tp.erase(tp.begin()+0);
                    arg.stype=tp;
                    arg.name=id;
                    arg.lv=nowlv+1;
                    arg.types="parameter";
                    atable.pb(arg);
                }
               | parameter_list COMMA scalar_type ID dim
               {
                  string tp($3.str),dm($5.str),id($4.str);
                  tp=","+tp;
                  strcat($$.str,tp.c_str());
                  strcat($$.str,dm.c_str());
                  symbol arg;
                  tp.erase(tp.begin()+0);
                  arg.stype=tp;
                  arg.name=id;
                  arg.lv=nowlv+1;
                  arg.types="parameter";
                  atable.pb(arg);

               }
               | scalar_type ID dim
               {
                  string tp($1.str);
                  string id($2.str);
                  string dm($3.str);
                  strcpy($$.str,$1.str);
                  strcat($$.str,$3.str);
                  string mix($$.str);
                  symbol arg;
                  arg.name=id;
                  arg.stype=mix;
                  arg.lv=nowlv+1;
                  arg.types="parameter";
                  atable.pb(arg);
               }
               | scalar_type ID
               {
                  strcpy($$.str,$1.str);
                  symbol arg;
                  string id($2.str),tp($1.str);
                  arg.stype=tp;
                  arg.name=id;
                  arg.lv=nowlv+1;
                  atable.pb(arg);
               }
               ;

var_decl : scalar_type identifier_list SEMICOLON
          {
              for(int i=0;i<(int)ttable.size();i++){
                string st($1.str);
                ttable[i].stype=st+ttable[i].stype;
                ttable[i].lv=nowlv;
                ttable[i].types="variable";
              }
              for(int i=0;i<(int)ttable.size();i++){
                Insert(ttable[i],nowlv,1);
              }
              ttable.clear();
              tclr;
          }
         ;

identifier_list : identifier_list COMMA ID
                {
                    string id($3.str);
                    tmp.name=id;
                    ttable.push_back(tmp);
                    tclr;
                }
                | identifier_list COMMA ID ASSIGN_OP logical_expression
                {
                    string id($3.str);
                    tmp.name=id;
                    ttable.pb(tmp);
                    tmp=(symbol){"","",0,"",""};
                }
                | identifier_list COMMA ID dim ASSIGN_OP initial_array
                {
                    string id($3.str);
                    tmp.name=id;
                    string dm($4.str);
                    tmp.stype=dm;
                    ttable.pb(tmp);
                    tclr
                }
                | identifier_list COMMA ID dim
                {
                    string id($3.str),dm($4.str);
                    tmp.name=id;
                    tmp.stype=dm;
                    ttable.pb(tmp);
                    tclr
                }
                | ID dim ASSIGN_OP initial_array
                {
                    string id($1.str),dm($2.str);
                    tmp.name=id;
                    tmp.stype=dm;
                    ttable.pb(tmp);
                    tclr
                }
                | ID dim
                {
                    string id($1.str),dm($2.str);
                    tmp.name=id;
                    tmp.stype=dm;
                    ttable.pb(tmp);
                    tclr
                }
                | ID ASSIGN_OP logical_expression
                {
                    string id($1.str);
                    tmp.name=id;
                    ttable.pb(tmp);
                    tclr
                }
                | ID
                {
                    string id($1.str);
                    tmp.name=id;
                    //cout<
                    ttable.pb(tmp);
                    tclr
                }
                ;

initial_array : L_BRACE literal_list R_BRACE
              ;

literal_list : literal_list COMMA logical_expression
             | logical_expression
             | 
             ;

const_decl : CONST scalar_type const_list SEMICOLON
            {
              for(int i=0;i<(int)ttable.size();i++){
                string st($2.str);
                ttable[i].stype=st;
                //ttable[i].lv=nowlv;
                //ttable[i].types="variable";
              }
              for(int i=0;i<(int)ttable.size();i++){
                Insert(ttable[i],nowlv,1);
              }
              ttable.clear();
              tclr;
            }
            ;

const_list : const_list COMMA ID ASSIGN_OP literal_const
            {
              string id($3.str),lc($5.str);
              tmp.name=id;
              tmp.att=lc;
              tmp.types="constant";
              tmp.lv=nowlv;
              ttable.pb(tmp);
            }
           | ID ASSIGN_OP literal_const
           {
              string id($1.str),lc($3.str);
              tmp.name=id;
              tmp.types="constant";
              tmp.att=lc;
              ttable.pb(tmp);
           }
           ;

//array_decl : ID dim
//           ;

dim : dim ML_BRACE INT_CONST MR_BRACE
    {
      string str1($2.str),str4($3.str),str2($4.str),str3($1.str);
      str1+=str4;
      str1+=str2;
      str1=str3+str1;
      strcpy($$.str,str1.c_str());
    }
    | ML_BRACE INT_CONST MR_BRACE
    {
      string str1($1.str),str2($3.str),str3($2.str);
      str1+=str3;
      str1+=str2;
      strcpy($$.str,str1.c_str());
    }
    ;

compound_statement : L_BRACE var_const_stmt_list R_BRACE
                   ;

var_const_stmt_list : var_const_stmt_list statement 
                    | var_const_stmt_list var_decl
                    | var_const_stmt_list const_decl
                    |
                    ;

statement : compound_statement
          | simple_statement
          {
            elseprint();
          }
          | conditional_statement
          | while_statement
          | for_statement
          | function_invoke_statement
          {
            elseprint();
          }
          | jump_statement
          {
            elseprint();
          }
          ;     

simple_statement : variable_reference ASSIGN_OP logical_expression SEMICOLON
                 | PRINT logical_expression SEMICOLON
                 | READ variable_reference SEMICOLON
                 ;

conditional_statement : IF L_PAREN logical_expression R_PAREN L_BRACE var_const_stmt_list R_BRACE
                      {
                        elseprint();
                        printTable(symboltable[(int)symboltable.size()-1]);
                        symboltable.pop_back();
                      }
                      | IF L_PAREN logical_expression R_PAREN 
                            L_BRACE var_const_stmt_list R_BRACE
                        ELSE
                            L_BRACE var_const_stmt_list R_BRACE
                        {
                           elseprint();
                          printTable(symboltable[(int)symboltable.size()-1]);
                          symboltable.pop_back();
                        }
                      ;
while_statement : WHILE L_PAREN logical_expression R_PAREN
                    L_BRACE var_const_stmt_list R_BRACE
                    {
                      elseprint();
                      printTable(symboltable[(int)symboltable.size()-1]);
                      symboltable.pop_back();
                    }
                | DO L_BRACE
                    var_const_stmt_list
                  R_BRACE WHILE L_PAREN logical_expression R_PAREN SEMICOLON
                  {
                     elseprint();
                      printTable(symboltable[(int)symboltable.size()-1]);
                      symboltable.pop_back();
                  }
                ;

for_statement : FOR L_PAREN initial_expression_list SEMICOLON control_expression_list SEMICOLON increment_expression_list R_PAREN 
                    L_BRACE var_const_stmt_list R_BRACE
                    {
                       elseprint();
                       printTable(symboltable[(int)symboltable.size()-1]);
                       symboltable.pop_back();
                    }
              ;

initial_expression_list : initial_expression
                        |
                        ;

initial_expression : initial_expression COMMA variable_reference ASSIGN_OP logical_expression
                   | initial_expression COMMA logical_expression
                   | logical_expression
                   | variable_reference ASSIGN_OP logical_expression

control_expression_list : control_expression
                        |
                        ;

control_expression : control_expression COMMA variable_reference ASSIGN_OP logical_expression
                   | control_expression COMMA logical_expression
                   | logical_expression
                   | variable_reference ASSIGN_OP logical_expression
                   ;

increment_expression_list : increment_expression 
                          |
                          ;

increment_expression : increment_expression COMMA variable_reference ASSIGN_OP logical_expression
                     | increment_expression COMMA logical_expression
                     | logical_expression
                     | variable_reference ASSIGN_OP logical_expression
                     ;

function_invoke_statement : ID L_PAREN logical_expression_list R_PAREN SEMICOLON
                          | ID L_PAREN R_PAREN SEMICOLON
                          ;

jump_statement : CONTINUE SEMICOLON
               | BREAK SEMICOLON
               | RETURN logical_expression SEMICOLON
               ;

variable_reference : array_list
                   | ID
                   ;


logical_expression : logical_expression OR_OP logical_term
                   | logical_term
                   ;

logical_term : logical_term AND_OP logical_factor
             | logical_factor
             ;

logical_factor : NOT_OP logical_factor
               | relation_expression
               ;

relation_expression : relation_expression relation_operator arithmetic_expression
                    | arithmetic_expression
                    ;

relation_operator : LT_OP
                  | LE_OP
                  | EQ_OP
                  | GE_OP
                  | GT_OP
                  | NE_OP
                  ;

arithmetic_expression : arithmetic_expression ADD_OP term
                      | arithmetic_expression SUB_OP term
                      | term
                      ;

term : term MUL_OP factor
     | term DIV_OP factor
     | term MOD_OP factor
     | factor
     ;

factor : SUB_OP factor
       | literal_const
       | variable_reference
       | L_PAREN logical_expression R_PAREN
       | ID L_PAREN logical_expression_list R_PAREN
       | ID L_PAREN R_PAREN
       ;

logical_expression_list : logical_expression_list COMMA logical_expression
                        | logical_expression
                        ;

array_list : ID dimension
           ;

dimension : dimension ML_BRACE logical_expression MR_BRACE         
          | ML_BRACE logical_expression MR_BRACE
          ;



scalar_type : INT {$$=$1;}
            | DOUBLE {$$=$1;}
            | STRING {$$=$1;}
            | BOOL {$$=$1;}
            | FLOAT {$$=$1;}
            ;
 
literal_const : INT_CONST {$$=$1;}
              | FLOAT_CONST {$$=$1;}
              | SCIENTIFIC {$$=$1;}
              | STR_CONST {$$=$1;}
              | TRUE {$$=$1;}
              | FALSE {$$=$1;}
              ;


%%

int yyerror( char *msg )
{
    fprintf( stderr, "\n|--------------------------------------------------------------------------\n" );
    fprintf( stderr, "| Error found in Line #%d: %s\n", linenum, buf );
    fprintf( stderr, "|\n" );
    fprintf( stderr, "| Unmatched token: %s\n", yytext );
    fprintf( stderr, "|--------------------------------------------------------------------------\n" );
    exit(-1);
    //  fprintf( stderr, "%s\t%d\t%s\t%s\n", "Error found in Line ", linenum, "next token: ", yytext );
}


