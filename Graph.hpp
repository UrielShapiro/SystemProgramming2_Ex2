/**
 * Last digits of ID: 9745
 * Email address: uriel1999@gmail.com
 */

#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <iostream>
using namespace std;
namespace ariel
{
    class Graph
    {
    private:
        std::vector<std::vector<int>> graph;
        bool isDirected;
        bool containsNegativeEdge;
        size_t _edges;

    public:
        /**
         * Constructors:
         */
        Graph();
        Graph(const std::vector<std::vector<int>> g);
        Graph(const Graph &other);

        /*
         * This function loads a graph from a given matrix.
         * The function checks if the matrix is empty.
         * The function checks if the matrix is a square matrix.
         * The function checks if the matrix is symmetric - if it is, the graph is undirected.
         * The function checks if the matrix contains negative edges.
         * The function checks if the distance from a vertex to itself isn't 0.
         */
        void loadGraph(std::vector<std::vector<int>> g);

        /*
         * The function prints the graph as a matrix.
         * The function counts the number of edges in the graph.
         * The function prints the number of vertices and edges in the graph.
         */
        std::string printGraph();
        const size_t size() const;
        const int get_edge(const size_t i, const size_t j) const;
        vector<int> at(const size_t i) const;
        const size_t NumOfVertices() const; // This function was made only for readability.
        const size_t NumOfEdges() const;
        const bool isDirectedGraph() const;
        const bool isContainsNegativeEdge() const;

        /*
         * This function creates an undirected graph from a directed graph.
         * The function creates a new graph with the same vertices as the original graph.
         * The function then copies the edges from the original graph to the new graph.
         * The function then copies the edges from the original graph to the new graph in reverse order.
         * The function then sets the new graph as undirected.
         * @returns the new undirected graph.
         */
        static Graph MakeUndirectedGraph(Graph g);
        bool operator==(const Graph &other) const;
        bool operator!=(const Graph &other) const;
        Graph &operator=(const Graph &other);
        Graph operator-(const Graph &other) const;
        Graph operator+(const Graph &other) const;
        Graph operator+() const;
        Graph operator-() const;
        Graph operator*(const Graph &other) const;
        Graph operator*(const int scalar) const;
        Graph operator/(const int scalar) const;
        Graph &operator*=(const int scalar);
        Graph &operator/=(const int scalar);
        Graph &operator++();
        Graph operator++(int);
        Graph &operator--();
        Graph operator--(int);
        Graph &operator+=(const Graph &other);
        Graph &operator-=(const Graph &other);
        Graph &operator*=(const Graph &other);

        bool operator>(const Graph &other) const;
        bool operator<(const Graph &other) const;
        bool operator>=(const Graph &other) const;
        bool operator<=(const Graph &other) const;

        friend std::ostream &operator<<(std::ostream &os, const ariel::Graph &g);
    };
};
#endif
