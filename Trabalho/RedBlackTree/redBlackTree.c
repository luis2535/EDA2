#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "redBlackTree.h"
int countSteps = 0;


void printTree(tree *RB, node *root){
    if(root == RB->nullRoot) return;

    printf("%i ", root->number);
    
    if(root->color == red) printf("red\n");
    else printf("black\n");
    
    printTree(RB, root->left);
    printTree(RB, root->right);
}

tree *createTree(){
    tree *RB;
    RB = (tree *)malloc(sizeof(tree));
    RB->firstRoot = NULL;
    RB->nullRoot = (node *)malloc(sizeof(node));
    RB->nullRoot->color = black;
    RB->nullRoot->father = RB->nullRoot;
    RB->nullRoot->left = RB->nullRoot;
    RB->nullRoot->right = RB->nullRoot;
    RB->nullRoot->number = -1;
    return RB;
}

node *createNode(tree *RB, node *father, int number){
    node *auxNode = (node*)malloc(sizeof(node));
    auxNode->number = number;
    auxNode->father = father;
    auxNode->left = RB->nullRoot;
    auxNode->right = RB->nullRoot;
    auxNode->color = red;
}

void addNode(tree *RB, int number){
    node *auxNode = RB->firstRoot;

    if(auxNode == NULL || auxNode == RB->nullRoot){ 
        countSteps++;
        RB->firstRoot = createNode(RB, RB->nullRoot, number);
        balance(RB, RB->firstRoot);
        return;
    }

    while(true){
        countSteps++;
        if(auxNode->number <= number && (auxNode->right == RB->nullRoot || auxNode->right == NULL)){ 
            auxNode->right = createNode(RB, auxNode, number);
            balance(RB, auxNode->right);
            return;
        }
        else if(auxNode->number > number && (auxNode->left == RB->nullRoot || auxNode->left == NULL)){
            auxNode->left = createNode(RB, auxNode, number);
            balance(RB, auxNode->left);
            return;
        }
        else if(auxNode->number <= number) auxNode = auxNode->right;
        else auxNode = auxNode->left;
    }
}

node *searchNode(tree *RB, node *root, int number){
    if(root->number == number || root == RB->nullRoot) return root;
    else if(root->number > number) return searchNode(RB, root->left, number);
    else return searchNode(RB, root->right, number);
}

node *grandFather(tree *RB, node *root){
    countSteps++;
    return root->father->father;
}

node *uncle(tree *RB, node *root){
    countSteps++;
    node *auxNode = grandFather(RB, root);
    if(auxNode == RB->nullRoot) return RB->nullRoot;
    else if(root->father == auxNode->left) return auxNode->right;
    else return auxNode->left;
}

void balance(tree *RB, node *root){

    // Caso (0): root é o nó incial (raiz da árvore)
    if(root->father == RB->nullRoot){
        countSteps++;
        root->color = black;
        return;
    }
    // Solução (0): recolorir o único nó existente.


    // Obs.: Suponha que o nó argumento da função é sempre vermelho, visto que...
    // ... será sempre um nó recém adicionado (ao menos inicialmente):
    while(root->father->color == red && root->color == red){
        countSteps++;
        node *fatherRoot = root->father;
        node *grandRoot = grandFather(RB, root);
        node *uncleRoot = uncle(RB, root);

        // Caso (1): o nó tio (uncle) é vermelho
        if(uncleRoot->color == red){
            fatherRoot->color = black;
            uncleRoot->color = black;
            grandRoot->color = red;
            root = grandRoot;
            // Obs.: note que o balanceamento terá que ocorrer em todos os nós no caminho...
            // ... entre o nó folha adicionado e a raiz.
        }
        // Solução (1): recolorir o nó tio, pai e avô.

        // Se o nó root é filho à esquerda:
        else if(root == root->father->left){

            // Caso (2): o nó tio (uncle) é preto e o nó pai é filho à direita (e root é filho à esquerda)
            if(uncleRoot->color == black && grandRoot->right == fatherRoot){
                rotateRight(RB, fatherRoot);
                root = fatherRoot;
                // Obs.: note que nesse caso é de suma importância o fato de que o nó root...
                // ... é filho à esquerda de seu nó pai.
            }
            // Solução (2): rotacionar o nó pai para a direita, para que o balanceamento...
            // ... ocorra na próxima iteração do while.

            // Caso (3): o nó tio (uncle) é preto e o nó pai é filho à esquerda (e root é filho à esquerda)
            else if(uncleRoot->color == black && grandRoot->left == fatherRoot){
                rotateRight(RB, grandRoot);
                fatherRoot->color = black;  
                grandRoot->color = red;
                root = root->father;
            }
            // Solução (3): rotacionar o nó avô para o lado contrário do nó root (à direita)... 
            // ... e recolorir o nó pai original e o nó avô original (que virou nó irmão de root).
        }

        // Se o nó root é filho à direita:
        else{

            // Caso (2): o nó tio (uncle) é preto e o nó pai é filho à esquerda (root é filho á direita)
            if(uncleRoot->color == black && grandRoot->left == fatherRoot){
                rotateLeft(RB, fatherRoot);
                root = fatherRoot;
                // Obs.: note que nesse caso é de suma importância o fato de que o nó root...
                // ... é filho à direita de seu nó pai.
            }
            // Solução (2): rotacionar o nó pai para a esquerda, para que o balanceamento...
            // ... ocorra na próxima iteração do while.

            // Caso (3): o nó tio (uncle) é preto e o nó pai é filho à direita (root é filho á direita)
            else if(uncleRoot->color == black && grandRoot->right == fatherRoot){
                rotateLeft(RB, grandRoot);
                fatherRoot->color = black;
                grandRoot->color = red;
                root = fatherRoot;
            }
            // Solução (3): rotacionar o nó avô para o lado contrário do nó root (à esquerda)... 
            // ... e recolorir o nó pai original e o nó avô original (que virou nó irmão de root).
        }
    }
    RB->firstRoot->color = black;
}

void removeNode(tree *RB, int oldNumber){
    node *oldNode = searchNode(RB, RB->firstRoot, oldNumber);
    node *oldNodeFather = oldNode->father;
    coloring oldNodeColor = oldNode->color;

    if(oldNode == RB->firstRoot){
        RB->firstRoot = auxRemoveNode(RB, oldNode);
        RB->firstRoot->color = black;
        if(oldNodeColor != red) balanceDeleted(RB, RB->firstRoot);
    }
    else if(oldNodeFather->left == oldNode){
        oldNodeFather->left = auxRemoveNode(RB, oldNode);
        oldNodeFather->left->color = oldNodeColor;
        if(oldNodeColor != red) balanceDeleted(RB, oldNodeFather->left);
    }
    else{
        oldNodeFather->right = auxRemoveNode(RB, oldNode);
        oldNodeFather->right->color = oldNodeColor;
        if(oldNodeColor != red) balanceDeleted(RB, oldNodeFather->right);
    }
}

void balanceDeleted(tree *RB, node *root){

    while (root != RB->firstRoot && root->color != black){
        if(root = RB->nullRoot) break;
        
        node *rootBrother = brother(RB, root);
        node *rootFather = root->father;

        // Caso (1): se o irmão de root é vermelho
        if(rootBrother->color == red){
            rootBrother->color = black;
            rootFather->color = red;
            if(root == rootFather->left) rotateLeft(RB, rootFather);
            else rotateRight(RB, rootFather);
        }
        
        // Caso (2): se o irmão de root é preto e todos os seus filhos são pretos
        else if(rootBrother->left->color == black && rootBrother->right->color == black){
            rootBrother->color = red;
            root = rootFather;
        }

        // Caso (3): se root é filho à esquerda, o irmão de root é preto e seu filho à direita é preto
        else if(root == rootFather->left && rootBrother->right->color == black){
            rootBrother->left->color = black;
            rootBrother->color = red;
            rotateRight(RB, rootBrother);
            mantainTreeRoot(RB);
        }

        // Caso (3): se root é filho à direita, o irmão de root é preto e seu filho à direita é preto
        else if(root == rootFather->right && rootBrother->left->color == black){
            rootBrother->right->color = black;
            rootBrother->color = red;
            rotateLeft(RB, rootBrother);
        }

        // Caso (4): se nenhum dos outros casos ocorrer mas root é filho à esquerda
        else if(root == rootFather->left){
            rootBrother->color = rootFather->color;
            rootFather->color = black;
            rootBrother->right->color = black;
            rotateLeft(RB, rootFather);
            mantainTreeRoot(RB);
            root = RB->firstRoot;
        }

        // Caso (4): se nenhum dos outros casos ocorrer mas root é filho à direita
        else{
            rootBrother->color = rootFather->color;
            rootFather->color = black;
            rootBrother->left->color = black;
            rotateRight(RB, rootFather);
            mantainTreeRoot(RB);
            root = RB->firstRoot;
        }

        mantainTreeRoot(RB);
        root->color = black;
    }
}

void mantainTreeRoot(tree *RB){
    if(RB->firstRoot == RB->nullRoot || RB->firstRoot->father == RB->nullRoot) return;
    while(RB->firstRoot->father != RB->nullRoot) RB->firstRoot = RB->firstRoot->father;
}

node *brother(tree *RB, node *root){
    if(root->father == RB->nullRoot) return RB->nullRoot;
    else if(root->father->left == root) return root->father->right;
    else return root->father->left;
}

// Subir de qualquer nó até a raiz é de complexidade O(log(n))   

node *auxRemoveNode(tree *RB, node *son){

    // (1) Se o nó a ser removido não tem filhos:
    if(son->left == RB->nullRoot && son->right == RB->nullRoot){
        free(son);
        return RB->nullRoot;
    }

    // (2) Se o nó a ser removido só tem filho à direita:
    else if(son->left == RB->nullRoot){
        node *auxSon;
        auxSon = son->right;
        auxSon->father = son->father;
        free(son);
        return auxSon;
    }

    // (3) Se o nó a ser removido só tem filho à esquerda:
    else if(son->right == RB->nullRoot){
        node *auxSon;
        auxSon = son->left;
        auxSon->father = son->father;
        free(son);
        return auxSon;
    }

    // (4) Se o nó a ser removido tem dois filhos:

    // (4.1) Encontrar o sucessor do nó a ser removido e o pai deste sucessor (nesse caso estamos...
    // ... buscando o sucessor, mas também é possível utilizar o antecessor para realizar a remoção):
    node *successor, *successorFather;
    successor = son->right;
    successorFather = son;

    // (4.2) Percorrer a árvore até encontrar o sucessor e o pai do sucessor:
    while(successor->left != RB->nullRoot){
        successorFather = successor;
        successor = successor->left;
    }
    // Obs.: note que andando pro filho a direita do nó removido e depois indo até o nó folha...
    // ... mais à esquerda temos então o nó com o menor valor maior que o valor do nó a ser removido,...
    // ... ou seja, temos então o nó sucessor.

    // (4.3) Trocar o sucessor do nó a ser removido de lugar com o nó a ser removido:
    if(successorFather != son) successorFather->left = RB->nullRoot;
    successor->father = son->father;
    successor->left = son->left;
    if(son->right != successor) successor->right = son->right;
    else successor->right = RB->nullRoot;
    //successor->father = balance(successor->father);
    //successor = balanceAll(successor);
    free(son);
    return successor;
}

// Avisar sobre o problema de rotação em inserções para o professor:

void rotateLeft(tree *RB, node *root){
    countSteps++;
    if(root == RB->nullRoot) return;
    node *rightRoot;
    rightRoot = root->right;
    rightRoot->father = root->father;
    if(root->father->left == root) root->father->left = rightRoot;
    else if(root->father != RB->nullRoot) root->father->right = rightRoot;
    root->father = rightRoot;
    root->right = rightRoot->left;
    if(root->right != RB->nullRoot) root->right->father = root;
    rightRoot->left = root;
    if(RB->firstRoot->father != RB->nullRoot) RB->firstRoot = RB->firstRoot->father;
    // Obs.: teremos que retornar para um dos ponteiros do pai do nó rotacionado.
    // return rightRoot;
}

void rotateRight(tree *RB, node *root){
    countSteps++;
    if(root == RB->nullRoot) return;
    node *leftRoot;
    leftRoot = root->left;
    leftRoot->father = root->father;
    if(root->father->left == root) root->father->left = leftRoot;
    else if(root->father != RB->nullRoot) root->father->right = leftRoot;  
    root->father = leftRoot;
    root->left = leftRoot->right;
    root->left->father = root;
    leftRoot->right = root;
    if(RB->firstRoot->father != RB->nullRoot) RB->firstRoot = RB->firstRoot->father;
    // Obs.: teremos que retornar para um dos ponteiros do pai do nó rotacionado.
    // return leftRoot;
}