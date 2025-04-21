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
            cout<<"ScopeTable# "<<getCurrectScope()->getId()<<" created"<<endl;
            this->bucketCount = bucketCount;
        }
        ~SymbolTable(){
            while(currentScope->getParent()!=nullptr){
                exitScope();
                cout<<"ScopeTable# "<<currentScope->getId()<<" removed"<<endl;
                delete currentScope;
            }
        }
        ScopeTable* getCurrectScope(){
            return currentScope;
        }
        void enterScope(){
            ScopeTable *newScope = new ScopeTable(bucketCount,currentScope);
            this->currentScope = newScope;
            cout<<"ScopeTable# "<<getCurrectScope()->getId()<<" created"<<endl;
        }

        void exitScope(){
            ScopeTable *toExit = currentScope;
            if(currentScope->getParent()!=nullptr){ //preventing global scope to get deleted
                cout<<"ScopeTable# "<<currentScope->getId()<<" removed"<<endl;
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
            while(temp!=nullptr){
                SymbolInfo* found = temp->LookUp(name);
                if(found!=nullptr){
                    return found;
                }
                temp = temp->getParent();
            }
            cout<<"'"<<name<<"' not found in any of the ScopeTables"<<endl;
            return nullptr;
        }

        void printCurrentScope(){
            cout<<"ScopeTable# "<<currentScope->getId()<<endl;
            currentScope->print();
        }

        void printAllScope(){
            ScopeTable* temp = currentScope;
            while(temp!=nullptr){
                cout<<"ScopeTable# "<<temp->getId()<<endl;
                temp->print();
                temp = temp->getParent();
                cout<<endl;
                cout<<"\t";
            }
        }
};