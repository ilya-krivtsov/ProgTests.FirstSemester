#include "linkedList.h"

#include <stdbool.h>
#include <stdlib.h>

typedef struct LinkedList {
    LinkedListNode *first;
    LinkedListNode *last;
} LinkedList;

typedef struct LinkedListNode {
    int value;
    LinkedListNode *next;
} LinkedListNode;

bool createList(LinkedList **list) {
    *list = calloc(1, sizeof(LinkedList));
    return *list != NULL;
}

bool addToList(LinkedList *list, int value) {
    LinkedListNode *node = calloc(1, sizeof(LinkedListNode));
    if (node == NULL) {
        return false;
    }

    node->value = value;

    if (list->first == NULL) {
        list->first = node;
    } else {
        list->last->next = node;
    }
    list->last = node;

    return true;
}

void removeAllOddNodes(LinkedList *list) {
    LinkedListNode *node = list->first;
    while (node != NULL) {
        LinkedListNode *next = node->next;
        if (node->next == NULL) {
            return;
        }

        LinkedListNode *nextNext = next->next;
        free(next);
        node->next = nextNext;
        node = nextNext;
    }
}

LinkedListNode *getFirst(LinkedList *list) {
    return list->first;
}

LinkedListNode *getNext(LinkedListNode *node) {
    return node->next;
}

int getValue(LinkedListNode *node) {
    return node->value;
}

void disposeList(LinkedList *list) {
    LinkedListNode *node = list->first;
    while (node != NULL) {
        LinkedListNode *next = node->next;
        free(node);
        node = next;
    }
    free(list);
}
