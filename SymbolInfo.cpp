#include <iostream>
#include <string>

using namespace std;

class SymbolInfo{
    private:
        string name;
        string type;
        SymbolInfo* next;
    public:
        SymbolInfo(string name, string type){
            this->name = name;
            this->type = type;
            this->next = nullptr;
        }

        string getName(){
            return this->name;
        }
        void setName(string name){
            this->name = name;
        }
        string getType(){
            return this->type;
        }
        void setType(string type){
            this->type = type;            
        }
        SymbolInfo* getNext(){
            return this->next;
        }
        void setNext(SymbolInfo* next){
            this->next = next;
        }
};