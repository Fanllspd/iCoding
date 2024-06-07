#include <stdio.h>
#include "graph.h" // 请不要删除，否则检查不通过

/**
 * 邻接矩阵

试在邻接矩阵存储结构上实现图的基本操作 matrix_insert_vertex 和matrix_insert_arc，相关定义如下：

typedef int VertexType;

typedef enum{
    DG, UDG
}GraphType;

typedef struct{
    VertexType vertex[MAX_VERTEX_NUM]; //顶点向量
    int arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; //邻接矩阵
    int vexnum, arcnum;   //图的当前顶点数和弧数
    GraphType type;     //图的种类标志
}MatrixGraph;

int matrix_locate_vertex(MatrixGraph *MG, VertexType vex); //返回顶点 v 在vertex数组中的下标，如果v不存在，返回-1
bool matrix_insert_vertex(MatrixGraph *G, VertexType v);
bool matrix_insert_arc(MatrixGraph *G, VertexType v, VertexType w);
当成功插入顶点或边时，函数返回true，否则（如顶点或边已存在、插入边时顶点v或w不存在）返回false。
*/

int matrix_locate_vertex(MatrixGraph *MG, VertexType vex)
{
    for (int i = 0; i < MG->vexnum; ++i)
    {
        if (MG->vertex[i] == vex)
        {
            return i;
        }
    }
    return -1; // 顶点不存在
}

bool matrix_insert_vertex(MatrixGraph *G, VertexType v)
{
    if (G->vexnum < MAX_VERTEX_NUM)
        if (matrix_locate_vertex(G, v) == -1)
        {
            G->vertex[G->vexnum++] = v;
            for (int i = 0; i < G->vexnum; i++)
                G->arcs[i][G->vexnum - 1] = G->arcs[G->vexnum - 1][i] = 0;

            return true;
        }
    return false;
}

bool matrix_insert_arc(MatrixGraph *G, VertexType v, VertexType w)
{
    int vLoc = matrix_locate_vertex(G, v);
    int wLoc = matrix_locate_vertex(G, w);
    if (vLoc != -1 && wLoc != -1 && G->arcs[vLoc][wLoc] != 1)
    {
        G->arcs[vLoc][wLoc] = 1;
        if (G->type == UDG)
            G->arcs[wLoc][vLoc] = 1;
        G->arcnum++;
        return true;
    }
    return false;
}

void print_graph(MatrixGraph *G)
{
    printf("Vertices: ");
    for (int i = 0; i < G->vexnum; ++i)
    {
        printf("%d ", G->vertex[i]);
    }
    printf("\nAdjacency Matrix:\n");
    for (int i = 0; i < G->vexnum; ++i)
    {
        for (int j = 0; j < G->vexnum; ++j)
        {
            printf("%d ", G->arcs[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, char const *argv[])
{
    MatrixGraph G;
    G.vexnum = 0;
    G.arcnum = 0;
    G.type = UDG; // Change to DG for directed graph

    matrix_insert_vertex(&G, 1);
    matrix_insert_vertex(&G, 2);
    matrix_insert_vertex(&G, 3);
    matrix_insert_vertex(&G, 4);

    matrix_insert_arc(&G, 1, 2);
    matrix_insert_arc(&G, 2, 3);
    matrix_insert_arc(&G, 3, 4);
    matrix_insert_arc(&G, 4, 1);

    print_graph(&G);

    return 0;
}
