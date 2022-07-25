typedef struct Node node;
struct Node{
    int number;
    node *father;
    node *left;
    node *right;
};

typedef struct Tree tree;
struct Tree{
    node *firstRoot; 
};
int countSteps;

void printTree(node *root);
void addNode(tree *RB, int number);
void balance(tree *AVL, node *root);
void balanceUp(tree *AVL, node *root);
void rotateLeft(tree *AVL, node *root);
void rotateRight(tree *AVL, node *root);
node *createNode(node *father, int number);
tree *createTree();
int nodeHeight(node *root);
int isAVL(node *root);