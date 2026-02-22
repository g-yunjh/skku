#include "graph.h"
#include <stdio.h>

int main ()
{
    GraphType *my_graph;
    my_graph=(GraphType*)malloc(sizeof(GraphType));

    while(1){
        char command;
        char data, data1;


        scanf("%c", &command);
        switch (command)
        {
            case 'G':
                create(my_graph);
                break;
            case '+':
                scanf(" %c", &data);
                insert_vertex(my_graph, data);
                print(my_graph);
                break;
            case 'E':
                scanf(" (%c,%c)", &data, &data1);
                add_edge(my_graph, data, data1);
                print(my_graph);
                break;
            case 'L':
                print(my_graph);
                break;
            case 'V':
                scanf(" (%c)", &data);
                printf("%d\n", degree_of_vertex(my_graph, data));
                break;
            case 'C':
                is_connected(my_graph);
                break;
            case 'N':
                is_empty(my_graph);
                break;
            case 'A':
                scanf(" (%c)", &data);
                adjacent(my_graph, data);
                break;
            case '-':
                scanf(" %c", &data);
                delete_vertex(my_graph, data);
                print(my_graph);
                break;
            case 'P':
                scanf(" (%c,%c)", &data, &data1);
                path_exist(my_graph, data, data1);
                break;
            case 'X':
                printf("%d\n", num_of_vertex(my_graph));
                break;
            case 'H':
                printf("%d\n", num_of_edge(my_graph));
                break;
            case 'D':
                scanf(" (%c,%c)", &data, &data1);
                delete_edge(my_graph, data, data1);
                print(my_graph);
                break;
            case 'R':
                scanf(" (%c, %c)", &data, &data1);
                rename_vertex(my_graph, data, data1);
                print(my_graph);
                break;
            case 'K':
                clear(my_graph);
                print(my_graph);
                break;
            case 'Q':
                return 0;
        }
    }
}