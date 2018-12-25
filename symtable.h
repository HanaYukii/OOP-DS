#include"datatype.h"
#include<vector>
using namespace std;
int initSymTableList(struct SymTableList *list);
int destroySymTableList(struct SymTableList *list);
//

int AddSymTable(struct SymTableList* list);
struct SymTable* deleteSymTable(struct SymTable* target);
int deleteLastSymTable(struct SymTableList* list);
int insertTableNode(struct SymTable *table,struct SymTableNode* newNode);
//
struct SymTableNode* deleteTableNode(struct SymTableNode* target);
struct SymTableNode* createVariableNode(const char* name,int level,struct ExtType* type);
struct SymTableNode* createFunctionNode(const char* name,int level,struct ExtType* type,struct Attribute* attr);
struct SymTableNode* createConstNode(const char* name,int level,struct ExtType* type,struct Attribute* attr);
struct SymTableNode* createParameterNode(const char* name,int level,struct ExtType* type);
//
struct Attribute* createFunctionAttribute(struct FuncAttrNode* list);
struct Attribute* createConstantAttribute(BTYPE type,void* value);
struct FuncAttrNode* deleteFuncAttrNode(struct FuncAttrNode* target);
int killAttribute(struct Attribute* target);
struct FuncAttrNode* createFuncAttrNode(struct ExtType* type,const char* name);
int connectFuncAttrNode(struct FuncAttrNode* head, struct FuncAttrNode* newNode);
//
struct ExtType* createExtType(BTYPE baseType,bool isArray,struct ArrayDimNode* dimArray);
int killExtType(struct ExtType* target);
//
struct ArrayDimNode* createArrayDimNode(int size);
int connectArrayDimNode(struct ArrayDimNode* head,struct ArrayDimNode* newNode);
struct ArrayDimNode* deleteArrayDimNode(struct ArrayDimNode* target);
//
struct SymTableNode* findFuncDeclaration(struct SymTable* table,const char* name);
int printSymTable(struct SymTable* table);
int printType(struct ExtType* extType);
int printConstAttribute(struct ConstAttr* constAttr);
int printParamAttribute(struct FuncAttr* funcAttr);

//
struct VariableList* createVariableList(struct Variable* head);
int deleteVariableList(struct VariableList* list);
int connectVariableList(struct VariableList* list,struct Variable* node);
struct Variable* createVariable(const char* name,struct ExtType* type);
struct Variable* deleteVariable(struct Variable* target);
BTYPE ID2BTYPE(struct SymTable* table, const char* name);
BTYPE arrayNameCheck(struct SymTable* table, const char* name, vector< BTYPE > arrayCheck);
bool redeclareCheck(struct SymTable* table, const char* name);
void arrayDeclareCheck(vector<BTYPE> v1, struct ArrayDimNode* dimNode, BTYPE t1);
void returnTypeCheck(BTYPE t1, BTYPE returnType[100], int return_linenum[100], int return_count);
void assignTypeCheck(BTYPE t1, BTYPE t2);
void functDeclDefParamCheck(struct FuncAttrNode *attr1, struct FuncAttrNode *attr2);
void conditionalStatementBoolCheck(BTYPE t1, int logical_expression_num);
BTYPE functNoParamInvokeCheck(struct SymTable* table, const char* name);
BTYPE functParamInvokeCheck(struct SymTable* table, const char* name, vector<BTYPE> v);
void declAssignTypeCheck(BTYPE t1, BTYPE t2);
