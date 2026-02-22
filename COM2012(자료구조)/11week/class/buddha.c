#include <stdio.h>
#include <stdlib.h>

// 정점을 표현하는 구조체
struct Vertex {
    char data;
    struct Vertex* next;
};

// 그래프를 표현하는 구조체
struct Graph {
    int numVertices;
    struct Vertex** adjLists;
    char* vertices; // 정점 데이터 배열
};

// 정점 추가 함수
void addVertex(struct Graph* graph, char data) {
    graph->vertices[graph->numVertices] = data;

    struct Vertex* vertex = (struct Vertex*) malloc(sizeof(struct Vertex));
    vertex->data = data;
    vertex->next = NULL;

    graph->adjLists[graph->numVertices] = vertex;
    graph->numVertices++;
}

// 간선 추가 함수
void addEdge(struct Graph* graph, int src, int dest) {
    // src에서 dest로의 간선 추가
    struct Vertex* vertex = (struct Vertex*) malloc(sizeof(struct Vertex));
    vertex->data = graph->vertices[dest];
    vertex->next = graph->adjLists[src]->next;
    graph->adjLists[src]->next = vertex;

    // dest에서 src로의 간선 추가 (무방향 그래프일 경우만)
    vertex = (struct Vertex*) malloc(sizeof(struct Vertex));
    vertex->data = graph->vertices[src];
    vertex->next = graph->adjLists[dest]->next;
    graph->adjLists[dest]->next = vertex;
}

// 그래프 출력 함수
void printGraph(struct Graph* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        struct Vertex* current = graph->adjLists[i];
        printf("정점 %c: ", graph->vertices[i]);
        while (current != NULL) {
            printf("%c -> ", current->data);
            current = current->next;
        }
        printf("NULL\n");
    }
}

// 정점 인덱스 찾기 함수
int findVertexIndex(struct Graph* graph, char data) {
    for (int i = 0; i < graph->numVertices; i++) {
        if (graph->vertices[i] == data)
            return i;
    }
    return -1; // 정점을 찾지 못한 경우
}

int main() {
    int initialSize = 10; // 초기 크기
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
    graph->numVertices = 0;
    graph->adjLists = (struct Vertex**) malloc(initialSize * sizeof(struct Vertex*));
    graph->vertices = (char*) malloc(initialSize * sizeof(char));

    // 각 정점에 대한 인접 리스트 초기화
    for (int i = 0; i < initialSize; i++) {
        graph->adjLists[i] = NULL;
    }

    char command;
    char src, dest;

    while (1) {
        printf("Enter command (A: Add vertex, E: Add edge, P: Print graph, Q: Quit): ");
        scanf(" %c", &command);

        switch(command) {
            case 'A':
                printf("Enter vertex data: ");
                scanf(" %c", &src);
                addVertex(graph, src);
                break;
            case 'E':
                printf("Enter source vertex data: ");
                scanf(" %c", &src);
                printf("Enter destination vertex data: ");
                scanf(" %c", &dest);
                int srcIndex = findVertexIndex(graph, src);
                int destIndex = findVertexIndex(graph, dest);
                if (srcIndex == -1 || destIndex == -1) {
                    printf("Invalid vertex data!\n");
                } else {
                    addEdge(graph, srcIndex, destIndex);
                }
                break;
            case 'P':
                printf("Graph:\n");
                printGraph(graph);
                break;
            case 'Q':
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid command!\n");
        }
    }

    return 0;
}