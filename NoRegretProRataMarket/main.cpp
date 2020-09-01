#include <iostream>

#include "Adversary.h"

int main() {
    Adversary adversary(10);
    
    for (unsigned int roundNumber = 1; roundNumber <= 10000; ++roundNumber) {
        adversary.playRound();
    }
}
