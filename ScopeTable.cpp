using namespace std;
#include "SymbolInfo.cpp"



 unsigned int SDBMHash(string str, unsigned int num_buckets) {
	unsigned long long hash = 0;
	unsigned long long i = 0;
	unsigned long long len = str.length();

	for (i = 0; i < len; i++)
	{
		hash = ((str[i]) + (hash << 6) + (hash << 16) - hash) % num_buckets;
	}

	return hash;
}

unsigned djb2_hash(string str, unsigned num_buckets) {
    unsigned long long hash = 5381;
    for (char c : str)
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    return hash % num_buckets;
}

unsigned polynomial_hash(string str, unsigned num_buckets) {
    const int p = 31;
    const int m = 1e9 + 9;
    unsigned long long hash = 0, p_pow = 1;
    for (char c : str) {
        hash = (hash + (c - 'a' + 1) * p_pow) % m;
        p_pow = (p_pow * p) % m;
    }
    return hash % num_buckets;
}

class ScopeTable{
    private:
        unsigned (*hashFunc)(string, unsigned); 
        static int scopeId;
        SymbolInfo **array;
        int num_buckets;
        ScopeTable* parentSCope;
        int collisionCount;
        int id;
    public:
        ScopeTable(int size,ScopeTable* parent=nullptr,unsigned (*hashF)(string, unsigned)=SDBMHash){
            this->id = scopeId++;
            this->hashFunc = hashF;
            this->collisionCount = 0;
            array = new SymbolInfo*[size];
            for(int i=0;i<size;i++){
                array[i] = nullptr;
            }
            this->num_buckets = size;
            this->parentSCope = parent;
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
        ScopeTable* getParent(){
            return this->parentSCope;
        }
        int getId(){
            return this->id;
        }
        int getCollision(){
            return this->collisionCount;
        }
        bool insert(string name, string type, string toPrint=""){
            int chainPosition = 1;
            SymbolInfo* newSymbol = new SymbolInfo(name,type,toPrint);
            unsigned int bucketNumber = hashFunc(name,num_buckets);
            //int bucketNumber = hashNumber % num_buckets;
            //cout<<"yoo "<<bucketNumber<<endl;
            if(array[bucketNumber]==nullptr){
                array[bucketNumber] = newSymbol;
                cout<<"\tInserted in ScopeTable# "<<this->id<<" at position "<<bucketNumber+1<<", "<<chainPosition<<endl;
                return true;

            }
            else{
                this->collisionCount++;
                SymbolInfo* temp = array[bucketNumber];
                if(temp->getName()==name){
                    delete newSymbol;
                    cout<<"\t'"<<name<<"'"<<" already exists in the current ScopeTable"<<endl;
                    return false;
                }
                while(temp->getNext()!=nullptr){
                    temp = temp->getNext();
                    chainPosition++;
                    if(temp->getName()==name){
                        delete newSymbol;
                        cout<<"\t'"<<name<<"'"<<" already exists in the current ScopeTable"<<endl;
                        return false;
                    }
                }
                temp->setNext(newSymbol);
                chainPosition++;
                cout<<"\tInserted in ScopeTable# "<<this->id<<" at position "<<bucketNumber+1<<", "<<chainPosition<<endl;
                return true;
            }
        }
        SymbolInfo* LookUp(string name){

            int bucket = hashFunc(name,num_buckets);
            SymbolInfo* temp = array[bucket];
            int chainPosition = 1;
            if(array[bucket]==nullptr){
                return nullptr;
            }
            do{
                string symbolName = temp->getName();
                if(symbolName == name){
                    cout<<"\t'"<<symbolName<<"' found in ScopeTable# "<<this->id<<" at position "<<bucket+1<<", "<<chainPosition<<endl;
                    return temp;
                }
                temp = temp->getNext();
                chainPosition++;
            } 
            while(temp!=nullptr);
            return nullptr;
        }
        bool Delete(string name){
            int chainPosition = 1;
            int bucket = hashFunc(name, num_buckets);
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
                cout<<"\tDeleted '"<<name<<"' from ScopeTable# "<<this->id<<" at position "<<bucket+1<<", "<<chainPosition<<endl;
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
                        cout<<"\tDeleted '"<<name<<"' from ScopeTable# "<<this->id<<" at position"<<bucket+1<<", "<<chainPosition<<endl;
                        return true;
                    }
                    temp = temp->getNext();
                    chainPosition++;
                } 
            }
            return false;
        }

        void print(int indentLevel) {

            for(int i = 0; i < indentLevel; i++) cout << '\t';
            cout << "ScopeTable# " << id << '\n';

            for (int b = 0; b < num_buckets; b++) {
                for(int i = 0; i < indentLevel; i++) cout << '\t';
                cout << (b+1) << "--> ";
                SymbolInfo* cur = array[b];
                while (cur) {
                    cout << cur->getPrintingLine() << ' ';
                    cur = cur->getNext();
                }
                cout << '\n';
            }
        }

    };
