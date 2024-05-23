#include <iostream>
#include <vector>
#include <stdexcept> // invalid_argument
#include <sstream>   // ostringstream
#include <string>    // string

#include "Graph.hpp"
using namespace ariel;
namespace ariel
{
    size_t NumOfVertices(const Graph &g)
    {
        return g.size();
    }

    std::vector<int> Graph::at(const size_t i) const
    {
        return this->graph.at(i);
    }

    ariel::Graph::Graph() : _edges(0), isDirected(false), containsNegativeEdge(false) {}

    ariel::Graph::Graph(const std::vector<std::vector<int>> g) : isDirected(false), containsNegativeEdge(false), _edges(0)
    {
        loadGraph(g);
    }

    ariel::Graph::Graph(const Graph &other) : isDirected(other.isDirected), containsNegativeEdge(other.containsNegativeEdge), _edges(0)
    {
        loadGraph(other.graph);
    }

    Graph ariel::Graph::MakeUndirectedGraph(Graph g)
    {
        Graph undirectedGraph;
        std::vector<std::vector<int>> newGraph(g.graph);
        undirectedGraph.loadGraph(newGraph); // Load the original graph to the new graph.
        undirectedGraph._edges = 0;          // Reset the number of edges becuase we will recalculate it.
        for (size_t i = 0; i < g.size(); i++)
        {
            for (size_t j = 0; j < g.size(); j++)
            {
                if (g.graph.at(i).at(j) != 0)
                {
                    undirectedGraph.graph.at(j).at(i) = g.graph.at(i).at(j); // Copy g[i][j] to undirectedGraph[j][i].
                    undirectedGraph._edges++;
                }
            }
        }
        undirectedGraph.isDirected = false; // Set the new graph as undirected.
        return undirectedGraph;
    }

    void ariel::Graph::loadGraph(const std::vector<std::vector<int>> g)
    {
        if (g.empty())
        {
            throw invalid_argument("Invalid graph: The graph is empty.");
        }
        if (g.size() != g.at(0).size()) // Check if the matrix is a square matrix.
        {
            throw invalid_argument("Invalid graph: The graph is not a square matrix.");
        }
        this->graph.clear(); // Clear the graph, if it was already initialized.
        std::vector<int> row;
        for (size_t i = 0; i < g.size(); i++)
        {
            for (size_t j = 0; j < g.size(); j++)
            {
                row.push_back(g.at(i).at(j)); // Copy the row from the matrix to the graph.
                if (g.at(i).at(j) != g.at(j).at(i))
                {
                    this->isDirected = true; // If the matrix is not symmetric, the graph is directed.
                }
                if (g.at(i).at(j) < 0) // If the matrix contains negative edge, we will mark this graph as containing negative edges.
                {
                    this->containsNegativeEdge = true;
                }
                if (g.at(i).at(j) != 0)
                {
                    this->_edges++;
                }
            }
            if (row.at(i) != 0) // Check if the distance from a vertex to itself isn't 0.
            {
                throw invalid_argument("Invalid graph: The distance from a vertex to itself must be 0.");
            }
            this->graph.push_back(row);
            row.clear(); // Clear the row, for the next iteration.
        }
    }

    std::string ariel::Graph::printGraph()
    {
        stringstream graph_str;
        int edges = 0;
        for (size_t i = 0; i < this->graph.size(); i++)
        {
            graph_str << "[";
            for (size_t j = 0; j < this->graph.size(); j++)
            {
                if (j == this->graph.size() - 1)
                {
                    graph_str << to_string(this->graph.at(i).at(j));
                }
                else
                {
                    graph_str << to_string(this->graph.at(i).at(j)) << ", ";
                }
                if (this->graph.at(i).at(j) != 0)
                {
                    edges++;
                }
            }
            if (i == this->graph.size() - 1)
            {
                graph_str << "]";
            }
            else
            {
                graph_str << "]\n";
            }
        }
        return graph_str.str();
    }

    ///////////////////////////////////////////////////////////OPERATOR OVERLOADING/////////////////////////////////////////////////////

    Graph &Graph::operator=(const Graph &other)
    {
        this->loadGraph(other.graph);
        return *this;
    }

    /**
     * Equality/inequality operators:
     */
    bool Graph::operator==(const Graph &other) const
    {
        if(this->graph.empty() && other.graph.empty())
        {
            return true;
        }

        // Check if the number of vertices is the same.
        bool condition1 = this->NumOfVertices() == other.NumOfVertices();

        // Check if the weight of each edge is the same.
        if (condition1)
        {
            for (size_t i = 0; i < this->graph.size(); i++)
            {
                for (size_t j = 0; j < this->graph.at(i).size(); j++)
                {
                    if (this->graph.at(i).at(j) != other.graph.at(i).at(j))
                    {
                        condition1 = false;
                        break;
                    }
                }
                if (!condition1)
                {
                    break;
                }
            }
        }

        bool condition2 = *this <= other && *this >= other;

        return condition1 || condition2;
    }

    bool Graph::operator!=(const Graph &other) const
    {
        return !(*this == other);
    }

    /**
     * Unary Operations:
     */

    Graph Graph::operator+() const
    {
        return *this;
    }

    Graph Graph::operator-() const
    {
        return *this * (-1);
    }
    // Prefix increment operator.
    Graph &Graph::operator++()
    {
        for (size_t i = 0; i < this->graph.size(); i++)
        {
            for (size_t j = 0; j < this->graph.at(i).size(); j++)
            {
                if (this->graph.at(i).at(j) != 0)
                {
                    ++(this->graph.at(i).at(j));
                }
            }
        }
        return *this;
    }

    // Postfix increment operator.
    Graph Graph::operator++(int)
    {
        Graph temp(*this);
        ++(*this);
        return temp;
    }

    // Prefix decrement operator.
    Graph &Graph::operator--()
    {
        for (size_t i = 0; i < this->graph.size(); i++)
        {
            for (size_t j = 0; j < this->graph.at(i).size(); j++)
            {
                if (this->graph.at(i).at(j) != 0)
                {
                    --(this->graph.at(i).at(j));
                }
            }
        }
        return *this;
    }

    // Postfix decrement operator.
    Graph Graph::operator--(int)
    {
        Graph temp(*this);
        --(*this);
        return temp;
    }

    /**
     * Binary Operations:
     */
    Graph Graph::operator+(const ariel::Graph &other) const
    {
        if (this->graph.size() != other.graph.size())
        {
            throw invalid_argument("The graphs must have the same size.");
        }
        std::vector<std::vector<int>> new_adj_matrix;
        for (size_t i = 0; i < this->graph.size(); i++)
        {
            std::vector<int> row;
            for (size_t j = 0; j < this->graph.at(i).size(); j++)
            {
                row.push_back(this->graph.at(i).at(j) + other.graph.at(i).at(j));
            }
            new_adj_matrix.push_back(row);
            row.clear();
        }
        return Graph(new_adj_matrix);
    }

    Graph Graph::operator-(const Graph &other) const
    {
        if (this->graph.size() != other.graph.size())
        {
            throw invalid_argument("The graphs must have the same size.");
        }
        std::vector<std::vector<int>> new_adj_matrix;
        for (size_t i = 0; i < this->graph.size(); i++)
        {
            std::vector<int> row;
            for (size_t j = 0; j < this->graph.at(i).size(); j++)
            {
                row.push_back(this->graph.at(i).at(j) - other.graph.at(i).at(j));
            }
            new_adj_matrix.push_back(row);
            row.clear();
        }
        return Graph(new_adj_matrix);
    }

    Graph Graph::operator*(const int scalar) const
    {
        // Checking base cases before performing the operation for optimization.
        if (scalar == 0)
        {
            std::vector<std::vector<int>> new_adj_matrix(this->graph.size(), std::vector<int>(this->graph.size(), 0));
            return Graph(new_adj_matrix);
        }
        if (scalar == 1)
        {
            return *this;
        }

        std::vector<std::vector<int>> new_adj_matrix;
        for (size_t i = 0; i < this->graph.size(); i++)
        {
            std::vector<int> row;
            for (size_t j = 0; j < this->graph.at(i).size(); j++)
            {
                row.push_back(this->graph.at(i).at(j) * scalar);
            }
            new_adj_matrix.push_back(row);
            row.clear();
        }
        return Graph(new_adj_matrix);
    }

    Graph Graph::operator/(const int scalar) const
    {
        // Checking base cases before performing the operation for optimization.
        if (scalar == 0)
        {
            throw invalid_argument("Cannot divide by zero.");
        }
        if (scalar == 1)
        {
            return *this;
        }

        std::vector<std::vector<int>> new_adj_matrix;
        for (size_t i = 0; i < this->graph.size(); i++)
        {
            std::vector<int> row;
            for (size_t j = 0; j < this->graph.at(i).size(); j++)
            {
                row.push_back(this->graph.at(i).at(j) / scalar);
            }
            new_adj_matrix.push_back(row);
            row.clear();
        }
        return Graph(new_adj_matrix);
    }

    Graph Graph::operator*(const Graph &other) const
    {
        if (this->graph.size() != other.graph.size() || this->graph.at(0).size() != other.graph.at(0).size())
        {
            throw invalid_argument("The number of columns in the first matrix must be equal to the number of rows in the second matrix.");
        }

        size_t graph_size = this->graph.size(); // For optimization - so that we don't have to call this->graph.size() multiple times.

        // Initialize the new graph adjecency matrix with zeros.
        std::vector<std::vector<int>> new_adj_matrix(graph_size, std::vector<int>(graph_size, 0));

        for (size_t i = 0; i < graph_size; i++)
        {
            for (size_t j = 0; j < graph_size; j++)
            {
                for (size_t k = 0; k < graph_size; k++)
                {
                    if (i == j)
                    {
                        continue;
                    }
                    new_adj_matrix[i][j] += this->graph.at(i).at(k) * other.graph.at(k).at(j);
                }
            }
        }
        return Graph(new_adj_matrix);
    }

    /**
     * Arithmetic Operator + Assignment operators:
     */
    Graph &Graph::operator+=(const Graph &other)
    {
        if (this->graph.size() != other.graph.size())
        {
            throw invalid_argument("The graphs must have the same size.");
        }
        *this = *this + other;
        return *this;
    }

    Graph &Graph::operator-=(const Graph &other)
    {
        if (this->graph.size() != other.graph.size())
        {
            throw invalid_argument("The graphs must have the same size.");
        }
        *this = *this - other;
        return *this;
    }

    Graph &Graph::operator*=(const Graph &other)
    {
        if (this->graph.size() != other.graph.size())
        {
            throw invalid_argument("The graphs must have the same size.");
        }
        *this = *this * other;
        return *this;
    }

    Graph &Graph::operator*=(const int scalar)
    {
        *this = *this * scalar;
        return *this;
    }

    Graph &Graph::operator/=(const int scalar)
    {
        *this = *this / scalar;
        return *this;
    }

    /**
     * @brief This function checks if g1 is a subgraph of g2.
     * @source: https://www.quora.com/Which-is-the-fastest-way-to-check-if-a-matrix-A-contains-a-matrix-B
     * @return true if g1 is a subgraph of g2, otherwise false.
     */
    bool GridSearch(const Graph &g1, const Graph &g2)
    {
        if (g1.size() > g2.size())
        {
            return false;
        }

        for (size_t i = 0; i <= g2.size() - g1.size(); ++i)
        {
            for (size_t j = 0; j <= g2.size() - g1.size(); ++j)
            {
                // Check if the submatrix starting at (i, j) matches g1.
                bool isMatch = true;
                for (size_t x = 0; x < g1.size(); ++x)
                {
                    for (size_t y = 0; y < g1.size(); ++y)
                    {
                        if (g2.at(i + x).at(j + y) != g1.at(x).at(y))
                        {
                            isMatch = false;
                            break;
                        }
                    }
                    if (!isMatch)
                    {
                        break;
                    }
                }
                if (isMatch)
                {
                    return true;
                }
            }
        }

        // If we reached here, g1 is not a subgraph of g2.
        return false;
    }

    /**
     * Relational Operators:
     */

    /**
     * @brief: This function compares two graphs in java like style.
     * @return: 0 if the graphs are equal, 1 if g1 > g2, -1 if g1 < g2.
     */
    int compare(const Graph &g1, const Graph &g2)
    {
        bool are_equal = g1.isContainsNegativeEdge() == g2.isContainsNegativeEdge() &&
                         g1.NumOfVertices() == g2.NumOfVertices();

        if (are_equal)
        {
            // Check if the weight of each edge is the same.
            for (size_t i = 0; i < g1.size(); i++)
            {
                for (size_t j = 0; j < g1.size(); j++)
                {
                    if (g1.at(i).at(j) != g2.at(i).at(j))
                    {
                        are_equal = false;
                    }
                }
            }
        }

        if (are_equal)
        {
            return 0;
        }
        if (g1.NumOfVertices() > g2.NumOfVertices() && GridSearch(g2, g1))
        {
            return 1;
        }
        if (g1.NumOfVertices() < g2.NumOfVertices() && GridSearch(g1, g2))
        {
            return -1;
        }
        if (g1.NumOfEdges() > g2.NumOfEdges())
        {
            return 1;
        }
        if (g1.NumOfEdges() < g2.NumOfEdges())
        {
            return -1;
        }
        if (g1.NumOfVertices() > g2.NumOfVertices())
        {
            return 1;
        }
        if (g1.NumOfVertices() < g2.NumOfVertices())
        {
            return -1;
        }
        return 0;
    }

    bool Graph::operator>(const Graph &other) const
    {
        return compare(*this, other) == 1;
    }

    bool Graph::operator<(const Graph &other) const
    {
        return compare(*this, other) == -1;
    }

    bool Graph::operator>=(const Graph &other) const
    {
        return compare(*this, other) >= 0;
    }

    bool Graph::operator<=(const Graph &other) const
    {
        return compare(*this, other) <= 0;
    }

    std::ostream &operator<<(std::ostream &os, const Graph &g)
    {
        for (size_t i = 0; i < g.size(); i++)
        {
            for (size_t j = 0; j < g.size(); j++)
            {
                os << g.get_edge(i, j) << "\t";
            }
            os << '\n';
        }
        os << '\n';

        return os;
    }
} // namespace ariel