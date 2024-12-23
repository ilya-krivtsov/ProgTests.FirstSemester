#include "graphCheck.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define NO_CONNECTION 0
#define CONNECTION 1
#define VISITED_NODE 2

static void copyLine(int **matrix, int nodeCount, int lineFrom, int lineTo) {
    for (int i = 0; i < nodeCount; ++i) {
        if (matrix[lineTo][i] < matrix[lineFrom][i]) {
            matrix[lineTo][i] = matrix[lineFrom][i];
        }
    }
}

static void createAdjacencyLists(int **matrix, int nodeCount) {
    for (int i = 0; i < nodeCount; ++i) {
        matrix[i][i] = VISITED_NODE;
    }

    while (true) {
        bool addedAnyValues = false;

        for (int i = 0; i < nodeCount; ++i) {
            for (int j = 0; j < nodeCount; ++j) {
                if (matrix[i][j] == CONNECTION) {
                    addedAnyValues = true;
                    matrix[i][j] = VISITED_NODE;
                    copyLine(matrix, nodeCount, j, i);
                }
            }
        }

        if (!addedAnyValues) {
            break;
        }
    }
}

bool getAllReachableNodes(FILE *input, int **reachableNodes, int *reachableNodesCount) {
    if (input == NULL) {
        return false;
    }

    int nodeCount = 0;
    if (fscanf(input, "%d", &nodeCount) != 1) {
        return false;
    }

    int **matrix = calloc(nodeCount, sizeof(int *));
    if (matrix == NULL) {
        return false;
    }

    bool failed = false;
    for (int i = 0; i < nodeCount; ++i) {
        matrix[i] = calloc(nodeCount, sizeof(int));
        if (matrix[i] == NULL) {
            failed = true;
            break;
        }

        for (int j = 0; j < nodeCount; ++j) {
            if (fscanf(input, "%d", &matrix[i][j]) != 1 ||
                (matrix[i][j] != NO_CONNECTION && matrix[i][j] != CONNECTION)) {
                failed = true;
            }
        }
    }

    if (failed) {
        for (int i = 0; i < nodeCount; ++i) {
            free(matrix[i]);
        }
        free(matrix);
        return false;
    }

    *reachableNodes = calloc(nodeCount, sizeof(int));
    if (*reachableNodes == NULL) {
        for (int i = 0; i < nodeCount; ++i) {
            free(matrix[i]);
        }
        free(matrix);
        return false;
    }

    createAdjacencyLists(matrix, nodeCount);

    for (int i = 0; i < nodeCount; ++i) {
        int reachedNodesCount = 0;
        for (int j = 0; j < nodeCount; ++j) {
            reachedNodesCount += matrix[i][j] != NO_CONNECTION ? 1 : 0;
        }

        if (reachedNodesCount == nodeCount) {
            (*reachableNodes)[*reachableNodesCount] = i;
            ++*reachableNodesCount;
        }
    }

    for (int i = 0; i < nodeCount; ++i) {
        free(matrix[i]);
    }
    free(matrix);

    return true;
}
