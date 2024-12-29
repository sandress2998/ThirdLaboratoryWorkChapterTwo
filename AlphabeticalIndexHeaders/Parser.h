#pragma once

#include <string>
#include "MutableSegmentedDeque.h"
#include "HashTable.h"
#include "Word.h"

void parse(std::string str, HashTable<Word>& wordsHashTable, MutableSegmentedDeque<SharedPtr<Word>>& wordsDeque);