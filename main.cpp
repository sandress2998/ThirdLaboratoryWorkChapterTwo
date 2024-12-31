#include <iostream>
#include <string>
#include "DataStructures/HashTable.h"
#include "HashFunction.h"
#include "AlphabeticalIndexHeaders/Word.h"
#include "AlphabeticalIndexHeaders/Parser.h"
#include "AlphabeticalIndexHeaders/Line.h"

int main() {
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
    Book book = parse(str, 10);

    for (int i = 0; i < book.getWordsQuantity(); ++i) {
        SharedPtr<DynamicArray<int>> numbers = book.getPageNumbers(book.getWord(i)->getValue());
        for (int j = 0; j < numbers->getSize(); ++j) {
            std::cout << book.getWord(i)->getValue() << ": " << numbers->get(j) << "\n";
        }
    }
    return 0;
}