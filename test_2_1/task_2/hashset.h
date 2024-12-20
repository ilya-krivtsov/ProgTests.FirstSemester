#pragma once

#define HASHSET_SIZE 256

/// @brief Hashset of strings
typedef struct Hashset Hashset;

/// @brief Creates new hashset
/// @param hashset Pointer to store new hashset to
/// @return `true` if created successfully, `false` otherwise (allocation failed)
bool createHashset(Hashset **hashset);

/// @brief Adds string to hashtable
/// @param hashset Hashset to add string to
/// @param string String to add
/// @return `true` if added successfully, `false` otherwise (no space for new entries left)
bool addToHashset(Hashset *hashset, const char *string);

/// @brief Searchs for specified string
/// @param hashset Hashset to search string in
/// @param string String to search
/// @return `true` if found, `false` otherwise
bool containedInHashset(Hashset *hashset, const char *string);

/// @brief Disposes hashtable
/// @param hashset Hashtable to dispose
void disposeHashset(Hashset *hashset);
