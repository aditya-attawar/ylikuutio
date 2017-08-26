#include "gtest/gtest.h"
#include "code/ylikuutio/graph/node_struct.hpp"

TEST(NodeStruct_must_be_initialized_appropriately, NodeStruct)
{
    NodeStruct test_node_struct;
    ASSERT_EQ(test_node_struct.parent_pointer, nullptr);
    ASSERT_EQ(test_node_struct.neighbor_nodeIDs.size(), 0);
}