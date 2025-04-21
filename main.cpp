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

    //cout<<numberOfBuckets<<endl;

    //initializing symbol Table
    SymbolTable* st = new SymbolTable(numberOfBuckets);
    int commandNumber = 0;


    
    string line;
    while (getline(cin, line)) {
        stringstream s(line); 
        commandNumber++;
        // To store individual words
        string word; 
    
        int count = 0;
        
        while (s >> word)
            count++;
        cout << "Cmd "<<commandNumber<<": "<<line <<" "<<'\n';
        cout<<'\t';

        ScopeTable* scopeTable = st->getCurrectScope();

        string *arg = new string[count];
        int index = 0;

        stringstream stream(line); 
        while (stream >> word)
            arg[index++] = word;
        

        // for(int i=0;i<count;i++){
        //     cout<<arg[i]<<endl;
        // }

        if(arg[0]=="I"){
            if(arg[2]=="VAR" || arg[2]=="NUMBER"){
                if(count!=3){
                    cout<<"Number of parameters mismatch for the command I"<<endl;
                    continue;
                }
                string toPrint = "<" + arg[1] + "," + arg[2] + ">";
                // cout<<toPrint<<endl;
                scopeTable->insert(arg[1],arg[2],toPrint);
            }
            else if(arg[2]=="STRUCT"){
                if(count<3){
                    cout<<"Number of parameters mismatch for the command I"<<endl;
                    continue;                    
                }
                string structInfo;
                for(int i=3;i<count;i=i+2){
                    if(i==count-2) { 
                        structInfo +=  "(" + arg[i]+","+arg[i+1]+")";
                    }
                    else {
                        structInfo +=  "(" + arg[i]+","+arg[i+1]+"),";
                    }
                }
                string toPrint = "<" + arg[1] + "," + arg[2] + ",{" +structInfo+"}"+">";
                scopeTable->insert(arg[1],arg[2],toPrint);
                // cout<<toPrint<<endl;
            }
            else if(arg[2]=="UNION"){
                if(count<3){
                    cout<<"Number of parameters mismatch for the command I"<<endl;
                    continue;                    
                }
                string structInfo;
                for(int i=3;i<count;i=i+2){
                    if(i==count-2) { 
                        structInfo +=  "(" + arg[i]+","+arg[i+1]+")";
                    }
                    else {
                        structInfo +=  "(" + arg[i]+","+arg[i+1]+"),";
                    }
                }
                string toPrint = "<" + arg[1] + "," + arg[2] + ",{" +structInfo+"}"+">";
                scopeTable->insert(arg[1],arg[2],toPrint);
                // cout<<toPrint<<endl;

            }
            else if(arg[2]=="FUNCTION"){
                if(count<3){
                    cout<<"Number of parameters mismatch for the command I"<<endl;
                    continue;                    
                }
                string structInfo="";
                for(int i=3;i<count;i++){
                    if(i==count-1) { 
                        structInfo +=  arg[i];
                    }
                    else {
                        structInfo +=  arg[i]+",";
                    }
                }
                string toPrint = "<" + arg[1] + "," + arg[2] + "," +arg[3] + "<==(" +structInfo+")>";
                scopeTable->insert(arg[1],arg[2],toPrint);
                // cout<<toPrint<<endl;

            }
        }
        else if(arg[0]=="L"){
            if(count!=2){
                cout<<"Number of parameters mismatch for the command L"<<endl;
                continue;         
            }
            SymbolInfo* symbol =  st->lookUp(arg[1]);
        }
        else if(arg[0]=="D"){
            if(count!=2){
                cout<<"Number of parameters mismatch for the command D"<<endl;
                continue;         
            }
            bool confirmation = st->getCurrectScope()->Delete(arg[1]);
            if (confirmation==false){
                cout<<"Not found in the current ScopeTable"<<endl;
            }
        }
        else if(arg[0]=="P"){
            if(count!=2){
                cout<<"Number of parameters mismatch for the command I"<<endl;
                continue;         
            }
            if(arg[1]=="C"){
                st->printCurrentScope();
            }
            else if(arg[1]=="A"){
                st->printAllScope();
            }
        }
        else if(arg[0]=="S"){
            if(count!=1){
                cout<<"Number of parameters mismatch for the command S"<<endl;
                continue;         
            }
            st->enterScope();
            
        }
        else if(arg[0]=="E"){
            if(count!=1){
                cout<<"Number of parameters mismatch for the command E"<<endl;
                continue;         
            }
            st->exitScope();
        }
        else if(arg[0]=="Q"){
            if(count!=1){
                cout<<"Number of parameters mismatch for the command Q"<<endl;
                continue;         
            }
            delete st;
            break;
        }

    }
    cin.rdbuf(cinbuf);
    cout.rdbuf(coutbuf);

}
