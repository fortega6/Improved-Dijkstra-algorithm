#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE

#include "catch.hpp"
#include "heap_priority_queue.hpp"

TEST_CASE( "Heap Priority Queue", "[HeapPriorityQueue<T>]" )
{
    INFO("Hint: testing HeapPriorityQueue<int> main features");

    HeapPriorityQueue<int> h1;
    REQUIRE(h1.isEmpty());

    h1.add(100);
    h1.add(19);
    h1.add(36);

    REQUIRE(!h1.isEmpty());
    REQUIRE(h1.peek() == 19);

    h1.add(17);
    h1.add(3);
    h1.add(25);
    h1.add(1);

    REQUIRE(!h1.isEmpty());
    REQUIRE(h1.peek() == 1);

    h1.remove();
    REQUIRE(h1.peek() == 3);

    h1.remove();
    h1.remove();
    REQUIRE(h1.peek() == 19);

    HeapPriorityQueue<int> h2;
    h2.add(25);
    h2.add(25);
    h2.add(30);

    REQUIRE(!h2.isEmpty());
    REQUIRE(h2.peek() == 25);

    h2.remove();
    REQUIRE(h2.peek() == 25);

    h2 = h1;
    h1.clear();

    REQUIRE(h1.isEmpty());
    REQUIRE(h2.peek() == 19);
}
