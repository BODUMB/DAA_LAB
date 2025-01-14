#include <stdio.h>
#include <stdlib.h>

int comparator(const void *a, const void *b)
{
    return ((int *)a)[2] - ((int *)b)[2];
}

int findParent(int parent[], int node)
{
    return (parent[node] == node) ? node : (parent[node] = findParent(parent, parent[node]));
}

void unionSet(int u, int v, int parent[], int rank[])
{
    u = findParent(parent, u);
    v = findParent(parent, v);
    if (rank[u] < rank[v])
        parent[u] = v;
    else if (rank[u] > rank[v])
        parent[v] = u;
    else
        parent[v] = u, rank[u]++;
}

void kruskalAlgo(int n, int edge[][3], int edgesCount)
{
    qsort(edge, edgesCount, sizeof(edge[0]), comparator);

    int parent[n], rank[n], minCost = 0;
    for (int i = 0; i < n; i++)
        parent[i] = i, rank[i] = 0;

    printf("Edges in the constructed MST:\n");
    for (int i = 0; i < edgesCount; i++)
    {
        int u = findParent(parent, edge[i][0]);
        int v = findParent(parent, edge[i][1]);

        if (u != v)
        {
            unionSet(u, v, parent, rank);
            minCost += edge[i][2];
            printf("%d -- %d == %d\n", edge[i][0], edge[i][1], edge[i][2]);
        }
    }
    printf("Minimum Cost Spanning Tree: %d\n", minCost);
}

int main()
{
    int n, edgesCount;

    // Prompt for the number of vertices and edges
    printf("Enter the number of vertices: ");
    scanf("%d", &n);
    printf("Enter the number of edges: ");
    scanf("%d", &edgesCount);

    int edges[edgesCount][3];

    // Prompt for each edge
    printf("Enter each edge in the format (u v weight):\n");
    for (int i = 0; i < edgesCount; i++)
    {
        printf("Edge %d: ", i + 1);
        scanf("%d %d %d", &edges[i][0], &edges[i][1], &edges[i][2]);
    }

    kruskalAlgo(n, edges, edgesCount);

    return 0;
}