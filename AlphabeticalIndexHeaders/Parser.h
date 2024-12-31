#pragma once

#include <string>
#include "MutableSegmentedDeque.h"
#include "HashTable.h"
#include "Word.h"
#include "Book.h"

//void parse(std::string str, HashTable<Word>& wordsHashTable, MutableSegmentedDeque<SharedPtr<Word>>& wordsDeque);
Book parse(const std::string& str, int hashTableLength);