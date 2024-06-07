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

bool del_vertex(ListGraph *G, VertexType v)
{
    int vLoc = locate_vertex(G, v);
    if (vLoc == -1)
        return false;

    for (int i = 0; i < G->vexnum; i++)
    {
        if (i == vLoc)
        {
            // G->vertex[vLoc].data = -1;
            ArcNode *arcNode = G->vertex[vLoc].firstarc;
            while (arcNode)
            {
                ArcNode *temp = arcNode;
                arcNode = arcNode->nextarc;
                free(temp);
                G->arcnum--;
            }
            continue;
        }

        ArcNode *prev = NULL;
        ArcNode *arcNode = G->vertex[i].firstarc;
        while (arcNode)
        {
            if (arcNode->adjvex == vLoc)
            {
                if (prev)
                    prev->nextarc = arcNode->nextarc;
                else
                    G->vertex[i].firstarc = arcNode->nextarc;

                // ArcNode *arcNodeDeleted = arcNode->nextarc;
                // prev->nextarc = arcNode->nextarc;
                free(arcNode);
                G->arcnum--;
                break;
            }
            prev = arcNode;
            arcNode = arcNode->nextarc;
        }
    }

    for (int i = vLoc; i < G->vexnum - 1; i++)
        G->vertex[i] = G->vertex[i + 1];

    G->vexnum--;

    // 更新部分原有节点
    for (int i = 0; i < G->vexnum; i++)
    {
        ArcNode *arcNode = G->vertex[i].firstarc;
        while (arcNode)
        {
            if (arcNode->adjvex > vLoc)
                arcNode->adjvex--;
            arcNode = arcNode->nextarc;
        }
    }

    return true;
}

int main()
{
    // Example usage and test
    ListGraph G;
    init_list_graph(&G, 9);
    int vertexs[] = {62, 26, 57, 46, 31, 74, 81, 97, 54, 6};
    for (int i = 0; i < sizeof(vertexs) / sizeof(int); i++)
    {
        insert_vertex(&G, vertexs[i]);
    }

    insert_arc(&G, 62, 54);
    insert_arc(&G, 26, 62);
    insert_arc(&G, 31, 62);
    insert_arc(&G, 74, 26);
    insert_arc(&G, 81, 26);
    // insert_arc(&G, 53, 32);
    // insert_arc(&G, 81, 53);
    // insert_arc(&G, 62, 37);
    del_vertex(&G, 97);

    // Print graph to verify
    for (int i = 0; i < G.vexnum; ++i)
    {
        printf("Vertex %d:", G.vertex[i].data);
        ArcNode *arc = G.vertex[i].firstarc;
        while (arc)
        {
            printf(" -> %d", G.vertex[arc->adjvex].data);
            arc = arc->nextarc;
        }
        printf("\n");
    }

    return 0;
}