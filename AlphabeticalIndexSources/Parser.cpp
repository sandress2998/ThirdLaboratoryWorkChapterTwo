#include <string>
#include "DynamicArray.h"
#include "MutableSegmentedDeque.h"
#include "HashTable.h"
#include "SharedPtr.h"
#include "D:\VSCodeProjects\ThirdLaboratoryWorkChapterTwo\HashFunction.h"
#include "Book.h"
#include "D:\VSCodeProjects\ThirdLaboratoryWorkChapterTwo\AlphabeticalIndexHeaders\Word.h"

bool checkSymbolValid(char symbol);
void analyzeWord(std::string phrase, HashTable<Word>& wordsHashTable, MutableSegmentedDeque<SharedPtr<Word>>& wordsDeque);

//void parse(std::string str, HashTable<Word>& wordsHashTable, MutableSegmentedDeque<SharedPtr<Word>>& wordsDeque) {
Book parse(const std::string& str, int hashTableLength) {
    SharedPtr<MutableSegmentedDeque<SharedPtr<Word>>> wordsDeque = makeShared<MutableSegmentedDeque<SharedPtr<Word>>>(); 
    SharedPtr<HashTable<Word>> wordsHashTable = makeShared<HashTable<Word>>(hashTableLength, &djb2_hash);

    std::string phrase = "";
    int length = str.size();
    for (int i = 0; i < length; ++i) {
        if (checkSymbolValid(str[i])) {
            phrase += str[i];
            
            if (i == length - 1) {
                analyzeWord(phrase, *wordsHashTable, *wordsDeque);
            }
            
        } else if (phrase == "") {
            continue;
        } else {
            analyzeWord(phrase, *wordsHashTable, *wordsDeque);
            phrase = "";
        }
    }

    return Book(wordsHashTable, wordsDeque);
}

bool checkSymbolValid(char symbol) {
    if (((int) symbol >= 65 && (int) symbol <= 90) || ((int) symbol >= 97 && (int) symbol <= 122)) {
        return true;
    }
    return false;
}

void analyzeWord(std::string phrase, HashTable<Word>& wordsHashTable, MutableSegmentedDeque<SharedPtr<Word>>& wordsDeque) {
    SharedPtr<Word> word;
    try {
        word = wordsHashTable.find(phrase); // пытаемся найти уже существующее слово
        //std::cout << "The word founded...\n";
    } catch (const std::invalid_argument&) { // ловим исключение, если не нашли слово
        wordsHashTable.append(phrase); // создаем новое слово
        word = wordsHashTable.find(phrase);
    }  
    //std::cout << "After try-catch...\n";
    if (wordsDeque.getLength() != 0) { // проверка на первое слово в тексте
        //std::cout << "Before setLine...\n";
        word->setLine(wordsDeque.getLast()->getLastLine()->addWord(phrase)); // мы устанавливаем для слова строку, на которой 
        // оно будет (или не будет) помещено. В параметры передаем указатель на строку у последнего уже 
        // рассмотренного слова.
        //std::cout << "After setLine...\n";
    } else {
        word->setLine(Line::createFirstLine()->addWord(phrase));
    }
    /*
    SharedPtr<DynamicArray<SharedPtr<Line>>> lineArray = word->getLineArray();
    for (int i = 0; i < lineArray->getSize(); ++i) {
        std::cout << word->getValue() << ": " << lineArray->get(i)->getPageAddress() << " with index " << lineArray->get(i)->getIndex() << "\n";
    }
    */
    wordsDeque.append(word);
    // выходит, проблема в том, что мое слово просто не анализируется... А почему так происходит?
    //std::cout << wordsDeque.getLength() << "\n";
}


/*
void parse(std::string str, HashTable<Word>& wordsHashTable, MutableSegmentedDeque<Word*>& wordsDeque) {
    std::string phrase = "";
    for (int i = 0; i < str.size(); ++i) {
        char symbol = str[i];
        if (((int) symbol >= 65 && (int) symbol <= 90) || ((int) symbol >= 97 && (int) symbol <= 122) && (i!= str.size() - 1)) { // проверяем, хороший ли символ
            phrase += symbol;
        } else if (phrase == "") { // если нехороший символ, а слово (phrase) не набралось, чтобы быть словом, то идем дальше
            continue;
        } else { // если символ нехороший, а слово набралось, то добавляем новое слово
            /*if ((i == str.size() - 1) && ((int) symbol >= 65 && (int) symbol <= 90) || ((int) symbol >= 97 && (int) symbol <= 122)) {
                phrase += symbol;
            }
            Word* word;
            try {
                word = &(wordsHashTable.find(phrase)); // пытаемся найти уже существующее слово
            } catch (const std::invalid_argument&) { // ловим исключение, если не нашли слово
                wordsHashTable.append(phrase); // создаем новое слово
                word = &(wordsHashTable.find(phrase));
            }  

            if (wordsDeque.getLength() != 0) { // проверка на первое слово в тексте
                word->setLine(wordsDeque.getLast()->getLastLine()->addWord(phrase)); // мы устанавливаем для слова строку, на которой 
                // оно будет (или не будет) помещено. В параметры передаем указатель на строку у последнего уже 
                // рассмотренного слова.
            } else {
                word->setLine((new Line())->addWord(phrase)); 
            }
            wordsDeque.append(word); // добавляем новое слово в любом случае
            phrase = "";
        }
    }
}
*/