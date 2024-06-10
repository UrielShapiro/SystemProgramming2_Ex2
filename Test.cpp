/**
 * Last digits of ID: 9745
 * Email address: uriel1999@gmail.com
*/

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

    ariel::Graph g5;
    CHECK_THROWS(g5 -= g3);

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

    g6 = g6 * 1;
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

    g4 = g4 / 1;
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

    ariel::Graph g5;
    ariel::Graph g6;
    CHECK(g5 == g6);
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

    ariel::Graph g6;
    CHECK_FALSE(g5 > g6);
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
    
    ariel::Graph g6;
    CHECK_FALSE(g5 < g6);
}

TEST_CASE("Test >=")
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
    CHECK(g2 >= g1);

    ariel::Graph g3;
    vector<vector<int>> graph2 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g3.loadGraph(graph2);
    CHECK(g1 >= g3);

    ariel::Graph g4;
    vector<vector<int>> graph3 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    g4.loadGraph(graph3);
    CHECK(g4 >= g1);

    CHECK(g4 >= g2 + g1);

    ariel::Graph g5;
    CHECK_FALSE(g5 >= g4);

    ariel::Graph g6;
    CHECK(g5 >= g6);
}

TEST_CASE("Test <=")
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
    CHECK(g1 <= g2);

    ariel::Graph g3;
    vector<vector<int>> graph2 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g3.loadGraph(graph2);
    CHECK(g3 <= g1);

    ariel::Graph g4;
    vector<vector<int>> graph3 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    g4.loadGraph(graph3);
    CHECK(g1 <= g4);

    CHECK(g2 + g1 <= g4);

    ariel::Graph g5;
    CHECK_FALSE(g4 <= g5);

    ariel::Graph g6;
    CHECK(g5 <= g6);
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

/**
 * Last digits of ID: 9745
 * Mail: uriel1999@gmail.com
*/

#include "doctest.h"
#include "Algorithms.hpp"
#include "Graph.hpp"
#include <iostream>
#include <vector>

using namespace std;

TEST_CASE("Test isConnected - Connected")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isConnected(g) == true);

    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {0, 0, 0, 1, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::isConnected(g) == true);

    vector<vector<int>> graph3 = {
        {0, 0, -27, -9, 0},
        {0, 0, 0, 6, 0},
        {-27, 0, 0, 0, -29},
        {-9, 6, 0, 0, -22},
        {0, 0, -29, -22, 0}};
    g.loadGraph(graph3);
    CHECK(ariel::Algorithms::isConnected(g) == true);

    vector<vector<int>> graph4 = {
        {0, -50, 0, 0, -43, 14, 0, -39, -38, 0, 37, 8, 27, 23, 26, 49, -44},
        {-50, 0, -48, 0, 0, 0, -27, 0, 44, -6, 0, -39, -44, 43, 0, -5, -16},
        {0, -48, 0, -8, -50, 0, 0, 11, 19, 37, 32, 0, 0, 0, 0, 35, -23},
        {0, 0, -8, 0, 0, -9, 11, 20, 33, 43, -37, 0, 0, -1, 0, 0, -19},
        {-43, 0, -50, 0, 0, 13, 0, -23, -24, -35, -27, 0, 0, 44, 0, 0, -17},
        {14, 0, 0, -9, 13, 0, -34, 0, 0, 0, -42, 0, -23, 0, -39, 0, -1},
        {0, -27, 0, 11, 0, -34, 0, 0, 0, 0, 24, 0, -24, 0, -29, 0, 0},
        {-39, 0, 11, 20, -23, 0, 0, 0, 20, 0, 0, 18, 27, 39, 38, 0, 0},
        {-38, 44, 19, 33, -24, 0, 0, 20, 0, -19, 0, 0, 0, 14, 0, 16, -14},
        {0, -6, 37, 43, -35, 0, 0, 0, -19, 0, -26, -10, 0, 0, 0, 0, -23},
        {37, 0, 32, -37, -27, -42, 24, 0, 0, -26, 0, -13, 0, 0, 0, -38, 18},
        {8, -39, 0, 0, 0, 0, 0, 18, 0, -10, -13, 0, -18, 0, 0, 0, 0},
        {27, -44, 0, 0, 0, -23, -24, 27, 0, 0, 0, -18, 0, -48, 39, 10, 0},
        {23, 43, 0, -1, 44, 0, 0, 39, 14, 0, 0, 0, -48, 0, 0, -37, -25},
        {26, 0, 0, 0, 0, -39, -29, 38, 0, 0, 0, 0, 39, 0, 0, 12, 25},
        {49, -5, 35, 0, 0, 0, 0, 0, 16, 0, -38, 0, 10, -37, 12, 0, -31},
        {-44, -16, -23, -19, -17, -1, 0, 0, -14, -23, 18, 0, 0, -25, 25, -31, 0}};
    g.loadGraph(graph4);
    CHECK(ariel::Algorithms::isConnected(g) == true);

    vector<vector<int>> graph5 = {
        {0, 46, -47, 2},
        {46, 0, 21, -18},
        {-47, 21, 0, 0},
        {2, -18, 0, 0}};
    g.loadGraph(graph5);
    CHECK(ariel::Algorithms::isConnected(g) == true);

    vector<vector<int>> graph7 = {{0}};
    g.loadGraph(graph7);
    CHECK(ariel::Algorithms::isConnected(g) == true);
}

TEST_CASE("isConnected - Not Connected")
{
    ariel::Graph g;
    vector<vector<int>> graph1 = {
        {0, 1, 1, 0},
        {1, 0, 1, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0}};
    g.loadGraph(graph1);
    CHECK(ariel::Algorithms::isConnected(g) == false);

    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::isConnected(g) == false);

    vector<vector<int>> graph3 = {
        {0, 0, -39, 0, 0, 0},
        {0, 0, 0, 0, 0, 0},
        {-39, 0, 0, 46, 0, 0},
        {0, 0, 46, 0, 22, 0},
        {0, 0, 0, 22, 0, -23},
        {0, 0, 0, 0, -23, 0}};
    g.loadGraph(graph3);
    CHECK(ariel::Algorithms::isConnected(g) == false);

    vector<vector<int>> graph4 = {
        {0, 0, 19, 0, 0},
        {0, 0, 0, -22, -50},
        {19, 0, 0, 0, 0},
        {0, -22, 0, 0, 0},
        {0, -50, 0, 0, 0}};
    g.loadGraph(graph4);
    CHECK(ariel::Algorithms::isConnected(g) == false);
    
    vector<vector<int>> graph8 = {
        {0, 0, 3},
        {0, 0, 0},
        {0, 3, 0}};
    g.loadGraph(graph8);
    CHECK(ariel::Algorithms::isConnected(g) == false);

    vector<vector<int>> graph5 = {
        {0, 9, 0, 28, -32, -15, 13, 0, 27, 0, -49, -3, 0},
        {9, 0, 0, -9, 11, 0, 41, 0, 0, -46, 0, 9, 0},
        {0, 0, 0, -36, 47, 0, 18, 0, 7, 0, -36, 25, 0},
        {28, -9, -36, 0, 0, 0, 0, 0, 0, 0, 21, -1, 0},
        {-32, 11, 47, 0, 0, -42, 0, -27, -46, 2, -12, 16, 0},
        {-15, 0, 0, 0, -42, 0, -9, 0, 36, 15, -19, 16, 0},
        {13, 41, 18, 0, 0, -9, 0, 44, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, -27, 0, 44, 0, -12, -4, 0, 18, 0},
        {27, 0, 7, 0, -46, 36, 0, -12, 0, 0, 0, 0, 0},
        {0, -46, 0, 0, 2, 15, 0, -4, 0, 0, -27, 42, 0},
        {-49, 0, -36, 21, -12, -19, 0, 0, 0, -27, 0, 23, 0},
        {-3, 9, 25, -1, 16, 16, 0, 18, 0, 42, 23, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
    g.loadGraph(graph5);
    CHECK(ariel::Algorithms::isConnected(g) == false);
}

TEST_CASE("Test shortestPath - Positive edges")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 2) == "0->1->2");

    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 4) == "-1");

    vector<vector<int>> graph3 = {
        {0, 1, 2, 0, 0},
        {1, 0, 3, 0, 0},
        {2, 3, 0, 4, 0},
        {0, 0, 4, 0, 5},
        {0, 0, 0, 5, 0}};
    g.loadGraph(graph3);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 4) == "0->2->3->4");

    vector<vector<int>> graph4 = {
        {0, 43, 0, 35},
        {0, 0, 40, 0},
        {0, 0, 0, 31},
        {0, 0, 0, 0}};
    g.loadGraph(graph4);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 2) == "0->1->2");

    vector<vector<int>> graph5 = {{0}};
    g.loadGraph(graph5);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 0) == "0");

    vector<vector<int>> graph6 = {
        {0, 43, 0, 35},
        {0, 0, 40, 0},
        {0, 0, 0, 31},
        {0, 0, 0, 0}};
    g.loadGraph(graph6);
    CHECK(ariel::Algorithms::shortestPath(g, 2, 2) == "0");
}

TEST_CASE("Test shortestPath - Negative edges")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, -1, 0},
        {0, 0, -1},
        {0, 0, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 2) == "0->1->2");

    vector<vector<int>> graph1 = {
        {0, 37, -9, 11},
        {0, 0, 0, 0},
        {0, 0, 0, 2},
        {0, 0, 0, 0}};

    g.loadGraph(graph1);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 2) == "0->2");

    vector<vector<int>> graph2 = {
        {0, 43, 0, 35},
        {0, 0, -40, 0},
        {0, 0, 0, 31},
        {0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 2) == "0->1->2");
}

TEST_CASE("Shortest Path - Negative Cycle")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 0, 0, 2, 0},
        {0, 0, -1, -1, 0},
        {0, -1, 0, -1, 0},
        {2, -1, -1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 4) == "-1");


    vector<vector<int>> graph1 = {
       { 0, -5, -5, 0},
       { -5, 0, 0, -5},
       { -5, 0, 0, -5},
        {0, -5, -5, 0}};
    g.loadGraph(graph1);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 3) == "-1");
}

TEST_CASE("Test isContainsCycle - Not contained")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isContainsCycle(g) == "0");

    vector<vector<int>> graph3 = {
        {0, 0, 0, 0, -5},
        {0, 0, 0, 3, 0},
        {0, 0, 0, 20, 0},
        {0, 0, 0, 0, 0},
        {0, -10, 10, 0, 0}};
    g.loadGraph(graph3);
    CHECK(ariel::Algorithms::isContainsCycle(g) == "0");

    vector<vector<int>> graph2 = {
        {0, 0, -10, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 3},
        {0, 3, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::isContainsCycle(g) == "0");
}

TEST_CASE("Test isContainsCycle - contained")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 33, 0, 20},
        {33, 0, 42, 30},
        {0, 42, 0, 0},
        {20, 30, 0, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isContainsCycle(g) == "The cycle is: 0->1->3->0");

    vector<vector<int>> graph1 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph1);
    CHECK(ariel::Algorithms::isContainsCycle(g) == "The cycle is: 0->1->2->0");

    vector<vector<int>> graph2 = {
        {0, 41, 0, 37, 17, 10, 0},
        {41, 0, -3, 31, -1, 0, 25},
        {0, -3, 0, 0, 0, 16, -4},
        {37, 31, 0, 0, 42, 44, -3},
        {17, -1, 0, 42, 0, 0, 0},
        {10, 0, 16, 44, 0, 0, -3},
        {0, 25, -4, -3, 0, -3, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::isContainsCycle(g) == "The cycle is: 0->1->2->5->0");
}

TEST_CASE("Test isBipartite - is bipartite")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0, 2}, B={1}");

    vector<vector<int>> graph1 = {
        {0, 12, 0, 4, 0},
        {12, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {4, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph1);
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0, 2, 4}, B={1, 3}");

    vector<vector<int>> graph2 = {
        {0, -1, 0, 0, 0, 0, 0},
        {-1, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 22, 0, 0, 0},
        {0, 0, 22, 0, 0, 3, 0},
        {0, 0, 0, 0, 0, 48, 20},
        {0, 0, 0, 3, 48, 0, 0},
        {0, 0, 0, 0, 20, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0, 2, 5, 6}, B={1, 3, 4}");

    vector<vector<int>> graph3 = {
        {0, 0, 0, 20, 0},
        {0, 0, 0, 0, 20},
        {0, 0, 0, 37, 32},
        {20, 0, 37, 0, 0},
        {0, 20, 32, 0, 0}};
    g.loadGraph(graph3);
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0, 1, 2}, B={3, 4}");
}

TEST_CASE("Test isBipartite - is not")
{
    ariel::Graph g;
    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::isBipartite(g) == "0");

    vector<vector<int>> graph3 = {
        {0, 1, 2, 0, 0},
        {1, 0, 3, 0, 0},
        {2, 3, 0, 4, 0},
        {0, 0, 4, 0, 5},
        {0, 0, 0, 5, 0}};
    g.loadGraph(graph3);
    CHECK(ariel::Algorithms::isBipartite(g) == "0");

    vector<vector<int>> graph4 = {
        {0, 0, 0, 2, 0},
        {0, 0, -1, -1, 0},
        {0, -1, 0, -1, 0},
        {2, -1, -1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph4);
    CHECK(ariel::Algorithms::isBipartite(g) == "0");

    vector<vector<int>> graph5 = {
        {0, 0, 0, 20, 3},
        {0, 0, 0, 0, 20},
        {0, 0, 0, 37, 32},
        {20, 0, 37, 0, 10},
        {3, 20, 32, 10, 0}};
    g.loadGraph(graph5);
    CHECK(ariel::Algorithms::isBipartite(g) == "0");

    vector<vector<int>> graph6 = {
        {0, -1, 25, 21, 0, 47},
        {-1, 0, 16, 0, 41, 8},
        {25, 16, 0, 31, 0, 49},
        {21, 0, 31, 0, -5, 11},
        {0, 41, 0, -5, 0, 34},
        {47, 8, 49, 11, 34, 0}};
    g.loadGraph(graph6);
    CHECK(ariel::Algorithms::isBipartite(g) == "0");

    vector<vector<int>> graph7 = {
        {0, 21, 11, 4, 46},
        {0, 0, -5, 0, 42},
        {0, 0, 0, -5, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph7);
    CHECK(ariel::Algorithms::isBipartite(g) == "0");
}

TEST_CASE("Test invalid graph")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 2, 0},
        {1, 0, 3, 0},
        {2, 3, 0, 4},
        {0, 0, 4, 0},
        {0, 0, 0, 5}};
    CHECK_THROWS(g.loadGraph(graph));

    vector<vector<int>> graph1 = {
        {0, 1, 2, 0},
        {1, 0, 3, 0},
        {2, 3, 0, 4},
        {0, 0, 4, 0},
        {0, 0, 0, 5},
        {0, 0, 0, 0}};
    CHECK_THROWS(g.loadGraph(graph1));

    vector<vector<int>> graph2 = {
        {0, 1, 2, 0},
        {1, 0, 3, 0},
        {2, 3, 0, 4},
        {0, 0, 4, 0},
        {0, 0, 0, 5},
        {0, 0, 0, 0},
        {0, 0, 0, 0}};
    CHECK_THROWS(g.loadGraph(graph2));

    vector<vector<int>> graph3 = {
        {0, 1, 2, 0, 5, 7},
        {1, 0, 3, 0, 0, 0}};
    CHECK_THROWS(g.loadGraph(graph3));

    vector<vector<int>> graph4 = {
        {0, 1, 2, 0, 5, 7},
        {1, 0, 1, 0},
        {2, 3, 0, 4, 0, 0}};
    CHECK_THROWS(g.loadGraph(graph4));
}

TEST_CASE("Test negativeCycle - Not negative cycles")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::negativeCycle(g) == "The graph does not contain a negative cycle.");

    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::negativeCycle(g) == "The graph does not contain a negative cycle.");

    vector<vector<int>> graph3 = {
        {0, 3, -10, 0},
        {3, 0, 0, 20},
        {-10, 0, 0, 30},
        {0, 20, 30, 0}};
    g.loadGraph(graph3);
    CHECK(ariel::Algorithms::negativeCycle(g) == "The graph does not contain a negative cycle.");

    vector<vector<int>> graph4 = {
        {0, 5, 1, 0},
        {0, 0, 0, -10},
        {1, 0, 0, 30},
        {0, -10, 30, 0}};
    g.loadGraph(graph4);
    CHECK(ariel::Algorithms::negativeCycle(g) == "The graph does not contain a negative cycle.");
}

TEST_CASE("Test negativeCycle - Negative cycles")
{
    ariel::Graph g;
    vector<vector<int>> graph3 = {
        {0, 0, 0, 2, 0, 0, 0, 0},
        {0, 0, -1, -1, 0, 0, 0, 0},
        {0, -1, 0, -1, 0, 0, 0, 0},
        {2, -1, -1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 5},
        {0, 0, 0, 0, 0, 0, 1, 0},
        {0, 0, 0, 0, 0, 1, 0, 5},
        {0, 0, 0, 0, 5, 0, 5, 0}};
    g.loadGraph(graph3);
    CHECK(ariel::Algorithms::negativeCycle(g) == "The graph contains a negative cycle: 2->3->1->2");

    vector<vector<int>> graph4 = {
        {0, 0, 0, 2, 0},
        {0, 0, -1, -1, 0},
        {0, -1, 0, -1, 0},
        {2, -1, -1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph4);
    CHECK(ariel::Algorithms::negativeCycle(g) == "The graph contains a negative cycle: 2->3->1->2");

    vector<vector<int>> graph5 = {
        {0, 0, 0, 2, 0},
        {0, 0, -1, -1, 0},
        {0, -1, 0, -1, 0},
        {2, -1, -1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph5);
    CHECK(ariel::Algorithms::negativeCycle(g) == "The graph contains a negative cycle: 2->3->1->2");
}
