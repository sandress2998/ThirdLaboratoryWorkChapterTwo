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
    std::string str = "___Are._ Pochto gonna do it ddd ffffff rrerere hghffg dfdfdf ttrt rd fdfd ggggd dfd";
    str += "sdsd dsd popolllpo xxxolmap kpor sdsds abkklslsl assbklls mmklllsds qwew edsds d";
    str += "dfdf fdfdf ereurueuru fghfgh hfgherh e fhdfh hehrh ehh hghfhgheh rherh eh hehdfh dh hherhe";
    str += "ff dfh dfffd rrrr ppdofid dfdfiinml di kkgfkkgji jf ddlfl ldkjjd jj ieirie idfjjd jdf jd jjdjg";
    str += "dfdf fdfdf ereurueuru fghfgh hfgherh e fhdfh hehrh ehh hghfhgheh rherh eh hehdfh dh hherhe";
    str += "ff dfh dfffd rrrr ppdofid dfdfiinml di kkgfkkgji jf ddlfl ldkjjd jj ieirie idfjjd jdf jd jjdjg";
    str += "dfdf fdfdf ereurueuru fghfgh hfgherh e fhdfh hehrh ehh hghfhgheh rherh eh hehdfh dh hherhe";
    str += "ff dfh dfffd rrrr ppdofid dfdfiinml di kkgfkkgji jf ddlfl ldkjjd jj ieirie idfjjd jdf jd jjdjg";
    str += "dfdf fdfdf ereurueuru fghfgh hfgherh e fhdfh hehrh ehh hghfhgheh rherh eh hehdfh dh hherhe";
    str += "ff dfh dfffd rrrr ppdofid dfdfiinml di kkgfkkgji jf ddlfl ldkjjd jj ieirie idfjjd jdf jd jjdjg";
    //std::string str = "___Are._ Pochto gonna do it well i don no what is goggi папа пtrte fg fgf dre er gfg gfggg ererr dfd on Are??? fdfd rere wewew rer ewrw ewrw reeeeeee weewv gggg rrrrt ttttttt rrrrr 5frtrt""
    parse(str, hashTable, wordsDeque);

    for (int i = 0; i < (wordsDeque).getLength(); ++i) {
        //SharedPtr<DynamicArray<int>> numbers = (wordsDeque)[i]->getLinesNumber();
        
        SharedPtr<DynamicArray<int>> numbers = (wordsDeque)[i]->getPagesNumber();
        SharedPtr<DynamicArray<Page*>> pages = (wordsDeque)[i]->getPagesAddress();

        for (int j = 0; j < numbers->getSize(); ++j) {
            std::cout << (wordsDeque)[i]->getValue() << ": " << pages->get(j) << " " << numbers->get(j) << "\n";
        }
       
    }
    return 0;
}