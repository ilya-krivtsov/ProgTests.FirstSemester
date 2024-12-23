#pragma once

#include <stdbool.h>

/// @brief Linked list that stores int values 
typedef struct LinkedList LinkedList;

/// @brief Node of a linked list
typedef struct LinkedListNode LinkedListNode;

/// @brief Creates new linked list
/// @param list Pointer to store new list to
/// @return `true` if created successfully, `false` otherwise (allocation failed)
bool createList(LinkedList **list);

/// @brief Adds value to list
/// @param list List to add value to
/// @param value Value to add to list
/// @return `true` if added successfully, `false` otherwise (allocation failed)
bool addToList(LinkedList *list, int value);

/// @brief Removes all nodes placed at odd indicies
/// @param list List to remove nodes from
void removeAllOddNodes(LinkedList *list);

/// @brief Gets first node of a list
/// @param list List to get first node from
/// @return Fist node of specified list
LinkedListNode *getFirst(LinkedList *list);

/// @brief Gets node following specified node
/// @param node Node to get next one from
/// @return Node following specified node 
LinkedListNode *getNext(LinkedListNode *node);

/// @brief Gets value of a node
/// @param node Node to get value from
/// @return Value of specified node
int getValue(LinkedListNode *node);

/// @brief Disposes list
/// @param list List to dispose
void disposeList(LinkedList *list);
