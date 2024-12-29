#include <string>
#include "DynamicArray.h"
#include "MutableSegmentedDeque.h"
#include "HashTable.h"
#include "D:\VSCodeProjects\ThirdLaboratoryWorkChapterTwo\AlphabeticalIndexHeaders\Word.h"

bool checkSymbolValid(char symbol);

void parse(std::string str, HashTable<Word>& wordsHashTable, MutableSegmentedDeque<Word*>& wordsDeque) {
    std::string phrase = "";
    int length = str.size();
    for (int i = 0; i < length; ++i) {
        if (checkSymbolValid(str[i])) {
            phrase += str[i];
            
            if (i == length - 1) {
                analyzeWord(phrase, wordsHashTable, wordsDeque);
            }
            
        } else if (phrase == "") {
            continue;
        } else {
            analyzeWord(phrase, wordsHashTable, wordsDeque);
            phrase = "";
        }
    }
}

bool checkSymbolValid(char symbol) {
    if (((int) symbol >= 65 && (int) symbol <= 90) || ((int) symbol >= 97 && (int) symbol <= 122)) {
        return true;
    }
    return false;
}

void analyzeWord(std::string phrase, HashTable<Word>& wordsHashTable, MutableSegmentedDeque<Word*>& wordsDeque) {
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
    wordsDeque.append(word);
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