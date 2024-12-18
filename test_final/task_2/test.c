#define CTEST_MAIN
#define CTEST_SEGFAULT
#include "../../ctest/ctest.h"

#include <stdlib.h>

#include "stackQueue.h"

int main(int argc, const char *argv[]) {
    return ctest_main(argc, argv);
}

StackQueue *createNewQueue(void) {
    StackQueue *queue = NULL;
    ASSERT_TRUE(createQueue(&queue));
    return queue;
}

void assertEnqueue(StackQueue *queue, int value) {
    ASSERT_TRUE(enqueue(queue, value));
}

void assertDequeue(StackQueue *queue, int expectedValue) {
    int realValue = 0;
    ASSERT_TRUE(dequeue(queue, &realValue));
    ASSERT_EQUAL(realValue, expectedValue);
}

CTEST(stackQueueTests, emptyQueue) {
    StackQueue *queue = createNewQueue();
    ASSERT_TRUE(isEmpty(queue));
    disposeQueue(queue);
}

CTEST(stackQueueTests, singleEnqueue) {
    StackQueue *queue = createNewQueue();
    ASSERT_TRUE(isEmpty(queue));
    assertEnqueue(queue, 234);
    ASSERT_FALSE(isEmpty(queue));
    assertDequeue(queue, 234);
    ASSERT_TRUE(isEmpty(queue));

    disposeQueue(queue);
}

CTEST(stackQueueTests, multipleEnqueuesA) {
    StackQueue *queue = createNewQueue();
    ASSERT_TRUE(isEmpty(queue));
    assertEnqueue(queue, 123);
    assertEnqueue(queue, 456);
    assertEnqueue(queue, 789);
    assertDequeue(queue, 123);
    assertDequeue(queue, 456);
    assertDequeue(queue, 789);
    ASSERT_TRUE(isEmpty(queue));

    disposeQueue(queue);
}

CTEST(stackQueueTests, multipleEnqueuesB) {
    StackQueue *queue = createNewQueue();
    ASSERT_TRUE(isEmpty(queue));

    for (int i = 0; i < 65536; ++i) {
        assertEnqueue(queue, i * 71 + 13);
        ASSERT_FALSE(isEmpty(queue));
    }

    for (int i = 0; i < 65536; ++i) {
        ASSERT_FALSE(isEmpty(queue));
        assertDequeue(queue, i * 71 + 13);
    }

    ASSERT_TRUE(isEmpty(queue));
    disposeQueue(queue);
}
