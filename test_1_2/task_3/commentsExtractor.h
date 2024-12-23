#pragma once

#include <stdbool.h>
#include <stdio.h>

/// @brief Reads from file all comments starting with `;` and ending with '\n'
/// @param input File to read comments from
/// @param output File to write comments to
/// @return `true` if extracted comments successfully, `false` otherwise (some of files were `NULL`)
bool extractSemicolonComments(FILE *input, FILE *output);
