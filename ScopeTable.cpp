using namespace std;
#include "SymbolInfo.cpp"

class ScopeTable{
    private:
        SymbolInfo **array;
        int size;
    public:
        ScopeTable(int size){
            array = new SymbolInfo*[size];
            this->size = size;
        }
        ~ScopeTable(){
            for (int i=0;i<size;i++){
                delete array[i];
            }
            delete [] array;
        }
        bool insert(string name, string type){
            SymbolInfo* newSymbol = new SymbolInfo();
            newSymbol->setName(name);
            newSymbol->setType(type);
        }
};