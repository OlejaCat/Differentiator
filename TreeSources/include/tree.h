#ifndef DESICION_TREE_H
#define DESICION_TREE_H

#include <stdlib.h>
#include <stdbool.h>

#include "arithmetic_tree_structure.h"

typedef AriphmeticNodeData tree_node_type;

typedef struct Tree Tree;
typedef struct TreeNode TreeNode;

const int EMPTY_NODE = -1;

#if defined(DUMP) || defined(LOGGER)
    #define DUMP_PARAMETERS const char* file_name, int line_number, const char* function
#else
    #define DUMP_PARAMETERS
#endif

#ifdef LOGGER
    #define LOGGER_PARAMETERS , const char* file_name, int line_number, const char* function
#else
    #define LOGGER_PARAMETERS
#endif


Tree* treeCtor_(DUMP_PARAMETERS);
void treeDtor_(Tree* tree LOGGER_PARAMETERS);
size_t treeNodesQuantity_(Tree* tree LOGGER_PARAMETERS);
bool treeIsNodeEnd_(Tree* tree, int node_index LOGGER_PARAMETERS);
tree_node_type treeGetNodeData_(Tree* tree, int node_index LOGGER_PARAMETERS);
int treeGetParentNode_(Tree* tree, int node_index LOGGER_PARAMETERS);
int treeGetLeftNode_(Tree* tree, int node_index LOGGER_PARAMETERS);
int treeGetRightNode_(Tree* tree, int node_index LOGGER_PARAMETERS);
int treeCreateNewNode_(Tree* tree, tree_node_type data LOGGER_PARAMETERS);
int treeInsertOnLeft_(Tree* tree, int node_parent_index, int node_index LOGGER_PARAMETERS);
int treeInsertOnRight_(Tree* tree, int node_parent_index, int node_index LOGGER_PARAMETERS);


#if defined(DUMP) || defined(LOGGER)
    #define treeCtor() treeCtor_(__FILE__, __LINE__, __PRETTY_FUNCTION__)
    #define treeDtor(tree_) treeDtor_(tree_, __FILE__, __LINE__, __PRETTY_FUNCTION__)
#else
    #define treeCtor() treeCtor_()
    #define treeDtor() treeDtor_()
#endif

#ifdef LOGGER
    #define treeNodesQuantity(tree_) \
        treeNodesQuantity_(tree_, __FILE__, __LINE__, __PRETTY_FUNCTION__)

    #define treeIsNodeEnd(tree_, node_index_) \
        treeIsNodeEnd_(tree_, node_index_, __FILE__, __LINE__, __PRETTY_FUNCTION__)

    #define treeGetNodeData(tree_, node_index_) \
        treeGetNodeData_(tree_, node_index_, __FILE__, __LINE__, __PRETTY_FUNCTION__)

    #define treeGetParentNode(tree_, node_index_) \
        treeGetParentNode_(tree_, node_index_, __FILE__, __LINE__, __PRETTY_FUNCTION__)

    #define treeGetLeftNode(tree_, node_index_) \
        treeGetLeftNode_(tree_, node_index_, __FILE__, __LINE__, __PRETTY_FUNCTION__)

    #define treeGetRightNode(tree_, node_index_) \
        treeGetRightNode_(tree_, node_index_, __FILE__, __LINE__, __PRETTY_FUNCTION__)

    #define treeCreateNewNode(tree_, data_) \
        treeCreateNewNode_(tree_, data_, __FILE__, __LINE__, __PRETTY_FUNCTION__)

    #define treeInsertOnLeft(tree_, node_parent_index_, node_index_) \
        treeInsertOnLeft_(tree_, node_parent_index_, node_index_, __FILE__, __LINE__, __PRETTY_FUNCTION__)

    #define treeInsertOnRight(tree_, node_parent_index_, node_index_) \
        treeInsertOnRight_(tree_, node_parent_index_, node_index_, __FILE__, __LINE__, __PRETTY_FUNCTION__)
#else
    #define treeNodesQuantity(tree_) \
        treeNodesQuantity_(tree_)

    #define treeIsNodeEnd(tree_, node_index_) \
        treeIsNodeEnd_(tree_, node_index_)

    #define treeGetNodeData(tree_, node_index_) \
        treeGetNodeData_(tree_, node_index_)

    #define treeGetParentNode(tree_, node_index_) \
        treeGetParentNode_(tree_, node_index_)

    #define treeGetLeftNode(tree_, node_index_) \
        treeGetLeftNode_(tree_, node_index_)

    #define treeGetRightNode(tree_, node_index_) \
        treeGetRightNode_(tree_, node_index_)

    #define treeInsertOnLeft(tree_, node_index_, data_) \
        treeInsertOnLeft_(tree_, node_index_, data_)

    #define treeInsertOnRight(tree_, node_index_, data_) \
        treeInsertOnRight_(tree_, node_index_, data_)
#endif

#endif // DESICION_TREE_H