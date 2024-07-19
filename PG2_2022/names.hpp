#pragma once

#include <vector>
#include <string>
#include <random>
#include <ctime>

class RandomNameGenerator {
public:
    static std::string getRandomName() {
        static std::mt19937 rng(static_cast<unsigned int>(std::time(nullptr)));
        static std::uniform_int_distribution<std::mt19937::result_type> dist(0, names.size() - 1);
        return names[dist(rng)];
    }

private:
    static const std::vector<std::string> names;
};
