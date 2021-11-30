#pragma once

#include <random>

class Random
{
public:
    static std::mt19937& Get();

private:
    static std::mt19937 s_rng;
};
