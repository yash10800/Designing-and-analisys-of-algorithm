#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define N 100000

struct data {
    int v, weight;
};

struct data pq[N];
int n, m, size;
int **mat;

void swap(struct data *a, struct data *b) {
    struct data other = *a;
    *a = *b;
    *b = other;
}

void push(struct data d) {
    int idx = size;
    pq[idx] = d;
    size++;
    while (idx > 0) {
        int parInd = (idx - 1) / 2;
        if (pq[parInd].weight > pq[idx].weight) {
            swap(&pq[parInd], &pq[idx]);
            idx = parInd;
        }
        else {
            break;
        }
    }
}

struct data pop() {
    struct data ret = pq[0];
    swap(&pq[0], &pq[size - 1]);
    size--;
    int idx = 0;
    while (true) {
        int lchild = 2 * idx + 1;
        int rchild = lchild + 1;
        int curr = idx;
        if (lchild <= size && pq[lchild].weight < pq[curr].weight) {
            curr = lchild;
        }
        if (rchild <= size && pq[rchild].weight < pq[curr].weight) {
            curr = rchild;
        }
        if (curr != idx) {
            idx = curr;
        }
        else {
            break;
        }
    }
    return ret;
}

//n = No of. nodes
//m = No. of Edges

int main() {
    scanf("%d %d", &n, &m);
    mat = (int **)malloc(sizeof(int *) * (n + 1));
    for (int i = 0; i < n + 1; i++) {
      mat[i] = (int *)malloc(sizeof(int) * (n + 1));
      for (int j = 0; j < n + 1; j++) {
        mat[i][j] = N;
      }
    }
    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        mat[u][v] = w;
        mat[v][u] = w;
    }
    int *visited, *source, *dist;
    visited = (int *)malloc(sizeof(int) * (n + 5));
    source = (int *)malloc(sizeof(int) * (n + 5));
    dist = (int *)malloc(sizeof(int) * (n + 5));
    for (int i = 0; i < n + 5; i++) {
        visited[i] = 0;
        dist[i] = N;
        source[i] = -1;
    }

    int take = 0;
    struct data d;
    d.v = 1, d.weight = 0;
    push(d);
    dist[1] = 0;
    while (size > 0) {
        struct data curr = pop();
        int u = curr.v, len = curr.weight;
        visited[u] = 1;
        for (int i = 1; i <= n; i++) {
            if (u == i) continue;
            if (!visited[i] && mat[u][i] < dist[i]) {
                dist[i] = mat[u][i];
                source[i] = u;
                struct data now;
                now.v = i, now.weight = dist[i];
                push(now);
            }
        }
    }
    printf("Edges of Spanning Tree :- \n");
    for (int i = 0; i < n + 1; i++) {
        if (source[i] == -1)    continue;
        printf("%d -> %d\n", source[i], i);
    }

}
/*
5 5
1 2 2
1 3 2
2 4 5
4 5 5
3 5 3
*/

/*
5 7
1 2 2
1 4 6
2 3 3
2 4 8
2 5 5
3 5 7
4 5 9*/
