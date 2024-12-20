#pragma once

#include <stdbool.h>
#include <stdio.h>

/// @brief Reads numbers seqentially from `input`, rearranges them so all numbers
/// less than `minRange` will come first, then numbers in range [`minRange`, `maxRange`],
/// then numbers greater than maxRange; internal order is preserved
/// @param input Input file
/// @param output Output file
/// @param minRange Min range
/// @param maxRange Max range
/// @return `true` if rearranged successfully, `false` otherwise
/// (io error, allocation error, minRange is greater than maxRange)
bool rearrangeNumbers(FILE *input, FILE *output, int minRange, int maxRange);
