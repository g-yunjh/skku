#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_VERTICES 26  // 알파벳은 26개

typedef struct GraphNode {
    char vertex;
    struct GraphNode* link;
} GraphNode;

typedef struct GraphType {
    int n;
    char vertices[MAX_VERTICES];
    GraphNode* adj_list[MAX_VERTICES];
} GraphType;

void create(GraphType* g) {
    g->n = 0;
    for (int v = 0; v < MAX_VERTICES; v++) {
        g->vertices[v] = '\0';
        g->adj_list[v] = NULL;
    }
}

void insert_vertex(GraphType* g, char v) {
    if (g->n >= MAX_VERTICES) {
        fprintf(stderr, "overflow\n");
        return;
    }
    g->vertices[g->n] = v;
    g->n++;
}

int get_vertex_index(GraphType* g, char v) {
    for (int i = 0; i < g->n; i++) {
        if (g->vertices[i] == v) {
            return i;
        }
    }
    return -1;
}

void add_edge(GraphType* g, char u, char v) {
    int idx_u = get_vertex_index(g, u);
    int idx_v = get_vertex_index(g, v);

    if (idx_u == -1 || idx_v == -1) {
        fprintf(stderr, "vertex not found\n");
        return;
    }

    // 출발 정점에 대한 간선 추가
    GraphNode* node_uv = (GraphNode*)malloc(sizeof(GraphNode));
    node_uv->vertex = v;
    node_uv->link = NULL;
    if (g->adj_list[idx_u] == NULL) {
        g->adj_list[idx_u] = node_uv;
    } else {
        GraphNode* p = g->adj_list[idx_u];
        while (p->link != NULL) {
            p = p->link;
        }
        p->link = node_uv;
    }

    // 도착 정점에 대한 간선 추가
    GraphNode* node_vu = (GraphNode*)malloc(sizeof(GraphNode));
    node_vu->vertex = u;
    node_vu->link = NULL;
    if (g->adj_list[idx_v] == NULL) {
        g->adj_list[idx_v] = node_vu;
    } else {
        GraphNode* p = g->adj_list[idx_v];
        while (p->link != NULL) {
            p = p->link;
        }
        p->link = node_vu;
    }
}

void print(GraphType* g) {
    printf("(");
    for (int i = 0; i < g->n; i++) {
        printf("%c", g->vertices[i]);
        GraphNode* p = g->adj_list[i];
        if (p != NULL) {
            printf("(");
            printf("%c", p->vertex);
            p = p->link;
            while (p != NULL) {
                printf(",%c", p->vertex);
                p = p->link;
            }
            printf(")");
        }
        if (i < g->n - 1) {
            printf(",");
        }
    }
    printf(")\n");
}

void path_exist(GraphType* g, char u, char v) {
    int idx_u = get_vertex_index(g, u);
    int idx_v = get_vertex_index(g, v);
    bool exists = false;

    if (idx_u == -1 || idx_v == -1) {
        fprintf(stderr, "vertex not found\n");
        printf("False\n");
        return;
    }

    bool visited[MAX_VERTICES] = {false};
    int queue[MAX_VERTICES];
    int front = 0, rear = 0;

    queue[rear++] = idx_u;
    visited[idx_u] = true;

    while (front < rear) {
        int current = queue[front++];
        GraphNode* p = g->adj_list[current];
        while (p != NULL) {
            int neighbor = get_vertex_index(g, p->vertex);
            if (neighbor == idx_v) {
                exists = true; // 경로 발견
                break;
            }
            if (!visited[neighbor]) {
                queue[rear++] = neighbor;
                visited[neighbor] = true;
            }
            p = p->link;
        }
        if (exists) {
            break; // 경로 발견 시 종료
        }
    }

    printf("%s\n", exists ? "True" : "False");
}

int degree_of_vertex(GraphType* g, char v) {
    int idx_v = get_vertex_index(g, v);
    if (idx_v == -1) {
        fprintf(stderr, "vertex not found\n");
        return -1;
    }
    GraphNode* p = g->adj_list[idx_v];
    int degree = 0;
    while (p != NULL) {
        degree++;
        p = p->link;
    }
    return degree;
}

void is_connected(GraphType* g) {
    for (int i = 0; i < g->n; i++) {
        GraphNode* p = g->adj_list[i];
        if (p == NULL) {
            printf("False\n");
            return;
        }
    }
    printf("True\n");
}

void is_empty(GraphType* g) {
    if (g->n == 0)
        printf("True\n");
    else
        printf("False\n");
}

void adjacent(GraphType* g, char v) {
    int idx_v = get_vertex_index(g, v);
    if (idx_v == -1) {
        fprintf(stderr, "vertex not found\n");
        return;
    }
    GraphNode* p = g->adj_list[idx_v];
    while (p != NULL) {
        printf("%c ", p->vertex);
        p = p->link;
    }
    printf("\n");
}

void delete_edge(GraphType* g, char u, char v) {
    int idx_u = get_vertex_index(g, u);
    int idx_v = get_vertex_index(g, v);

    if (idx_u == -1 || idx_v == -1) {
        fprintf(stderr, "vertex not found\n");
        return;
    }

    GraphNode* p = g->adj_list[idx_u];
    GraphNode* prev = NULL;
    while (p != NULL && p->vertex != v) {
        prev = p;
        p = p->link;
    }
    if (p == NULL) {
        fprintf(stderr, "no edge between %c and %c\n", u, v);
        return;
    }
    if (prev == NULL)
        g->adj_list[idx_u] = p->link;
    else
        prev->link = p->link;
    free(p);

    p = g->adj_list[idx_v];
    prev = NULL;
    while (p != NULL && p->vertex != u) {
        prev = p;
        p = p->link;
    }
    if (p == NULL) {
        fprintf(stderr, "no edge between %c and %c\n", v, u);
        return;
    }
    if (prev == NULL)
        g->adj_list[idx_v] = p->link;
    else
        prev->link = p->link;
    free(p);
}

void delete_vertex(GraphType* g, char v) {
    int idx_v = get_vertex_index(g, v);
    if (idx_v == -1) {
        fprintf(stderr, "vertex not found\n");
        return;
    }

    GraphNode* p = g->adj_list[idx_v];
    while (p != NULL) {
        char connected_vertex = p->vertex;
        delete_edge(g, v, connected_vertex);
        p = g->adj_list[idx_v];
    }

    g->adj_list[idx_v] = NULL;

    for (int i = idx_v; i < g->n - 1; i++) {
        g->vertices[i] = g->vertices[i + 1];
        g->adj_list[i] = g->adj_list[i + 1];
    }
    g->vertices[g->n - 1] = '\0';
    g->adj_list[g->n - 1] = NULL;
    g->n--;
}

int num_of_vertex(GraphType* g) {
    return g->n;
}

int num_of_edge(GraphType* g) {
    int num = 0;
    for (int i = 0; i < g->n; i++) {
        GraphNode* p = g->adj_list[i];
        while (p != NULL) {
            num++;
            p = p->link;
        }
    }
    return num / 2;
}

//function to rename the vertex
void rename_vertex(GraphType* g, char old_name, char new_name) {
    int idx_old = get_vertex_index(g, old_name);

    if (idx_old == -1) {
        fprintf(stderr, "vertex not found\n");
        return;
    }

    // 이름을 변경
    g->vertices[idx_old] = new_name;

    // 인접 리스트에서 old_name을 new_name으로 변경
    for (int i = 0; i < g->n; i++) {
        GraphNode* p = g->adj_list[i];
        while (p != NULL) {
            if (p->vertex == old_name) {
                p->vertex = new_name;
            }
            p = p->link;
        }
    }
}

void clear(GraphType* g) {
    for (int i = 0; i < g->n; i++) {
        GraphNode* p = g->adj_list[i];
        while (p != NULL) {
            GraphNode* tmp = p;
            p = p->link;
            free(tmp);
        }
        g->adj_list[i] = NULL;
    }
    g->n = 0;
    for (int v = 0; v < MAX_VERTICES; v++) {
        g->vertices[v] = '\0';
    }
}