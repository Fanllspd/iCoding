#include <stdio.h>
#include <stdlib.h>
#include "graph.h" //请勿删除，否则检查不通过

int locate_vertex(ListGraph *G, VertexType v)
{
    for (int i = 0; i < G->vexnum; ++i)
    {
        if (G->vertex[i].data == v)
        {
            return i;
        }
    }
    return -1;
}

bool insert_vertex(ListGraph *G, VertexType v)
{
    if (G->vexnum < MAX_VERTEX_NUM)
        if (locate_vertex(G, v) == -1)
        {
            VNode newNode = {v, NULL};
            G->vertex[G->vexnum++] = newNode;
            return true;
        }
    return false;
}

bool insert_arc(ListGraph *G, VertexType v, VertexType w)
{
    int vLoc = locate_vertex(G, v);
    int wLoc = locate_vertex(G, w);
    if (vLoc == -1 || wLoc == -1)
        return false;

    ArcNode *vArcNode = G->vertex[vLoc].firstarc;

    while (vArcNode)
    {
        if (vArcNode->adjvex == wLoc)
            return false;
        vArcNode = vArcNode->nextarc; // 检查(v,w)重复
    }
    ArcNode *newNode = (ArcNode *)malloc(sizeof(ArcNode));
    if (newNode == NULL)
        return false;

    newNode->adjvex = wLoc;

    newNode->nextarc = G->vertex[vLoc].firstarc;
    G->vertex[vLoc].firstarc = newNode; // 头插

    // if (G->type == UDG)
    // {
    //     ArcNode *wArcNode = G->vertex[wLoc].firstarc;
    //     while (wArcNode)
    //     {
    //         if (wArcNode->adjvex == vLoc)
    //             return false;
    //         wArcNode = wArcNode->nextarc; // 检查(w,v)重复
    //     }
    //     newNode->adjvex = vLoc;
    //     newNode->nextarc = G->vertex[wLoc].firstarc;
    //     G->vertex[vLoc].firstarc = newNode;
    //     // G->arcnum++;
    // }
    // 貌似不用考虑无向图？
    G->arcnum++;

    return true;
}

void init_list_graph(ListGraph *G, int vertex_count)
{
    G->vexnum = 0;
    G->arcnum = 0;
    for (int i = 0; i < vertex_count; ++i)
    {
        G->vertex[i].data = i + 1; // Assign vertex data, you can customize this
        G->vertex[i].firstarc = NULL;
    }
}
int main()
{
    // Example usage and test
    ListGraph G;
    init_list_graph(&G, 9);
    int vertexs[] = {71, 87, 37, 28, 80, 40, 35, 14, 0};
    for (int i = 0; i < sizeof(vertexs) / sizeof(int); i++)
    {
        insert_vertex(&G, vertexs[i]);
    }

    // insert_arc(&G, 99, 99);
    // insert_arc(&G, 99, 81);
    // insert_arc(&G, 32, 19);
    // insert_arc(&G, 22, 32);
    // insert_arc(&G, 53, 81);
    // insert_arc(&G, 53, 32);
    // insert_arc(&G, 81, 53);
    insert_arc(&G, 14, 37);

    // Print graph to verify
    for (int i = 0; i < G.vexnum; ++i)
    {
        printf("Vertex %d:", G.vertex[i].data);
        ArcNode *arc = G.vertex[i].firstarc;
        while (arc)
        {
            printf(" -> %d", arc->adjvex);
            arc = arc->nextarc;
        }
        printf("\n");
    }

    return 0;
}