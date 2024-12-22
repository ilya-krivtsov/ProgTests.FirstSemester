#pragma once

/// @brief Converts number formatted in binary to string, representing same number as decimal 
/// @param binaryString String to convert
/// @return New allocated string,
/// `NULL` if specified string was `NULL`, in incorrect format, too long (more than 32 digits) or allocation failed
char *binaryToDecimal(const char *binaryString);
