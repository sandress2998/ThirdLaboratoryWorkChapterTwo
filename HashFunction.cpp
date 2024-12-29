#include "HashFunction.h"

int djb2_hash(const std::string& str, int hashTableLength) {
    int hash = 5381;
    for (char c : str) {
        hash = ((hash << 5) + hash) + static_cast<unsigned char>(c);
    }
    return std::abs(hash) % hashTableLength;
}
