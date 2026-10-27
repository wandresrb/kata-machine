#include "ArrayList.hpp"

#include "fixtures/list_test.hpp"
#include "kata_test.hpp"

static_assert(kata::List<kata::ArrayList<int>, int>, "ArrayList must satisfy kata::List");

TEST(array_list) {
    kata::ArrayList<int> list(3);
    kata::fixtures::test_list(list);
}
