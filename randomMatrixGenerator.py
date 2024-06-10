# Last digits of ID: 9745
# Mail: uriel1999@gmail.com

import random

def generate_random_adjacency_matrix(vertices, density):
    adjacency_matrix = [[0] * vertices for _ in range(vertices)]  # Initialize matrix with zeros

    # Fill upper triangular matrix (excluding diagonal) with random connections based on density
    for i in range(vertices):
        for j in range(i + 1, vertices):
            if random.random() < density:
                rand = random.randint(-10, 50)
                adjacency_matrix[i][j] = rand
                adjacency_matrix[j][i] = 0

    return adjacency_matrix

# Example usage:
vertices = random.randint(3,7)  # Number of vertices in the graph
density = 0.8  # Density of connections (probability of two vertices being connected)

random_adjacency_matrix = generate_random_adjacency_matrix(vertices, density)
for row in random_adjacency_matrix:
    print(row)
