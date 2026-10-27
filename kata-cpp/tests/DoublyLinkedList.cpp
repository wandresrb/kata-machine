#include "DoublyLinkedList.hpp"

#include "fixtures/list_test.hpp"
#include "kata_test.hpp"

static_assert(kata::List<kata::DoublyLinkedList<int>, int>, "DoublyLinkedList must satisfy kata::List");

TEST(doubly_linked_list) {
    kata::DoublyLinkedList<int> list;
    kata::fixtures::test_list(list);
}
