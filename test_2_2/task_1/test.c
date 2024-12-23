#define CTEST_MAIN
#define CTEST_SEGFAULT
#include "../../ctest/ctest.h"

#include <stdlib.h>

#include "linkedList.h"

int main(int argc, const char *argv[]) {
    return ctest_main(argc, argv);
}

void assertList(LinkedList *list, int *array, int arraySize) {
    ASSERT_NOT_NULL(list);
    LinkedListNode *node = getFirst(list);
    for (int i = 0; i < arraySize; ++i) {
        ASSERT_NOT_NULL(node);
        ASSERT_EQUAL(getValue(node), array[i]);
        node = getNext(node);
    }
    ASSERT_NULL(node);
}

void assertAddToList(LinkedList *list, int *array, int arraySize) {
    for (int i = 0; i < arraySize; ++i) {
        ASSERT_TRUE(addToList(list, array[i]));
    }
}

LinkedList *createNewList(void) {
    LinkedList *list = NULL;
    ASSERT_TRUE(createList(&list));
    return list;
}

void assertOddRemoving(int *arrayA, int arrayASize, int *arrayB, int arrayBSize) {
    LinkedList *list = createNewList();
    assertAddToList(list, arrayA, arrayASize);
    removeAllOddNodes(list);
    assertList(list, arrayB, arrayBSize);
    disposeList(list);
}

CTEST(linkedListTest, emptyListTest) {
    assertOddRemoving(NULL, 0, NULL, 0);
}

CTEST(linkedListTest, singleElementTest) {
    int array[1] = { 42 };
    assertOddRemoving(
        array, sizeof(array) / sizeof(int),
        array, sizeof(array) / sizeof(int));
}

CTEST(linkedListTest, twoElementsTest) {
    int arrayA[2] = { 42, 96 };
    int arrayB[1] = { 42 };

    assertOddRemoving(
        arrayA, sizeof(arrayA) / sizeof(int),
        arrayB, sizeof(arrayB) / sizeof(int));
}

CTEST(linkedListTest, someElementsTest) {
    int arrayA[9] = { 42, 96, -1122, 53, 623, 734, 23446, 76756456, 87354 };
    int arrayB[5] = { 42,     -1122,     623,      23446,           87354 };

    assertOddRemoving(
        arrayA, sizeof(arrayA) / sizeof(int),
        arrayB, sizeof(arrayB) / sizeof(int));
}
