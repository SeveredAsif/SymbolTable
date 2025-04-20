#include<iostream>
#include <fstream> 
#include<sstream>
#include<string>
#include "SymbolTable.cpp"
using namespace std;

int main() {
    ifstream input("in.txt");
    ofstream output("out.txt");
    
    if (!input.is_open()) {
        cerr << "Failed to open input file\n";
        return 1;
    }
    if (!output.is_open()) {
        cerr << "Failed to open output file\n";
        return 1;
    }

    streambuf* cinbuf = cin.rdbuf();
    streambuf* coutbuf = cout.rdbuf();
    
    cin.rdbuf(input.rdbuf());
    cout.rdbuf(output.rdbuf());

    int numberOfBuckets;
    cin>>numberOfBuckets;
    cin.ignore();

    cout<<numberOfBuckets+1<<endl;

    //initializing symbol Table
    SymbolTable* st = new SymbolTable(numberOfBuckets);


    
    string line;
    while (getline(cin, line)) {
        stringstream s(line); 
  
        // To store individual words
        string word; 
    
        int count = 0;
        while (s >> word)
            count++;
        cout << line <<" "<<count<<'\n';

        ScopeTable* scopeTable = st->getCurrectScope();

        string *arg = new string[count];
        int index = 0;

        stringstream stream(line); 
        while (stream >> word)
            arg[index++] = word;
        

        for(int i=0;i<count;i++){
            cout<<arg[i]<<endl;
        }

        if(arg[0]=="I"){}
        else if(arg[0]=="I"){
            if(arg[2]=="VAR"){
                if(count!=3){
                    cout<<"Number of parameters mismatch for the command I"<<endl;
                    continue;
                }
                scopeTable->insert(arg[1],arg[2]);
            }
            else if(arg[2]=="STRUCT"){

            }
            else if(arg[2]=="UNION"){

            }
            else if(arg[2]=="FUNCTION"){

            }
        }
        else if(arg[0]=="L"){}
        else if(arg[0]=="D"){}
        else if(arg[0]=="P"){}
        else if(arg[0]=="S"){}
        else if(arg[0]=="E"){}
        else if(arg[0]=="Q"){}

    }
    cin.rdbuf(cinbuf);
    cout.rdbuf(coutbuf);

}
