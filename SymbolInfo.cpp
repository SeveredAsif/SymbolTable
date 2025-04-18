#include <iostream>
#include <string>

using namespace std;

class SymbolInfo{
    private:
        string name;
        string type;
        SymbolInfo* next;
    
    public:
        SymbolInfo(){
        
        }
        ~SymbolInfo(){

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
        string setType(string type){
            this->type = type;            
        }
};