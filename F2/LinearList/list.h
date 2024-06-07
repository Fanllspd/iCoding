struct _lnklist
{
    int data;
    struct _lnklist *next;
};

typedef struct _lnklist Node;
typedef struct _lnklist *LinkList;

struct _seqlist
{
    int elem[1000];
    int last;
};
typedef struct _seqlist SeqList;