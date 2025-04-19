using namespace std;
#include "SymbolInfo.cpp"

static unsigned int SDBMHash(string str) {
	unsigned int hash = 0;
	unsigned int i = 0;
	unsigned int len = str.length();

	for (i = 0; i < len; i++)
	{
		hash = (str[i]) + (hash << 6) + (hash << 16) - hash;
	}

	return hash;
}

class ScopeTable{
    private:
        SymbolInfo **array;
        int num_buckets;
    public:
        ScopeTable(int size){
            array = new SymbolInfo*[size];
            for(int i=0;i<size;i++){
                array[i] = nullptr;
            }
            this->num_buckets = size;
        }
        ~ScopeTable(){
            for (int i=0;i<num_buckets;i++){
                delete array[i];
            }
            delete [] array;
        }
        bool insert(string name, string type){
            SymbolInfo* newSymbol = new SymbolInfo();
            newSymbol->setName(name);
            newSymbol->setType(type);
            int hashNumber = SDBMHash(name);
            int bucketNumber = hashNumber % num_buckets;
            if(array[bucketNumber]==nullptr){
                array[bucketNumber] = newSymbol;

            }
            else{
                SymbolInfo* temp = array[bucketNumber];
                while(temp->getNext()!=nullptr){
                    temp = temp->getNext();
                }
                temp->setNext(newSymbol);
            }
        }
        SymbolInfo* LookUp(string name){

            int bucket = SDBMHash(name) % num_buckets;
            SymbolInfo* temp = array[bucket];
            do{
                string symbolName = temp->getName();
                if(symbolName == name){
                    return temp;
                }
            } 
            while(temp->getNext()!=nullptr);
            return nullptr;
        }
        bool Delete(string name){
            int bucket = SDBMHash(name) % num_buckets;
            SymbolInfo* temp = array[bucket];
            string symbolName = temp->getName();
            if(symbolName==name){
                array[bucket] = temp->getNext();
                temp->setNext(nullptr);
                return true;
            }
            else{
                while(temp->getNext()!=nullptr)
                {
                    string symbolName = temp->getNext()->getName();
                    if(symbolName == name){
                        SymbolInfo* toDelete = temp->getNext();
                        temp->setNext(temp->getNext()->getNext());
                        delete toDelete;
                        return true;
                    }
                } 
            }
            return false;
        }

        void print(){
            for (int i=0;i<num_buckets;i++){
                cout<<i+1<<". ";
                SymbolInfo* temp = array[i];
                cout<<temp->getName()<<" Type: "<<temp->getType();
                temp = temp->getNext();
                while(temp!=nullptr){
                    cout<<"-->"<<temp->getName()<<" Type: "<<temp->getType();                    
                }
                cout<<""<<endl;
            }
        }
    };