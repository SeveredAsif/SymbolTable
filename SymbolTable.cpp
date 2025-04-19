using namespace std;
#include "ScopeTable.cpp"
int ScopeTable::scopeId = 1;

class SymbolTable
{
    private:
        ScopeTable* currentScope;
        int bucketCount;
    public:

        SymbolTable(int bucketCount=7){
            // ScopeTable.setScopeId(1);
            currentScope = new ScopeTable(bucketCount);
            this->bucketCount = bucketCount;
        }
        ~SymbolTable(){
            while(currentScope!=nullptr){
                exitScope();
            }
        }
        void enterScope(){
            ScopeTable *newScope = new ScopeTable(bucketCount,currentScope);
            this->currentScope = newScope;
        }

        void exitScope(){
            ScopeTable *toExit = currentScope;
            if(currentScope->getParent()!=nullptr){ //preventing global scope to get deleted
                this->currentScope = currentScope->getParent();
                delete toExit;
            }
        }

        bool insert(string name,string type){
            bool validity = currentScope->insert(name,type);
            return validity;
        }

        bool remove(string name){
            return currentScope->Delete(name);
        }

        SymbolInfo* lookUp(string name){
            ScopeTable* temp = currentScope;
            while(!temp->LookUp(name)){
                if(temp==nullptr){
                    return nullptr;
                }
                temp = temp->getParent();
            }
            return temp->LookUp(name);
        }

        void printCurrentScope(){
            currentScope->print();
        }

        void printAllScope(){
            ScopeTable* temp = currentScope;
            while(temp!=nullptr){
                temp->print();
                temp = temp->getParent();
            }
        }
};