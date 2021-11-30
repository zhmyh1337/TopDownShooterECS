#include "random.h"

std::mt19937 Random::s_rng(std::random_device{}());

std::mt19937& Random::Get()
{
    return s_rng;
}
