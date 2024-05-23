/**
 * Last digits of ID: 9745
 * Email address: uriel1999@gmail.com
*/

#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include <string>
#include "Graph.hpp"
namespace ariel
{
    class Algorithms
    {
    private:
        enum Color
        {
            UNCOLORED,
            RED,
            BLUE
        };
        enum Visited
        {
            WHITE,
            GREY,
            BLACK
        };
        static size_t min_neighbor(const std::vector<int> &dist, const std::vector<bool> &converged);
        static bool should_relax(size_t u, size_t v, int weight, std::vector<int> dist);
        static void dijkstra(Graph g, size_t src, size_t end, std::vector<int> &dist, std::vector<size_t> &parents);
        static bool relax(Graph g, size_t v, size_t u, std::vector<int> &distance, std::vector<size_t> &parents);
        static bool BellmanFord(Graph g, size_t src, std::vector<int> &dist, std::vector<size_t> &parents, std::vector<size_t> &cycleNodes);
        static void DFS(Graph g, size_t current, size_t parent, std::vector<bool> &visited, std::vector<bool> &inStack);
        static bool BFSColoring(Graph g, size_t start, std::vector<Color> &colors);
        static size_t DFSCycleCheck(Graph g, size_t current, size_t parent, std::vector<Visited> &visited,
                                    std::vector<size_t> &parents, std::vector<size_t> &cycleNodes);
        static std::string printPath(size_t src, size_t parent, std::vector<size_t> parents);

    public:
        static bool isConnected(Graph g);
        static std::string shortestPath(Graph g, size_t start, size_t end);
        static std::string isContainsCycle(Graph g);
        static std::string isBipartite(Graph g);
        static std::string negativeCycle(Graph g);
    };
};
#endif