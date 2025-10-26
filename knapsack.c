#include <stdio.h>

#include <stdlib.h>

// Structure for an item

typedef struct
{

    int value, weight;

    float ratio;

} Item;

// Structure for a node in the Branch and Bound tree

typedef struct Node
{

    int level;

    int profit;

    int weight;

    float bound; // Cost estimate (fractional)

    float ubound; // Upper bound (non-fractional)

} Node;

// Function to compare items by ratio (descending order)

int cmp(const void *a, const void *b)
{

    Item *i1 = (Item *)a;

    Item *i2 = (Item *)b;

    if (i2->ratio > i1->ratio)
        return 1;

    else if (i2->ratio < i1->ratio)
        return -1;

    else
        return 0;
}

// Function to calculate cost (fractional bound)

float costBound(Node node, int n, int C, Item items[])
{

    int i = node.level;

    int totWeight = node.weight;

    float result = node.profit;

    // Add full items until capacity reached

    while (i < n && totWeight + items[i].weight <= C)
    {

        totWeight += items[i].weight;

        result += items[i].value;

        i++;
    }

    // Add fractional part of next item

    if (i < n)

        result += (C - totWeight) * items[i].ratio;

    return result;
}

// Function to calculate upper bound (non-fractional)

float upperBound(Node node, int n, int C, Item items[])
{

    int i = node.level;

    int totWeight = node.weight;

    float result = node.profit;

    while (i < n && totWeight + items[i].weight <= C)
    {

        totWeight += items[i].weight;

        result += items[i].value;

        i++;
    }

    return result;
}

int max(int a, int b) { return (a > b) ? a : b; }

int main()
{

    int n, C;

    printf("Enter number of items: ");

    scanf("%d", &n);

    Item items[n];

    printf("Enter values and weights of items:\n");

    for (int i = 0; i < n; i++)
    {

        printf("Item %d (value weight): ", i + 1);

        scanf("%d %d", &items[i].value, &items[i].weight);

        items[i].ratio = (float)items[i].value / items[i].weight;
    }

    printf("Enter knapsack capacity: ");

    scanf("%d", &C);

    // Sort items by decreasing value/weight ratio

    qsort(items, n, sizeof(Item), cmp);

    // Initialize

    int bestProfit = 0;

    // Simple array-based queue

    Node queue[1000];

    int front = 0, rear = 0;

    Node u, v;

    v.level = 0;

    v.profit = 0;

    v.weight = 0;

    v.bound = costBound(v, n, C, items);

    v.ubound = upperBound(v, n, C, items);

    queue[rear++] = v;

    while (front < rear)
    {

        v = queue[front++]; // dequeue

        if (v.level == n)
            continue;

        // Left child (include current item)

        u.level = v.level + 1;

        u.weight = v.weight + items[v.level].weight;

        u.profit = v.profit + items[v.level].value;

        if (u.weight <= C && u.profit > bestProfit)

            bestProfit = u.profit;

        u.bound = costBound(u, n, C, items);

        u.ubound = upperBound(u, n, C, items);

        if (u.bound > bestProfit)

            queue[rear++] = u;

        // Right child (exclude current item)

        u.weight = v.weight;

        u.profit = v.profit;

        u.level = v.level + 1;

        u.bound = costBound(u, n, C, items);

        u.ubound = upperBound(u, n, C, items);

        if (u.bound > bestProfit)

            queue[rear++] = u;
    }

    printf("\nMaximum Profit = %d\n", bestProfit);

    return 0;
}