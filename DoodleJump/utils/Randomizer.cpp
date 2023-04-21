#pragma once
#include "../utils.h"

std::mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());
int Rand(int a, int b) { return std::uniform_int_distribution<int>(a, b)(rng); }
int Rand(int a, int b, int hash) { srand(hash); return rand() % (b - a + 1) + a; }