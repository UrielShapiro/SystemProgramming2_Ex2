#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
using namespace std;
namespace ariel
{
    class Graph
    {
    private:
        std::vector<std::vector<int>> graph;
        bool isDirected;
        bool containsNegativeEdge;

    public:
        Graph();
        Graph(const std::vector<std::vector<int>> g);
        void loadGraph(std::vector<std::vector<int>> graph);
        void printGraph();
        size_t size() const;
        int get_edge(const size_t i, const size_t j) const;
        vector<int> at(const size_t i) const;
        bool isDirectedGraph() const;
        bool isContainsNegativeEdge() const;
        static Graph MakeUndirectedGraph(Graph g);
        bool operator==(const Graph &other) const;
        bool operator!=(const Graph &other) const;
        Graph &operator=(const Graph &other);
        Graph operator-(const Graph &other);
        Graph operator+(const Graph &other);
        Graph operator+();
        Graph operator-();
        Graph operator*(const Graph &other);
        Graph operator*(const int &scalar);
        Graph operator/(const int &scalar);
        Graph &operator++();
        Graph &operator++(int);
        Graph &operator--();
        Graph &operator--(int);
        Graph &operator+=(const Graph &other);
        Graph &operator-=(const Graph &other);
        ostream &operator<<(ostream &os);
    };
};
#endif
