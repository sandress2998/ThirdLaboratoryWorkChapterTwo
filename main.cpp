#include <iostream>
#include <string>
#include "DataStructures/HashTable.h"
#include "HashFunction.h"
#include "AlphabeticalIndexHeaders/Word.h"
#include "Parser.h"

#include "AlphabeticalIndexHeaders/Line.h"

int main() {
    
    MutableSegmentedDeque<Word*> wordsDeque(10);
    HashTable<Word> hashTable(10, &djb2_hash);
    std::string str = "are you the only one";
    parse(str, hashTable, wordsDeque);

    
    return 0;
}
