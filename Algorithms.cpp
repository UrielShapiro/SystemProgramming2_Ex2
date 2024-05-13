#include "Graph.hpp"
#include <vector>
#include <string>
#include <queue>    // For the BFS algorithm.
#include <climits>  // For INT_MAX
#include <iostream>
#include <algorithm> // For the find function.
#include "Algorithms.hpp"
using ariel::Graph;

#define INFINITY INT_MAX
// #define DEBUG

namespace ariel
{
    /*
     * A function that finds the neighbor with the minimum distance from the source.
     * @return The index of the neighbor with the minimum distance from the source.
     */
    size_t Algorithms::min_neighbor(const std::vector<int> &dist, const std::vector<bool> &converged)
    {
        int min = INFINITY;
        size_t min_index = 0; // Initializing it to 0 to avoid any errors when returning (uninitialized value otherwise).

        for (size_t vertex_i = 0; vertex_i < dist.size(); vertex_i++) // Looping through the vertices
        {
            if (converged[vertex_i] == false && dist[vertex_i] < min) // If the neighbor was not visited yet and the distance
            // from the source is less or equal to the minimum distance.
            // This is the neighbor with the current minimum distance from the source.
            {
                min = dist[vertex_i]; // The unvisited neighbor with the minimum distance from the source is stored in min.
                min_index = vertex_i; // Updating min_index to the index of the neighbor with the minimum distance from the source.
            }
        }
#ifdef DEBUG
        std::cout << "The min index is: " << min_index << std::endl;
#endif
        return min_index; // Returning the index of the neighbor with the minimum distance from the source.
    }

    /*
     * A function that checks if a vertex should be relaxed or not.
     * @return True if the vertex should be relaxed, False otherwise.
     */
    bool Algorithms::should_relax(size_t u, size_t v, int weight, std::vector<int> dist)
    {
        // If the vertex was visited (it's distance from the origin was updated)
        // and the distance from the origin to that vertex from the path through vertex u is shorter than the current distance
        // found from the origin to vertex v, then the vertex should be relaxed.
        if (dist[u] != INFINITY && dist[u] + weight <= dist[v])
        {
            return true;
        }
        return false;
    }

    /*
     * Function that implements Dijkstra's single source shortest path algorithm
     * for a graph represented using adjacency matrix
     * @return A vector that stores the shortest distance from the source to each vertex in the graph.
     */
    void Algorithms::dijkstra(Graph g, size_t src, size_t end, std::vector<int> &dist, std::vector<size_t> &parents)
    {
        std::vector<bool> converged(g.size(), false); // converged[i] will be true if vertex i is included in shortest path tree
                                                 // or shortest distance from src to i is finalized

        dist[src] = 0;         // Distance of source vertex from itself is always 0
        converged[src] = true; // Mark the source vertex as converged
        // Find shortest path from src to all vertices
        for (size_t count = 0; count < g.size() - 1; count++)
        {
            // Pick the minimum distance vertex from the set of vertices not yet processed.
            size_t u = min_neighbor(dist, converged);
            converged[u] = true;

            // Update distance value of the adjacent vertices of the picked vertex. (Relaxation step)
            for (size_t v = 0; v < g.size(); v++)
            {
                if (v == u)
                {
                    continue;
                }
#ifdef DEBUG
                std::cout << "Checking edge: " << u << " -> " << v << std::endl;
#endif
                // Update dist[v] only if not converged yet,
                // and there is an edge from u to v (graph[u][v] != 0),
                // and that vertex should relax (using the should_relax function)
                if (!converged[v] && g.get_edge(u, v) != 0 && should_relax(u, v, g.get_edge(u, v), dist))
                {
#ifdef DEBUG
                    std::cout << "Will set the parent of " << v << " to be: " << u << std::endl;
#endif
                    parents[v] = u;
                    dist[v] = dist[u] + g.get_edge(u, v);
                }
            }
        }
    }
    /*
     * This function relaxes the edge between two nodes in the graph.
     * If the distance from the source node to the current node is shorter than the current distance,
     * the function will update the distance to the new shorter distance (in the distance vector).
     * @return true if the distance was updated, false otherwise.
     */
    bool Algorithms::relax(Graph g, size_t v, size_t u, std::vector<int> &distances, std::vector<size_t> &parents)
    {
        if (distances[u] == INFINITY)
        {
            return false;
        }
        else if (distances[u] + g.get_edge(u, v) < distances[v])
        {
            distances[v] = distances[u] + g.get_edge(u, v);
            parents[v] = u; // We assume the graph is directed, so the parent of v is u.

#ifdef DEBUG
            std::cout << "Relaxing edge: " << u << " -> " << v << std::endl;
            std::cout << "The new distance from " << u << " to " << v << " is: " << distances.at(v) << std::endl;
#endif
            return true;
        }
        return false;
    }
    /*
        * This function implements the Bellman-Ford algorithm to find the shortest path in a graph.
        * @return True if the graph contains a negative cycle, False otherwise.
    */
    bool Algorithms::BellmanFord(Graph g, size_t src, std::vector<int> &dist, std::vector<size_t> &parents, std::vector<size_t> &cycleNodes)
    {
        dist[src] = 0; // The distance from the start node to itself is 0.
        parents[src] = INFINITY;
        if (g.size() == 1)
        {
            return false;
        }
        for (size_t times = 0; times < g.size() - 1; times++)
        {
            for (size_t i = 0; i < g.size(); i++)
            {
                for (size_t j = 0; j < g.size(); j++)
                {
                    if (g.get_edge(i, j) != 0)
                    {
                        relax(g, j, i, dist, parents);
                    }
                }
            }
        }

        // Check for negative weight cycle.
        for (size_t i = 0; i < g.size(); i++)
        {
            for (size_t j = 0; j < g.size(); j++)
            {
#ifdef DEBUG
                if (g.get_edge(i, j) != 0)
                {
                    std::cout << "Checking edge: " << i << " -> " << j << std::endl;
                    std::cout << "The edge weight is: " << g.get_edge(i, j) << std::endl;
                }
#endif
                if (g.get_edge(i, j) != 0 && (parents[j] != i && !g.isDirectedGraph()) && relax(g, j, i, dist, parents))
                {
#ifdef DEBUG
                    std:: << "Negative cycle found" << std::endl;
                    std::cout << "The cycle is: " << i << " -> " << j << std::endl;
                    std::cout << "Parents: ";
                    for (size_t p : parents)
                    {
                        std::cout << p << " ";
                    }
                    std::cout << std::endl;
#endif
                    // The nodes in which the cycle starts and ends are stored in the cycleNodes vector.
                    cycleNodes.push_back(i);
                    cycleNodes.push_back(j);
                    return true; // The graph contains a negative cycle.
                }
            }
        }
#ifdef DEBUG
        std::cout << "There is no negative cycle" << std::endl;
#endif
        return false;
    }


    /*
        * This function performs a Depth First Search (DFS) on the graph to check connactivity.
        * This function is used to check if the graph is strongly connected (1 SCC).
    */
    void Algorithms::DFS(Graph g, size_t current, size_t parent, std::vector<bool> &visited,
                         std::vector<bool> &inStack)
    {
#ifdef DEBUG
        std::cout << "Running DFS with: " << current << std::endl;
#endif
        visited[current] = true;
        inStack[current] = true;

        for (size_t neighbor = 0; neighbor < g.at(current).size(); neighbor++)
        {
            if (!g.isDirectedGraph() && neighbor == parent) // Skip the parent node in undirected graphs.
            {
#ifdef DEBUG
                std::cout << "The graph is directed" << std::endl;
#endif
                continue;
            }
            if (neighbor == current)
            {
                continue;   // Skip the current node - small runtime improvement.
            }
            if (!visited[neighbor] && g.get_edge(neighbor, current) != 0)
            {
#ifdef DEBUG
                std::cout << "Running DFS from " << neighbor << ". His parent is: " << current << std::endl;
#endif
                DFS(g, neighbor, current, visited, inStack);
            }
        }
        inStack[current] = false;   // Remove the current node from the stack.
    }


    /*
        * This function performs a Depth First Search (DFS) on the graph.
        * It is used to check if the graph contains a cycle.
        * @return The node in which the cycle starts.
    */
    size_t Algorithms::DFSCycleCheck(Graph g, size_t current, size_t parent, std::vector<Visited> &visited,
                         std::vector<size_t> &parents, std::vector<size_t> &cycleNodes)
    {
#ifdef DEBUG
        std::cout << "Running DFSCycleCheck with: " << current << std::endl;
#endif

        visited[current] = GREY;    // Mark the current node as "in-work".
        parents[current] = parent;
        cycleNodes.push_back(current);

        for (size_t neighbor = 0; neighbor < g.at(current).size(); neighbor++)
        {
            if (!g.isDirectedGraph() && (neighbor == parent || parents[neighbor] == current)) // Skip the parent node in undirected graphs.
            {
                continue;
            }
            if (visited[neighbor] == GREY && g.get_edge(neighbor, current) != 0)
            {
#ifdef DEBUG
                std::cout << "The cycle is: " << current << "->" << neighbor << std::endl;
#endif
                parents[neighbor] = current;
                cycleNodes.push_back(neighbor);
                return current;
            }
            else if (visited[neighbor] == WHITE && g.get_edge(neighbor, current) != 0)
            {
#ifdef DEBUG
                std::cout << "Running DFSCycleCheck from " << neighbor << ". His parent is: " << current << std::endl;
#endif
                parents[neighbor] = current;
                if (DFSCycleCheck(g, neighbor, current, visited, parents, cycleNodes) != INFINITY)
                {
                    return current; // Return the node in which the cycle starts.
                }
            }
        }
        visited[current] = BLACK;   // Mark the current node as "done".
        cycleNodes.pop_back();      // Remove the current node from the cycleNodes vector (because a cycle was not found).
        return INFINITY;            // Return INFINITY if no cycle was found.
    }

    /*
        * This function colors the graph using the Breadth First Search (BFS) algorithm.
        * The function colors the graph in two colors (RED and BLUE) and checks if the graph is bipartite.
        * Theorom: A graph is bipartite if and only if it is 2-colorable.
        * @return True if the graph is bipartite, False otherwise.
    */
    bool Algorithms::BFSColoring(Graph g, size_t start, std::vector<Color> &colors)
    {
        std::queue<size_t> Q;
        Q.push(start); 
        colors[start] = RED;

        while (!Q.empty())      // Running the BFS algorithm while the queue is not empty.
        {
            size_t current = Q.front();
            Q.pop();

            for (size_t i = 0; i < g.size(); i++)
            {
#ifdef DEBUG
                std::cout << "Checking edge: " << current << " -> " << i << std::endl;
#endif
                if (g.get_edge(current, i) != 0 && colors[i] == UNCOLORED)
                {
                    Q.push(i);                                          // Push the neighbor to the queue.
                    colors[i] = colors[current] == RED ? BLUE : RED;    // Color the neighbor with the opposite color.
#ifdef DEBUG
                    std::cout << "Coloring node: " << i << " with: " << colors[i] << std::endl;
#endif
                }
                if (i != current && g.get_edge(current, i) != 0 && colors[i] == colors[current])
                {
#ifdef DEBUG
                    std::cout << "vertex " << i << " color is the same as vertex: " << current << std::endl;
#endif
                    return false;
                }
            }
        }
        return true;
    }

    /*
        * This function prints the path from the source node to the end node.
        * @return The path from the source node to the end node.
    */
    std::string Algorithms::printPath(size_t src, size_t parent, const std::vector<size_t> parents)
    {
        if (parent == src)
        {
            return std::to_string(src);
        }
        else if (parent == INFINITY)
        {
            return "No path";
        }
        return printPath(src, parents[parent], parents) + "->" + std::to_string(parent);
    }

    /*
        * This function checks if the graph is connected.
        * In order to check if the graph is connected and not just strongly connected, the function creates a new undirected graph.
        * And run a Depth First Search (DFS) algorithm on that graph.
        * @return True if the graph is strongly connected, False otherwise.
    */
    bool Algorithms::isConnected(const Graph g)
    {
        if (g.size() == 0 || g.size() == 1)
        {
#ifdef DEBUG
            std::cout << "Empty graph is considered connected" << std::endl;
#endif
            return true;
        }

        std::vector<bool> visited(g.size(), false); // Create a visited array for the graph nodes. initialized to false.
        std::vector<bool> inStack(g.size(), false); // Create a stack array for the graph nodes. initialized to false.
        
        if (g.isDirectedGraph())
        {
#ifdef DEBUG
            std::cout << "The graph is directed" << std::endl;
#endif
            Graph undirectedGraph = Graph::MakeUndirectedGraph(g);   // Create an undirected graph to check if the graph is connected.
            DFS(undirectedGraph, 0, INFINITY, visited, inStack); // Check if start is connected to end.
        }
        else
        {
            DFS(g, 0, INFINITY, visited, inStack); // Check if start is connected to end.
        }
        
        auto iter = find(visited.begin(), visited.end(), false);
        if (iter != visited.end()) // The iterator found a false value in the visited array.
        {
            return false; // The graph is not connected.
        }
        return true; // The graph is connected if all nodes are visited
    }


    /*
        * This function finds the shortest path between two nodes in the graph.
        * If the graph has no negative edges, The function uses Dijkstra's algorithm to find the shortest path.
        * Else, the function uses the Bellman-Ford algorithm to find the shortest path.
        * @return The shortest path between the start and end nodes. if there is no path, the function returns -1.
    */
    std::string Algorithms::shortestPath(const Graph g, const size_t start, const size_t end)
    {
        if (start == end)
        {
            return "0"; // If the start and end nodes are the same, the path is 0.
        }

        std::vector<bool> visited(g.size(), false);
        std::vector<bool> inStack(g.size(), false);
        
        if (g.isDirectedGraph())
        {
#ifdef DEBUG
            std::cout << "The graph is directed" << std::endl;
#endif
            Graph undirectedGraph = Graph::MakeUndirectedGraph(g);   // Create an undirected graph to check if the graph is connected.
            // Is used to check if the start is connected to the end (without needing it to be strongly connected).
            DFS(undirectedGraph, start, INFINITY, visited, inStack); // Check if start is connected to end.
        }
        else
        {
            DFS(g, start, INFINITY, visited, inStack); // Check if start is connected to end.
        }
        if (!visited[end])
        {
#ifdef DEBUG
            std::cout << "The end node is not connected to the start node" << std::endl;
#endif
            return "-1"; // If the start node is not connected to the end node, return -1.
        }

        std::vector<int> dist(g.size(), INFINITY);       // Initialize all distances to infinity.
        std::vector<size_t> parents(g.size(), INFINITY); // Initialize all parents to infinity.
        std::vector<size_t> cycleNodes;                  // Initialize the cycle nodes vector.

        if (!g.isContainsNegativeEdge())    // If the graph does not contain negative edges, run Dijkstra's algorithm.
        {
#ifdef DEBUG
            std::cout << "Running dijkstra" << std::endl;
#endif

            dijkstra(g, start, end, dist, parents);

#ifdef DEBUG
            std::cout << "Dijkstra finished" << std::endl;
            for (int a : parents)
            {
                std::cout << a << " ";
            }
            std::cout << std::endl;
#endif

            size_t current = end;
            std::string path = std::to_string(end); // Start building the path from the end node.
            while (current != start)
            {
                path = std::to_string(parents[current]) + "->" + path;
                current = parents[current];
#ifdef DEBUG
                std::cout << "Current node: " << current << std::endl;
                std::cout << "The path is: " << path << std::endl;
#endif
            }
            return path;
        }
        else    // If the graph contains negative edges, run the Bellman-Ford algorithm.
        {
            bool negative_cycle = BellmanFord(g, start, dist, parents, cycleNodes); // Run Bellman-Ford algorithm to find the shortest path.

#ifdef DEBUG
            for (size_t i = 0; i < dist.size(); i++)
            {
                std::cout << "Shotest path for vertex: " << i << " is: " << dist.at(i) << endl;
            }
#endif

            if (negative_cycle)
            {
#ifdef DEBUG
                std::cout << "A cycle was found" << endl;
#endif
                return "-1"; // If the graph contains a negative weight cycle, return -1.
            }
        }
#ifdef DEBUG
        std::cout << "There is no negative cycle" << std::endl;
        for (int a : parents)
        {
            std::cout << a << " ";
        }
        std::cout << std::endl;
#endif

        size_t current = end;
        std::string path = std::to_string(end); // Start building the path from the end node.
        while (current != start && parents[current] != INFINITY)
        {
            path = std::to_string(parents[current]) + "->" + path;
            current = parents[current];
#ifdef DEBUG
            std::cout << "Current node: " << current << std::endl;
            std::cout << "The path is: " << path << std::endl;
#endif
        }
        return path;
    }


    /*
        * This function checks if the graph contains a cycle.
        * The function uses Depth First Search (DFS) to check if the graph contains a cycle.
        * @return The cycle in the graph if it contains a cycle, "0" otherwise.
    */
    std::string Algorithms::isContainsCycle(Graph g)
    {
        std::vector<Visited> visited(g.size(), WHITE);   // Create a visited array for the graph nodes. initialized to false.
        std::vector<size_t> parents(g.size(), INFINITY); // Create a stack vector for the graph nodes. initialized to false.
        size_t cycle_node;
        for (size_t i = 0; auto iter = find(visited.begin(), visited.end(), WHITE) != visited.end(); i++)
        {
            if (visited[i] != WHITE)    // Skip the visited nodes.
            {
#ifdef DEBUG
                std::cout << "The node is already visited: " << i << std::endl;
#endif
                continue;
            }

            std::vector<size_t> cycleNodes;
            cycle_node = DFSCycleCheck(g, i, INFINITY, visited, parents, cycleNodes);   
            // DFSCycleCheck returns the node in which the cycle starts.
            
            if (cycle_node != INFINITY)
            {
#ifdef DEBUG
                for (int a : parents)
                {
                    std::cout << a << " ";
                }
                std::cout << std::endl;
#endif
                std::string path = "The cycle is: ";
                path += printPath(cycle_node, parents[cycle_node], parents);
                path += "->" + std::to_string(cycle_node);   // Add the last node in the cycle.
#ifdef DEBUG
                std::cout << path << std::endl;
#endif
                return path;
            }
        }
        return "0"; // If the graph does not contain a cycle, return false.
    }

    /*
        * This function checks if the graph is bipartite.
        * The function uses Breadth First Search (BFS) to color the graph in two colors (RED and BLUE).
        * Theorom: A graph is bipartite if and only if it is 2-colorable.
        * @return The sets of vertices if the graph is bipartite, "0" otherwise.
    */
    std::string Algorithms::isBipartite(Graph g)
    {
        // Create a color vector for the graph nodes. initialized all nodes to UNCOLORED.
        std::vector<Color> colors(g.size(), UNCOLORED);
        for (size_t i = 0; i < g.size(); i++)
        {
            if (colors[i] == UNCOLORED)
            {
                if (!BFSColoring(g, i, colors)) // If the graph is not bipartite, return false.
                {
                    return "0"; // If the graph is not bipartite, return false.
                }
            }
        }

        // If reached here, the graph is bipartite.
        std::string Set_A = "A={";
        std::string Set_B = "B={";
        for (size_t i = 0; i < g.size(); i++)
        {
            if (colors[i] == RED)
            {
                Set_A += std::to_string(i) + ", ";
            }
            else    // If the color is BLUE.
            {
                Set_B += std::to_string(i) + ", ";
            }
        }
        // Remove the last comma and space in both strings:
        Set_A = Set_A.substr(0, Set_A.size() - 2);
        Set_B = Set_B.substr(0, Set_B.size() - 2);
        Set_A += "}";
        Set_B += "}";
        return "The graph is bipartite: " + Set_A + ", " + Set_B;
    }

    /*
        * This function checks if the graph contains a negative cycle.
        * The function won't work on directed graphs that contain a negative cycle.
        * The function uses the Bellman-Ford algorithm to check if the graph contains a negative cycle.
        * @return The cycle in the graph if it contains a negative cycle, "0" otherwise.
    */
    std::string Algorithms::negativeCycle(Graph g)
    {
        if (isContainsCycle(g) == "0" || !g.isContainsNegativeEdge() || g.size() < 3)
        {
            return "The graph does not contain a negative cycle.";
        }

        std::vector<int> distance(g.size(), INFINITY);
        std::vector<size_t> parents(g.size(), INFINITY);
        std::vector<size_t> cycleNodes;

        for (size_t i = 0; i < g.size(); i++)
        {
            if (distance.at(i) == INFINITY) // Checks only unvisited nodes. will work on graphs that are not connected
            {
                if (BellmanFord(g, i, distance, parents, cycleNodes))   // If the graph contains a negative cycle.
                { 
#ifdef DEBUG
                    std::cout << "A cycle was found" << std::endl;
#endif
                    return "The graph contains a negative cycle: " + printPath(cycleNodes[1], cycleNodes[0], parents)
                                                                    + "->" + std::to_string(cycleNodes[1]);
                }
#ifdef DEBUG
                for (int a : distance)
                {
                    std::cout << a << " ";
                }
                std::cout << std::endl;
#endif
            }
        }
        return "The graph does not contain a negative cycle.";
    }
};