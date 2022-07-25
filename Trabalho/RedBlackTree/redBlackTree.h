enum coloring {red, black};
typedef enum coloring coloring;

typedef struct Node node;
struct Node {
    node *father;
    node *left;
    node *right;
    coloring color;
    int number;
};

typedef struct RedBlackTree tree;
struct RedBlackTree {
    node *firstRoot;
    node *nullRoot;
};

int countSteps;

// Regras da árvore rubro negra:
// 1. Todo nó é vermelho ou preto
// 2. O nó raiz sempre será preto
// 3. Todo nó folha é preto
// 4. Se um nó é vermelho então ambos os seus filhos são pretos
// 5. Todos os caminhos de um nó até cada uma das suas folhas possui a mesma quantidade de nós pretos

void rotateLeft(tree *RB, node *root);
void rotateRight(tree *RB, node *root);
void balance(tree *RB, node *root);
void balanceDeleted(tree *RB, node *root);
void printTree(tree *RB, node *root);
void addNode(tree *RB, int number);
void removeNode(tree *RB, int oldNumber);
void mantainTreeRoot(tree *RB);
node *auxRemoveNode(tree *RB, node *son);
node *createNode(tree *RB, node *father, int number);
tree *createTree();
node *searchNode(tree *RB, node *root, int number);
node *recolor(node *root);
node *grandFather(tree *RB, node *root);
node *uncle(tree *RB, node *root);
node *brother(tree *RB, node *root);

