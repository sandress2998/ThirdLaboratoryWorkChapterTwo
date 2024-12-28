#include <string>
#include "DynamicArray.h"
#include "MutableSegmentedDeque.h"
#include "HashTable.h"
#include "D:\VSCodeProjects\ThirdLaboratoryWorkChapterTwo\AlphabeticalIndexHeaders\Word.h"

#include <iostream>

void parse(std::string str, HashTable<Word>& wordsHashTable, MutableSegmentedDeque<Word*>& wordsDeque) {
    std::string phrase = "";
    for (int i = 0; i < str.size(); ++i) {
        char symbol = str[i];
        if (((int) symbol >= 65 && (int) symbol <= 90) || ((int) symbol >= 97 && (int) symbol <= 122)) { // проверяем, хороший ли символ
            phrase += symbol;
        } else if (phrase == "") { // если нехороший символ, а слово (phrase) не набралось, чтобы быть словом, то идем дальше
            continue;
        } else { // если символ нехороший, а слово набралось, то добавляем новое слово
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
                std::cout << "phrase = " << phrase << "\n";
                Line* someLine = (new Line())->addWord(phrase);
                std::cout << "some line lenght = " << someLine->getSize();
                word->setLine(someLine); 
            }
            std::cout << "Мы близки\n";
            wordsDeque.append(word); // добавляем новое слово в любом случае
            phrase = "";
        }
    }
}