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
                srand(time(NULL));
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

    ariel::Graph g5;
    ariel::Graph g6;
    CHECK_THROWS(g5 = g6 + g6);

    std::vector<std::vector<int>> graph2 = {
        {0, 2, 1},
        {2, 0, 3},
        {1, 3, 0}};
    g5.loadGraph(graph2);
    CHECK_THROWS(g5 = g5 + g6);

    std::vector<std::vector<int>> graph3 = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}};
    g6.loadGraph(graph3);
    g5 = g5 + g6;
    CHECK(g5.printGraph() == "[0, 2, 1]\n[2, 0, 3]\n[1, 3, 0]");

    srand(time(NULL));
    for (size_t i = 0; i < NUM_OF_TESTS; i++)
    {
        size_t n = (size_t)(rand() % 100) + 5;
        n = n <= 0 ? 5 : n;
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
        n = n <= 0 ? 5 : n;

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

    std::vector<std::vector<int>> graph2 = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}};
    g1.loadGraph(graph2);
    g4 = g2 - g1;
    CHECK(g4.printGraph() == "[0, 1, 1]\n[1, 0, 2]\n[1, 2, 0]");

    ariel::Graph g5;
    CHECK_THROWS(g4 = g4 - g5);

    srand(time(NULL));
    for (size_t i = 0; i < NUM_OF_TESTS; i++)
    {
        size_t n = (size_t)(rand() % 100) + 5;
        n = n <= 0 ? 5 : n;

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

TEST_CASE("Testing +=")
{
    ariel::Graph g1;
    std::vector<std::vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    g1 += g1;
    CHECK(g1.printGraph() == "[0, 2, 0]\n[2, 0, 2]\n[0, 2, 0]");

    ariel::Graph g2;
    std::vector<std::vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph);
    g2 += g1;
    CHECK(g2.printGraph() == "[0, 3, 1]\n[3, 0, 4]\n[1, 4, 0]");

    ariel::Graph g3;
    CHECK_THROWS(g3 += g1);

    ariel::Graph g4;
    std::vector<std::vector<int>> graph2 = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}};
    g4.loadGraph(graph2);
    g4 += g1;
    CHECK(g4.printGraph() == "[0, 2, 0]\n[2, 0, 2]\n[0, 2, 0]");

    // Check deep copy
    g1 += g1;
    CHECK(g1.printGraph() == "[0, 4, 0]\n[4, 0, 4]\n[0, 4, 0]");
    CHECK(g4.printGraph() == "[0, 2, 0]\n[2, 0, 2]\n[0, 2, 0]");

    srand(time(NULL));
    for (size_t i = 0; i < NUM_OF_TESTS; i++)
    {
        size_t n = (size_t)(rand() % 100) + 5;
        n = n <= 0 ? 5 : n;

        ariel::Graph g1;
        ariel::Graph g2;
        std::vector<std::vector<int>> graph1 = RandomGraph(n);
        std::vector<std::vector<int>> graph2 = RandomGraph(n);
        g1.loadGraph(graph1);
        g2.loadGraph(graph2);
        g1 += g2;
        for (size_t i = 0; i < n; i++)
        {
            for (size_t j = 0; j < n; j++)
            {
                CHECK(g1.get_edge(i, j) == graph1[i][j] + graph2[i][j]);
            }
        }
    }
}

TEST_CASE("Testing -=")
{
    ariel::Graph g1;
    std::vector<std::vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    g1 -= g1;
    CHECK(g1.printGraph() == "[0, 0, 0]\n[0, 0, 0]\n[0, 0, 0]");

    ariel::Graph g2;
    std::vector<std::vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph);
    g2 -= g1;
    CHECK(g2.printGraph() == "[0, 1, 1]\n[1, 0, 2]\n[1, 2, 0]");

    ariel::Graph g4;
    std::vector<std::vector<int>> graph2 = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}};
    g4.loadGraph(graph2);
    g4 -= g2;
    CHECK(g4.printGraph() == "[0, -1, -1]\n[-1, 0, -2]\n[-1, -2, 0]");

    ariel::Graph g3;
    std::vector<std::vector<int>> graph3 = {
        {0, 1, 0},
        {0, 0, 0},
        {0, 1, 0}};
    g3.loadGraph(graph3);

    // Check deep copy
    g2 -= g3;
    CHECK(g2.printGraph() == "[0, 0, 1]\n[1, 0, 2]\n[1, 1, 0]");
    CHECK(g4.printGraph() == "[0, -1, -1]\n[-1, 0, -2]\n[-1, -2, 0]");

    srand(time(NULL));
    for (size_t i = 0; i < NUM_OF_TESTS; i++)
    {
        size_t n = (size_t)(rand() % 100) + 5;
        n = n <= 0 ? 5 : n;

        ariel::Graph g1;
        ariel::Graph g2;
        std::vector<std::vector<int>> graph1 = RandomGraph(n);
        std::vector<std::vector<int>> graph2 = RandomGraph(n);
        g1.loadGraph(graph1);
        g2.loadGraph(graph2);
        g1 -= g2;
        for (size_t i = 0; i < n; i++)
        {
            for (size_t j = 0; j < n; j++)
            {
                CHECK(g1.get_edge(i, j) == graph1[i][j] - graph2[i][j]);
            }
        }
    }
}

TEST_CASE("Test * scalar")
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
    ariel::Graph g3 = g1 * 2;
    CHECK(g3.printGraph() == "[0, 2, 0]\n[2, 0, 2]\n[0, 2, 0]");

    ariel::Graph g4 = g2 * -2;
    CHECK(g4.printGraph() == "[0, -2, -2]\n[-2, 0, -4]\n[-2, -4, 0]");

    ariel::Graph g5 = g1 * 0;
    CHECK(g5.printGraph() == "[0, 0, 0]\n[0, 0, 0]\n[0, 0, 0]");

    ariel::Graph g6 = g2 * 5 * 10;
    CHECK(g6.printGraph() == "[0, 50, 50]\n[50, 0, 100]\n[50, 100, 0]");

    srand(time(NULL));
    for (size_t i = 0; i < NUM_OF_TESTS; i++)
    {
        size_t n = (size_t)(rand() % 100) + 5;
        n = n <= 0 ? 5 : n;

        ariel::Graph g1;
        std::vector<std::vector<int>> graph1 = RandomGraph(n);
        g1.loadGraph(graph1);
        int scalar = (rand() % 100) - 50;
        ariel::Graph g2 = g1 * scalar;
        for (size_t i = 0; i < n; i++)
        {
            for (size_t j = 0; j < n; j++)
            {
                CHECK(g2.get_edge(i, j) == scalar * graph1[i][j]);
            }
        }
    }
}

TEST_CASE("Test *= scalar")
{
    ariel::Graph g1;
    std::vector<std::vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    g1 *= -2;
    CHECK(g1.printGraph() == "[0, -2, 0]\n[-2, 0, -2]\n[0, -2, 0]");

    ariel::Graph g2;
    std::vector<std::vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph);
    g2 *= 2;
    CHECK(g2.printGraph() == "[0, 2, 2]\n[2, 0, 4]\n[2, 4, 0]");

    ariel::Graph g3;
    std::vector<std::vector<int>> graph2 = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g3.loadGraph(graph2);
    g3 *= 0;
    CHECK(g3.printGraph() == "[0, 0, 0]\n[0, 0, 0]\n[0, 0, 0]");

    ariel::Graph g4;
    std::vector<std::vector<int>> graph3 = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g4.loadGraph(graph3);
    g4 *= 5 * -10;
    CHECK(g4.printGraph() == "[0, -50, -50]\n[-50, 0, -100]\n[-50, -100, 0]");

    g4 *= 3 * 0;
    CHECK(g4.printGraph() == "[0, 0, 0]\n[0, 0, 0]\n[0, 0, 0]");

    srand(time(NULL));
    for (size_t i = 0; i < NUM_OF_TESTS; i++)
    {
        size_t n = (size_t)(rand() % 100) + 5;
        n = n <= 0 ? 5 : n;

        ariel::Graph g1;
        std::vector<std::vector<int>> graph1 = RandomGraph(n);
        g1.loadGraph(graph1);
        int scalar = (rand() % 100) - 50;
        g1 *= scalar;
        for (size_t i = 0; i < n; i++)
        {
            for (size_t j = 0; j < n; j++)
            {
                CHECK(g1.get_edge(i, j) == scalar * graph1[i][j]);
            }
        }
    }
}

TEST_CASE("Test / scalar")
{
    ariel::Graph g1;
    std::vector<std::vector<int>> graph = {
        {0, 10, 0},
        {10, 0, 10},
        {0, 10, 0}};
    g1.loadGraph(graph);

    ariel::Graph g3 = g1 / 2;
    CHECK(g3.printGraph() == "[0, 5, 0]\n[5, 0, 5]\n[0, 5, 0]");

    ariel::Graph g2;
    std::vector<std::vector<int>> weightedGraph = {
        {0, 10, 12},
        {14, 0, 22},
        {18, 28, 0}};
    g2.loadGraph(weightedGraph);
    ariel::Graph g4 = g2 / -2;
    CHECK(g4.printGraph() == "[0, -5, -6]\n[-7, 0, -11]\n[-9, -14, 0]");

    ariel::Graph g5;
    CHECK_THROWS(g5 = g1 / 0);

    ariel::Graph g6;
    std::vector<std::vector<int>> graph2 = {
        {0, 10, 0},
        {0, 0, 10},
        {10, 0, 0}};
    g6.loadGraph(graph2);
    ariel::Graph g7 = g6 / 2;
    CHECK(g7.printGraph() == "[0, 5, 0]\n[0, 0, 5]\n[5, 0, 0]");

    g7 = g7 / -5;
    CHECK(g7.printGraph() == "[0, -1, 0]\n[0, 0, -1]\n[-1, 0, 0]");

    CHECK_THROWS(g7 = g7 / 0);
}

TEST_CASE("Test /=")
{
    ariel::Graph g1;
    std::vector<std::vector<int>> graph = {
        {0, 10, 0},
        {10, 0, 10},
        {0, 10, 0}};
    g1.loadGraph(graph);
    g1 /= 2;
    CHECK(g1.printGraph() == "[0, 5, 0]\n[5, 0, 5]\n[0, 5, 0]");

    ariel::Graph g2;
    std::vector<std::vector<int>> weightedGraph = {
        {0, 10, 12},
        {14, 0, 22},
        {18, 28, 0}};
    g2.loadGraph(weightedGraph);
    g2 /= -2;
    CHECK(g2.printGraph() == "[0, -5, -6]\n[-7, 0, -11]\n[-9, -14, 0]");

    ariel::Graph g3;
    std::vector<std::vector<int>> graph2 = {
        {0, 10, 0},
        {0, 0, 10},
        {10, 0, 0}};
    CHECK_THROWS(g3 /= 0);

    g3.loadGraph(graph2);
    g3 /= 2;
    CHECK(g3.printGraph() == "[0, 5, 0]\n[0, 0, 5]\n[5, 0, 0]");

    g3 /= -5;
    CHECK(g3.printGraph() == "[0, -1, 0]\n[0, 0, -1]\n[-1, 0, 0]");

    ariel::Graph g4;
    std::vector<std::vector<int>> graph3 = {
        {0, 10, 0},
        {10, 0, 10},
        {0, 10, 0}};
    g4.loadGraph(graph3);
    CHECK_THROWS(g4 /= 0);
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

    ariel::Graph g5;
    vector<vector<int>> graph2 = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}};
    g5.loadGraph(graph2);
    ariel::Graph g6 = g1 * g5;
    CHECK(g6.printGraph() == "[0, 0, 0]\n[0, 0, 0]\n[0, 0, 0]");

    ariel::Graph g7;
    vector<vector<int>> graph3 = {
        {0, 1, 1, 1},
        {1, 0, 2, 1},
        {1, 2, 0, 1},
        {1, 1, 1, 0}};
    g7.loadGraph(graph3);
    CHECK_THROWS(g1 * g7);

    ariel::Graph g8;
    vector<vector<int>> graph4 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    g8.loadGraph(graph4);
    CHECK_THROWS(g1 * g8);
    CHECK_THROWS(g8 * g1);

    ariel::Graph g9;
    vector<vector<int>> graph5 = {
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}};
    g9.loadGraph(graph5);
    ariel::Graph g10 = g9 * g8;
    CHECK(g10.printGraph() == "[0, 0, 0, 0, 0]\n[0, 0, 0, 0, 0]\n[0, 0, 0, 0, 0]\n[0, 0, 0, 0, 0]\n[0, 0, 0, 0, 0]");
}

TEST_CASE("Unary +")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2 = +g1;
    CHECK(g2.printGraph() == "[0, 1, 0]\n[1, 0, 1]\n[0, 1, 0]");

    ariel::Graph g3;
    vector<vector<int>> graph1 = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}};
    g3.loadGraph(graph1);
    g1 = +g3;
    CHECK(g2.printGraph() != g1.printGraph());
}

TEST_CASE("Unary -")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2 = -g1;
    CHECK(g2.printGraph() == "[0, -1, 0]\n[-1, 0, -1]\n[0, -1, 0]");

    ariel::Graph g3;
    vector<vector<int>> graph1 = {
        {0, 0, 1},
        {0, 0, 1},
        {1, 0, 0}};
    g3.loadGraph(graph1);
    g1 = -g3;
    CHECK(g2.printGraph() != g1.printGraph());
}

TEST_CASE("Test ++Graph")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2 = ++g1;
    CHECK(g2.printGraph() == "[0, 2, 0]\n[2, 0, 2]\n[0, 2, 0]");
    CHECK(g1.printGraph() == "[0, 2, 0]\n[2, 0, 2]\n[0, 2, 0]");

    // Check deep copy
    g1.loadGraph(graph);
    CHECK(g2.printGraph() != g1.printGraph());
}

TEST_CASE("Test Graph++")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2 = g1++;
    CHECK(g2.printGraph() == "[0, 1, 0]\n[1, 0, 1]\n[0, 1, 0]");
    CHECK(g1.printGraph() == "[0, 2, 0]\n[2, 0, 2]\n[0, 2, 0]");

    // Check deep copy
    std::vector<std::vector<int>> graph2 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    g2.loadGraph(graph2);
    g1.loadGraph(graph);
    CHECK(g2.printGraph() != g1.printGraph());
}

TEST_CASE("Test Graph--")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2 = g1--;
    CHECK(g2.printGraph() == "[0, 1, 0]\n[1, 0, 1]\n[0, 1, 0]");
    CHECK(g1.printGraph() == "[0, 0, 0]\n[0, 0, 0]\n[0, 0, 0]");

    // Check deep copy
    std::vector<std::vector<int>> graph2 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    g2.loadGraph(graph2);
    g1.loadGraph(graph);
    CHECK(g2.printGraph() != g1.printGraph());
}

TEST_CASE("Test --Graph")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2 = --g1;
    CHECK(g2.printGraph() == "[0, 0, 0]\n[0, 0, 0]\n[0, 0, 0]");
    CHECK(g1.printGraph() == "[0, 0, 0]\n[0, 0, 0]\n[0, 0, 0]");

    // Check deep copy
    std::vector<std::vector<int>> graph2 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    g2.loadGraph(graph2);
    g1.loadGraph(graph);
    CHECK(g2.printGraph() != g1.printGraph());
}

TEST_CASE("Test *= of a Graph")
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
    g1 *= g2;
    vector<vector<int>> expectedGraph = {
        {0, 0, 2},
        {1, 0, 1},
        {1, 0, 0}};
    CHECK(g1.printGraph() == "[0, 0, 2]\n[1, 0, 1]\n[1, 0, 0]");

    ariel::Graph g3;
    vector<vector<int>> graph2 = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}};
    g3.loadGraph(graph2);
    g1 *= g3;
    CHECK(g1.printGraph() == "[0, 0, 0]\n[0, 0, 0]\n[0, 0, 0]");

    ariel::Graph g4;
    vector<vector<int>> graph3 = {
        {0, 1, 1, 1},
        {1, 0, 2, 1},
        {1, 2, 0, 1},
        {1, 1, 1, 0}};
    g4.loadGraph(graph3);
    CHECK_THROWS(g1 *= g4);

    ariel::Graph g5;
    vector<vector<int>> graph4 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    g5.loadGraph(graph4);
    CHECK_THROWS(g1 *= g5);
    CHECK_THROWS(g5 *= g1);
}

TEST_CASE("Test !=")
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
    CHECK(g1 != g2);

    ariel::Graph g3;
    vector<vector<int>> graph2 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g3.loadGraph(graph2);
    CHECK_FALSE(g1 != g3);

    ariel::Graph g4;
    vector<vector<int>> graph3 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    g4.loadGraph(graph3);
    CHECK(g4 != g1);

    ariel::Graph g5;
    CHECK(g5 != g4);
}

TEST_CASE("Test ==")
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
    CHECK_FALSE(g1 == g2);

    ariel::Graph g3;
    vector<vector<int>> graph2 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g3.loadGraph(graph2);
    CHECK(g1 == g3);

    ariel::Graph g4;
    vector<vector<int>> graph3 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    g4.loadGraph(graph3);
    CHECK_FALSE(g4 == g1);
}

TEST_CASE("Test >")
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
    
    // Graph with more edges
    CHECK(g2 > g1);

    ariel::Graph g3;
    vector<vector<int>> graph2 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g3.loadGraph(graph2);
    CHECK_FALSE(g1 > g3);

    ariel::Graph g4;
    vector<vector<int>> graph3 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    g4.loadGraph(graph3);
    CHECK(g4 > g1);

    CHECK(g4 > g2 + g1);

    ariel::Graph g5;
    CHECK_FALSE(g5 > g4);
}

TEST_CASE("Test <")
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
    
    // Graph with less edges
    CHECK(g1 < g2);

    ariel::Graph g3;
    vector<vector<int>> graph2 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g3.loadGraph(graph2);
    CHECK_FALSE(g3 < g1);

    ariel::Graph g4;
    vector<vector<int>> graph3 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    g4.loadGraph(graph3);
    CHECK(g1 < g4);

    CHECK(g2 + g1 < g4);

    ariel::Graph g5;
    CHECK_FALSE(g4 < g5);

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