#include <catch2/catch_all.hpp>

#include <bicycle/container/intrusive_linked_list.hpp>

namespace bicycle::container::tests {

struct TestNode : public intrusive::ListNode<TestNode> {
};

TEST_CASE("Intrusive list") {
  intrusive::LinkedList<TestNode> list;

  TestNode node_1;
  TestNode node_2;

  list.PushFront(&node_1);

}



}  // namespace bicycle::container::tests