#pragma GCC optimize("O3")
#include <stdio.h>
#include <math.h>
#define ctoi(c) ((int)c - 97)
#define log2(c) ((int)(log((c)) / log(2)))
#define MAXL 200002
#define MAXD 20
#define ALPHA_LEN 26
using namespace std;
 
typedef struct node {
    struct node* child[ALPHA_LEN];
    struct node* ancestor[MAXD];
    struct node* parent;
    int len;
}node;
 
inline node *getNode(node *parent) {
    node *tmp = new (node);
 
    tmp->len = 0;
    for (int i = 0; i < 26; i++)
        tmp->child[i] = NULL;
    tmp->parent = parent;
    return tmp;
}
 
inline void swap(int *a, int *b) {
    (*a) ^= (*b);
    (*b) ^= (*a);
    (*a) ^= (*b);
}
 
inline void putAncestor(node* address[], int line) {
	int maxLevel = log2(address[line]->len);

	address[line]->ancestor[0] = address[line]->parent;
	for (int i = 1; i <= maxLevel; i++)
		address[line]->ancestor[i] = address[line]->ancestor[i - 1]->ancestor[i - 1];
}
 
inline void insert(node* root, node* address[], int line, int index, char in) {
    if (index == 0) {
        if (root->child[ctoi(in)] == NULL) {
            address[line] = getNode(root);
            address[line]->len = 1;
            root->child[ctoi(in)] = address[line];
            address[line]->ancestor[0] = root;
        }
        else
            address[line] = root->child[ctoi(in)];
    }
    else {
        if (address[index]->child[ctoi(in)] == NULL) {
            address[line] = getNode(address[index]);
            address[line]->len = address[index]->len + 1;
            address[index]->child[ctoi(in)] = address[line];
            putAncestor(address, line);
        }
        else
            address[line] = address[index]->child[ctoi(in)];
    }
}
 
inline int lca(node *ptr1, node *ptr2) {
    if (ptr1 == ptr2)
        return ptr1->len;
    if (ptr1->len > ptr2->len) {
        int maxLevel = log2(ptr1->len - ptr2->len);
        for (int i = maxLevel; i >= 0; i--) {
            if (ptr2->len <= ptr1->len - (1 << i))
                ptr1 = ptr1->ancestor[i];
        }
    }
 
    if (ptr1 == ptr2)
        return ptr1->len;
 
    int MaxLevel = log2(ptr1->len);
    for (int i = MaxLevel; i >= 0; i--) {
        if (ptr1->ancestor[i] != ptr2->ancestor[i]) {
            ptr1 = ptr1->ancestor[i];
            ptr2 = ptr2->ancestor[i];
        }
    }
    return ptr1->len - 1;
}
 
int main() {
    int n, q, index, id1, id2;
    char in;
    node *root = getNode(NULL);
    node* address[MAXL];
 
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d %c", &index, &in);
        insert(root, address, i, index, in);
    }
 
    scanf("%d", &q);
    for (int i = 0; i < q; i++) {
        scanf("%d%d", &id1, &id2);
        if (address[id2]->len > address[id1]->len)
            swap(&id1, &id2);
        printf("%d\n", lca(address[id1], address[id2]));
    }
    return 0;
}
