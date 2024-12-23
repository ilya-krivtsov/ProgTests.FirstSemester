#pragma once

#include <stdbool.h>
#include <stdio.h>

/// @brief Gets all nodes that can reach any other node in graph
/// @param input File to read from in format
///
/// `nodeCount`
///
/// `Adjacency matrix of a directed graph, represented by
/// nodeCount x nodeCount ones or zeroes separated by space characters or line break`
/// @param reachableNodes Pointer to store count of everywhere-reaching nodes
/// @param reachableNodesCount Pointer to store array of everywhere-reaching nodes
/// @return `true` if got all nodes correctly, `false` otherwise
/// (allocation failed, io error or incorrect file format)
bool getAllReachableNodes(FILE *input, int **reachableNodes, int *reachableNodesCount);
