#include "SinglyLinkedList.hpp"

#include "fixtures/list_test.hpp"
#include "kata_test.hpp"

static_assert(kata::List<kata::SinglyLinkedList<int>, int>, "SinglyLinkedList must satisfy kata::List");

TEST(singly_linked_list) {
    kata::SinglyLinkedList<int> list;
    kata::fixtures::test_list(list);
}
