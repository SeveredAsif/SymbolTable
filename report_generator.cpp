// report_generator.cpp
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include "SymbolTable.hpp"
using namespace std;

// Define 100 realistic identifiers and their types
const int MAX_INPUT_SIZE = 100;
const char* inputNames[MAX_INPUT_SIZE] = {
    "foo", "i", "23", "car", "brand", "<=", "==", ">=", "x", "y", "num", "bicycle", "true", "a",
    "apple", "banana", "cherry", "date", "elderberry", "fig", "grape", "honeydew",
    "jackfruit", "kiwi", "lemon", "mango", "nectarine", "orange", "papaya", "quince",
    "rose", "sunflower", "tulip", "violet", "watermelon", "xigua", "yam", "zucchini",
    "air", "boat", "caravan", "drone", "engine", "ferry", "glider", "helicopter",
    "iceberg", "jet", "kayak", "lifeboat", "motorbike", "nautical", "orbiter", "plane",
    "quadbike", "rocket", "submarine", "tram", "unicycle", "van", "wagon", "zeppelin",
    "actor", "baker", "chef", "driver", "editor", "farmer", "guard", "host",
    "illustrator", "janitor", "knight", "lawyer", "miner", "nurse", "officer", "pilot",
    "queen", "ranger", "soldier", "teacher", "umpire", "vet", "waiter", "xylophonist",
    "yogi", "zoologist", "alpha", "beta", "gamma", "delta", "epsilon", "zeta",
    "eta", "theta", "iota", "kappa", "lambda", "mu"
};
const char* inputTypes[MAX_INPUT_SIZE] = {
    "FUNCTION","VAR","NUMBER","STRUCT","VAR","RELOP","RELOP","RELOP","VAR","VAR","VAR","UNION","BOOL","VAR",
    "VAR","VAR","VAR","VAR","VAR","VAR","VAR","VAR",
    "VAR","VAR","VAR","VAR","VAR","VAR","VAR","VAR",
    "VAR","VAR","VAR","VAR","VAR","VAR","VAR","VAR",
    "VAR","VAR","VAR","VAR","VAR","VAR","VAR","VAR",
    "VAR","VAR","VAR","VAR","VAR","VAR","VAR","VAR",
    "VAR","VAR","VAR","VAR","VAR","VAR","VAR","VAR",
    "VAR","VAR","VAR","VAR","VAR","VAR","VAR","VAR",
    "VAR","VAR","VAR","VAR","VAR","VAR","VAR","VAR",
    "VAR",
    // fill remaining with VAR
    "VAR","VAR","VAR","VAR","VAR","VAR","VAR","VAR","VAR","VAR",
    "VAR","VAR","VAR","VAR","VAR","VAR","VAR","VAR","VAR","VAR",
    "VAR"
};

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <SDBM|DJB2|POLY>" << endl;
        return 1;
    }

    string hashName = argv[1];
    unsigned (*hashFunc)(string, unsigned) = SDBMHash;
    if (hashName == "DJB2") hashFunc = djb2_hash;
    else if (hashName == "POLY") hashFunc = polynomial_hash;
    else if (hashName != "SDBM") {
        cerr << "Unknown hash function: " << hashName << endl;
        return 1;
    }

    const int numInserts = MAX_INPUT_SIZE;
    const int bucketCount = 50;  // fixed bucket size

    // Create exactly one table and scope
    SymbolTable* st = new SymbolTable(bucketCount, hashFunc);
    ScopeTable* scope = st->getCurrectScope();

    // Perform 100 insertions
    for (int i = 0; i < numInserts; i++) {
        string name = inputNames[i];
        string type = inputTypes[i];
        string toPrint = "<" + name + "," + type + ">";
        scope->insert(name, type, toPrint);
    }

    // Retrieve collisions
    int collisionCount = scope->getCollision();

    // Write report
    string fileName = string("report_") + hashName + ".csv";
    ofstream report(fileName.c_str());
    report.setf(ios::fixed);
    report.precision(2);
    report << "HashFunction,Inputs,BucketSize,Collisions,CollisionRatio\n";
    report << hashName << "," << numInserts << "," << bucketCount << ","
           << collisionCount << "," << ((double)collisionCount / bucketCount) << "\n";
    report.close();

    cout << "Report generated in '" << fileName << "'." << endl;
    delete st;
    return 0;
}
