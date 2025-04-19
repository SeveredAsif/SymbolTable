using namespace std;
#include "SymbolInfo.cpp"

static unsigned long SDBMHash(string str) {
	unsigned long hash = 0;
	unsigned long i = 0;
	unsigned long len = str.length();

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
                SymbolInfo* temp = array[i];
                while(temp!=nullptr){
                    SymbolInfo* toDelete = temp;
                    temp = temp->getNext();
                    delete toDelete;
                }
            }
            delete [] array;
        }
        bool insert(string name, string type){
            SymbolInfo* newSymbol = new SymbolInfo(name,type);
            unsigned long hashNumber = SDBMHash(name);
            int bucketNumber = hashNumber % num_buckets;
            cout<<"yoo "<<bucketNumber<<endl;
            if(array[bucketNumber]==nullptr){
                array[bucketNumber] = newSymbol;
                return true;

            }
            else{
                SymbolInfo* temp = array[bucketNumber];
                if(temp->getName()==name){
                    delete newSymbol;
                    return false;
                }
                while(temp->getNext()!=nullptr){
                    temp = temp->getNext();
                    if(temp->getName()==name){
                        delete newSymbol;
                        return false;
                    }
                }
                temp->setNext(newSymbol);
                return true;
            }
        }
        SymbolInfo* LookUp(string name){

            int bucket = SDBMHash(name) % num_buckets;
            SymbolInfo* temp = array[bucket];
            if(array[bucket]==nullptr){
                return nullptr;
            }
            do{
                string symbolName = temp->getName();
                if(symbolName == name){
                    return temp;
                }
                temp = temp->getNext();
            } 
            while(temp!=nullptr);
            return nullptr;
        }
        bool Delete(string name){
            int bucket = SDBMHash(name) % num_buckets;
            if(array[bucket]==nullptr){
                return false;
            }
            SymbolInfo* temp = array[bucket];
            string symbolName = temp->getName();
            if(symbolName==name){
                SymbolInfo* toDelete = temp;
                array[bucket] = toDelete->getNext();
                toDelete->setNext(nullptr);
                delete toDelete;
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
                    temp = temp->getNext();
                } 
            }
            return false;
        }

        void print(){
            for (int i=0;i<num_buckets;i++){
                cout<<i+1<<". ";
                SymbolInfo* temp = array[i];
                if(temp!=nullptr){
                    cout<<temp->getName()<<" Type: "<<temp->getType();
                    temp = temp->getNext();
                }

                while(temp!=nullptr){
                    cout<<"-->"<<temp->getName()<<" Type: "<<temp->getType(); 
                    temp = temp->getNext();                   
                }
                cout<<""<<endl;
            }
        }
    };

    int main(){
        ScopeTable st(7);
        st.insert("foo","any");
    }