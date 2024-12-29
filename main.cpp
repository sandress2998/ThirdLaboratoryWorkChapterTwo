#include <iostream>
#include <string>
#include "DataStructures/HashTable.h"
#include "HashFunction.h"
#include "AlphabeticalIndexHeaders/Word.h"
#include "Parser.h"

#include "AlphabeticalIndexHeaders/Line.h"
void parse(std::string str, HashTable<Word>& wordsHashTable, MutableSegmentedDeque<SharedPtr<Word>>& wordsDeque);
int main() {
    MutableSegmentedDeque<SharedPtr<Word>> wordsDeque(10);
    HashTable<Word> hashTable(10, &djb2_hash);
    std::string str = "___Are._ Pochto gonna do it well i  don no what is goggiiind on???";
    parse(str, hashTable, wordsDeque);

    for (int i = 0; i < (wordsDeque).getLength(); ++i) {
        std::cout << (wordsDeque)[i]->getValue() << " ";
    }
    return 0;
}