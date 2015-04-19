#include <iostream>
#include <cmath>
#include <array>
#include <vector>
#include <algorithm>

bool BruteForceParity(uint64_t input) {
  bool result = false;
  while (input) {
    result ^= input & 1;
    input >>= 1;
  }
  return result;
}

bool NeatTrickParity(uint64_t input) {
  bool result = false;
  while (input) {
    result ^= 1;
    input &= (input - 1);
  }
  return result;
}

class CachedParity {
private:
  std::array<short, 65536> bitDict;
  std::vector<uint16_t> chunks;

  bool GetChunkParity(uint16_t chunk) {
    // Calculate it lazily or look it up.
    if (bitDict[chunk] == -1) {
      bool chunkResult = false;
      while (chunk) {
        chunkResult ^= 1;
        chunk &= (chunk - 1);
      }
      bitDict[chunk] = chunkResult;
      return chunkResult;
    } else {
      return bitDict[chunk];
    }
  }

public:
  CachedParity(uint64_t input) {
    bitDict.fill(-1);
    for (int i = 0; i < 4; ++i) {
      chunks.push_back(input & 0xff);
      input >>= 16;
    }
    std::reverse(chunks.begin(), chunks.end());
  }

  bool Parity() {
    auto result = false;
    for (const auto chunk : chunks) {
      result ^= GetChunkParity(chunk);
    }
    return result;
  }
};

bool AssociativeParity(uint64_t input) {
  input ^= input >> 32;
  input ^= input >> 16;
  input ^= input >> 8;
  input ^= input >> 4;
  input ^= input >> 2;
  input ^= input >> 1;
  return input & 1;
}

int main() {
  std::cout << std::boolalpha << CachedParity(0).Parity() << std::endl;
  std::cout << std::boolalpha << CachedParity(1).Parity() << std::endl;
  std::cout << std::boolalpha << CachedParity(2).Parity() << std::endl;
  std::cout << std::boolalpha << CachedParity(3).Parity() << std::endl;
  std::cout << std::boolalpha << CachedParity(4).Parity() << std::endl;
  std::cout << std::boolalpha << CachedParity(5).Parity() << std::endl;
  std::cout << std::boolalpha << CachedParity(6).Parity() << std::endl;
  std::cout << std::boolalpha << CachedParity(7).Parity() << std::endl;
  std::cout << std::boolalpha << CachedParity(8).Parity() << std::endl;
  std::cout << std::boolalpha << CachedParity(9).Parity() << std::endl;
  std::cout << std::boolalpha << CachedParity(10).Parity() << std::endl;
  std::cout << std::boolalpha << CachedParity(20).Parity() << std::endl;
  std::cout << std::boolalpha << CachedParity(30).Parity() << std::endl;
  std::cout << std::boolalpha << CachedParity('a').Parity() << std::endl;
  std::cout << std::boolalpha << CachedParity('A').Parity() << std::endl;
  std::cout << std::boolalpha << CachedParity(97).Parity() << std::endl;
  std::cout << std::boolalpha << CachedParity(65).Parity() << std::endl;
  std::cout << "###############################################################"
               "#################" << std::endl;
  std::cout << std::boolalpha << AssociativeParity(0) << std::endl;
  std::cout << std::boolalpha << AssociativeParity(1) << std::endl;
  std::cout << std::boolalpha << AssociativeParity(2) << std::endl;
  std::cout << std::boolalpha << AssociativeParity(3) << std::endl;
  std::cout << std::boolalpha << AssociativeParity(4) << std::endl;
  return 0;
}
