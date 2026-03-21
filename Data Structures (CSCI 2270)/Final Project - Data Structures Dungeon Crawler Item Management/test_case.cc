#include <gtest/gtest.h>
#include "PriorityQueue.hpp"
#include "enemy_graph.hpp"
#include "hash.hpp"
#include <string>
#include <vector>
using namespace std;

class CrawlTest : public ::testing::Test {
protected:
    EnemyGraph* graph1;
    
    void SetUp() override {
        // This runs before each test to instantiate 

            graph1 = new EnemyGraph();
        
    }
    
    void TearDown() override {
        // This runs after each test
        delete graph1;
    }
};


TEST_F(CrawlTest, searchgraphHappyPath) {

        //Given a graph with a vertex
        graph1->addVertex("fong");

        // When we search for that vertex
        Vertex* result = graph1->searchVertex("fong");

        //Then we expect the vertex return to Not equal a nullptr (EXPECT_NE means expect not equal)
        EXPECT_NE(result, nullptr);
        EXPECT_EQ(result->id, "fong");

}

TEST_F(CrawlTest, searchGraphErrorPath) {
    //Given an empty graph

    //When we try to search for a vertex
    //We expect an invalid argument error to be thrown
    EXPECT_THROW(graph1->searchVertex("doesnt exist"), std::invalid_argument);


}
//************************************************************************** 
TEST_F(CrawlTest, searchgraphEdgeCaseInvalidEdge){
    graph1->addVertex("start");
    graph1->addVertex("end");

    Vertex* startVertex = graph1->searchVertex("start");
    ASSERT_NE(startVertex, nullptr);
    EXPECT_EQ(startVertex->adjacent.size(), 0u);

    graph1->addEdge("start", "ghostRoom", "Scary Enemy");

    EXPECT_EQ(startVertex->adjacent.size(), 0u);
}




//  ********   ******* PRIORITY QUEUE TESTS   ***** ****** *******
//When testing priority Queue you may wish to update line 63 to specify the capacity of the queue in the constructor

class PriorityTest : public ::testing::Test {
protected:

    PriorityQ* priority1;
    
    void SetUp() override {
        // This runs before each test to instantiate 
            priority1 = new PriorityQ();
        
    }
    
    void TearDown() override {
        // This runs after each test
        delete priority1;
    }
};


TEST_F(PriorityTest, PriorityQueueInsertHappyPath) {

    ItemInfo item;
    item.characterName = "Tester";
    item.itemName = "Sword of Testing";
    item.damage = 1000;
    item.comment = "Test Blade";

    //when: we insert a valid item
    priority1->insertElement(item);

    //then: item should be retrievable via peek
    ItemInfo* top = priority1->peek();
    ASSERT_NE(top,nullptr);
    EXPECT_EQ(top->characterName, "Tester");
    EXPECT_EQ(top->itemName, "Sword of Testing");
    EXPECT_EQ(top->damage, 1000);
    EXPECT_EQ(top->comment, "Test Blade");


}

// TO DO add  more tests of your priority queue here
TEST_F(PriorityTest, PrirorityQueuePeekEmpty){
    //given an empty pq
    //when peek is called
    ItemInfo* top = priority1->peek();
    //expect nullptr result
    EXPECT_EQ(top,nullptr);
}

TEST_F(PriorityTest, PriorityQueuePopEmpty){
    //given an empty pq
    //when pop is called
    //then queue should stay empty and not crash
    priority1->pop();

    ItemInfo* top = priority1->peek();
    EXPECT_EQ(top, nullptr);
}
