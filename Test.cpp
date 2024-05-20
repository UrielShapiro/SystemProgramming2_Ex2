#include "doctest.h"
#include "Algorithms.hpp"
#include "Graph.hpp"
#include <time.h>
#include <vector>
#include <iostream>

#define NUM_OF_TESTS 20

std::vector<std::vector<int>> RandomGraph(size_t n)
{
    std::vector<std::vector<int>> graph(n, std::vector<int>(n, 0));
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            if (i != j)
            {
                graph[i][j] = (rand() % 100) - 50;
            }
        }
    }
    return graph;
}

TEST_CASE("Test graph addition")
{
    ariel::Graph g1;
    std::vector<std::vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    std::vector<std::vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph);
    ariel::Graph g3 = g1 + g2;
    std::vector<std::vector<int>> expectedGraph = {
        {0, 2, 1},
        {2, 0, 3},
        {1, 3, 0}};
    CHECK(g3.printGraph() == "[0, 2, 1]\n[2, 0, 3]\n[1, 3, 0]");

    ariel::Graph g4 = g2 + g1;
    CHECK(g4.printGraph() == "[0, 2, 1]\n[2, 0, 3]\n[1, 3, 0]");

    srand(time(NULL));
    for (size_t i = 0; i < NUM_OF_TESTS; i++)
    {
        size_t n = (size_t)(rand() % 100) + 5;
        ariel::Graph g5;
        std::vector<std::vector<int>> graph = RandomGraph(n);
        g5.loadGraph(graph);
        ariel::Graph g6 = g5 + g5;
        for (size_t i = 0; i < n; i++)
        {
            for (size_t j = 0; j < n; j++)
            {
                CHECK(g6.get_edge(i, j) == 2 * graph[i][j]);
            }
        }
    }

    for (size_t i = 0; i < NUM_OF_TESTS; i++)
    {
        size_t n = (size_t)(rand() % 100) + 5;
        ariel::Graph g1;
        std::vector<std::vector<int>> graph1 = RandomGraph(n);
        g1.loadGraph(graph1);
        ariel::Graph g2;
        std::vector<std::vector<int>> graph2 = RandomGraph(n);
        g2.loadGraph(graph2);
        ariel::Graph g3 = g1 + g2;
        for (size_t i = 0; i < n; i++)
        {
            for (size_t j = 0; j < n; j++)
            {
                CHECK(g3.get_edge(i, j) == graph1[i][j] + graph2[i][j]);
            }
        }
    }
}

TEST_CASE("Test Graph subtraction")
{

    ariel::Graph g1;
    std::vector<std::vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    std::vector<std::vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph);
    ariel::Graph g3 = g1 - g2;
    CHECK(g3.printGraph() == "[0, 0, -1]\n[0, 0, -1]\n[-1, -1, 0]");

    ariel::Graph g4 = g2 - g1;
    CHECK(g4.printGraph() == "[0, 0, 1]\n[0, 0, 1]\n[1, 1, 0]");


    srand(time(NULL));
    for (size_t i = 0; i < NUM_OF_TESTS; i++)
    {
        size_t n = (size_t)(rand() % 100) + 5;
        ariel::Graph g1;
        std::vector<std::vector<int>> graph1 = RandomGraph(n);
        g1.loadGraph(graph1);
        ariel::Graph g2;
        std::vector<std::vector<int>> graph2 = RandomGraph(n);
        g2.loadGraph(graph2);
        ariel::Graph g3 = g1 - g2;
        for (size_t i = 0; i < n; i++)
        {
            for (size_t j = 0; j < n; j++)
            {
                CHECK(g3.get_edge(i, j) == graph1[i][j] - graph2[i][j]);
            }
        }
    }
}


TEST_CASE("Test graph multiplication")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph);
    ariel::Graph g4 = g1 * g2;
    vector<vector<int>> expectedGraph = {
        {0, 0, 2},
        {1, 0, 1},
        {1, 0, 0}};
    CHECK(g4.printGraph() == "[0, 0, 2]\n[1, 0, 1]\n[1, 0, 0]");
}

TEST_CASE("Invalid operations")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1, 1},
        {1, 0, 2, 1},
        {1, 2, 0, 1}};
    // g2.loadGraph(weightedGraph);
    ariel::Graph g5;
    vector<vector<int>> graph2 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    g5.loadGraph(graph2);
    CHECK_THROWS(g5 * g1);
    // CHECK_THROWS(g1 * g2);

    // Addition of two graphs with different dimensions
    ariel::Graph g6;
    vector<vector<int>> graph3 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    g6.loadGraph(graph3);
    CHECK_THROWS(g1 + g6);
}