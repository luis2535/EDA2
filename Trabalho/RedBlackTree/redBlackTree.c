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

    // Caso (0): root ?? o n?? incial (raiz da ??rvore)
    if(root->father == RB->nullRoot){
        countSteps++;
        root->color = black;
        return;
    }
    // Solu????o (0): recolorir o ??nico n?? existente.


    // Obs.: Suponha que o n?? argumento da fun????o ?? sempre vermelho, visto que...
    // ... ser?? sempre um n?? rec??m adicionado (ao menos inicialmente):
    while(root->father->color == red && root->color == red){
        countSteps++;
        node *fatherRoot = root->father;
        node *grandRoot = grandFather(RB, root);
        node *uncleRoot = uncle(RB, root);

        // Caso (1): o n?? tio (uncle) ?? vermelho
        if(uncleRoot->color == red){
            fatherRoot->color = black;
            uncleRoot->color = black;
            grandRoot->color = red;
            root = grandRoot;
            // Obs.: note que o balanceamento ter?? que ocorrer em todos os n??s no caminho...
            // ... entre o n?? folha adicionado e a raiz.
        }
        // Solu????o (1): recolorir o n?? tio, pai e av??.

        // Se o n?? root ?? filho ?? esquerda:
        else if(root == root->father->left){

            // Caso (2): o n?? tio (uncle) ?? preto e o n?? pai ?? filho ?? direita (e root ?? filho ?? esquerda)
            if(uncleRoot->color == black && grandRoot->right == fatherRoot){
                rotateRight(RB, fatherRoot);
                root = fatherRoot;
                // Obs.: note que nesse caso ?? de suma import??ncia o fato de que o n?? root...
                // ... ?? filho ?? esquerda de seu n?? pai.
            }
            // Solu????o (2): rotacionar o n?? pai para a direita, para que o balanceamento...
            // ... ocorra na pr??xima itera????o do while.

            // Caso (3): o n?? tio (uncle) ?? preto e o n?? pai ?? filho ?? esquerda (e root ?? filho ?? esquerda)
            else if(uncleRoot->color == black && grandRoot->left == fatherRoot){
                rotateRight(RB, grandRoot);
                fatherRoot->color = black;  
                grandRoot->color = red;
                root = root->father;
            }
            // Solu????o (3): rotacionar o n?? av?? para o lado contr??rio do n?? root (?? direita)... 
            // ... e recolorir o n?? pai original e o n?? av?? original (que virou n?? irm??o de root).
        }

        // Se o n?? root ?? filho ?? direita:
        else{

            // Caso (2): o n?? tio (uncle) ?? preto e o n?? pai ?? filho ?? esquerda (root ?? filho ?? direita)
            if(uncleRoot->color == black && grandRoot->left == fatherRoot){
                rotateLeft(RB, fatherRoot);
                root = fatherRoot;
                // Obs.: note que nesse caso ?? de suma import??ncia o fato de que o n?? root...
                // ... ?? filho ?? direita de seu n?? pai.
            }
            // Solu????o (2): rotacionar o n?? pai para a esquerda, para que o balanceamento...
            // ... ocorra na pr??xima itera????o do while.

            // Caso (3): o n?? tio (uncle) ?? preto e o n?? pai ?? filho ?? direita (root ?? filho ?? direita)
            else if(uncleRoot->color == black && grandRoot->right == fatherRoot){
                rotateLeft(RB, grandRoot);
                fatherRoot->color = black;
                grandRoot->color = red;
                root = fatherRoot;
            }
            // Solu????o (3): rotacionar o n?? av?? para o lado contr??rio do n?? root (?? esquerda)... 
            // ... e recolorir o n?? pai original e o n?? av?? original (que virou n?? irm??o de root).
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

        // Caso (1): se o irm??o de root ?? vermelho
        if(rootBrother->color == red){
            rootBrother->color = black;
            rootFather->color = red;
            if(root == rootFather->left) rotateLeft(RB, rootFather);
            else rotateRight(RB, rootFather);
        }
        
        // Caso (2): se o irm??o de root ?? preto e todos os seus filhos s??o pretos
        else if(rootBrother->left->color == black && rootBrother->right->color == black){
            rootBrother->color = red;
            root = rootFather;
        }

        // Caso (3): se root ?? filho ?? esquerda, o irm??o de root ?? preto e seu filho ?? direita ?? preto
        else if(root == rootFather->left && rootBrother->right->color == black){
            rootBrother->left->color = black;
            rootBrother->color = red;
            rotateRight(RB, rootBrother);
            mantainTreeRoot(RB);
        }

        // Caso (3): se root ?? filho ?? direita, o irm??o de root ?? preto e seu filho ?? direita ?? preto
        else if(root == rootFather->right && rootBrother->left->color == black){
            rootBrother->right->color = black;
            rootBrother->color = red;
            rotateLeft(RB, rootBrother);
        }

        // Caso (4): se nenhum dos outros casos ocorrer mas root ?? filho ?? esquerda
        else if(root == rootFather->left){
            rootBrother->color = rootFather->color;
            rootFather->color = black;
            rootBrother->right->color = black;
            rotateLeft(RB, rootFather);
            mantainTreeRoot(RB);
            root = RB->firstRoot;
        }

        // Caso (4): se nenhum dos outros casos ocorrer mas root ?? filho ?? direita
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

// Subir de qualquer n?? at?? a raiz ?? de complexidade O(log(n))   

node *auxRemoveNode(tree *RB, node *son){

    // (1) Se o n?? a ser removido n??o tem filhos:
    if(son->left == RB->nullRoot && son->right == RB->nullRoot){
        free(son);
        return RB->nullRoot;
    }

    // (2) Se o n?? a ser removido s?? tem filho ?? direita:
    else if(son->left == RB->nullRoot){
        node *auxSon;
        auxSon = son->right;
        auxSon->father = son->father;
        free(son);
        return auxSon;
    }

    // (3) Se o n?? a ser removido s?? tem filho ?? esquerda:
    else if(son->right == RB->nullRoot){
        node *auxSon;
        auxSon = son->left;
        auxSon->father = son->father;
        free(son);
        return auxSon;
    }

    // (4) Se o n?? a ser removido tem dois filhos:

    // (4.1) Encontrar o sucessor do n?? a ser removido e o pai deste sucessor (nesse caso estamos...
    // ... buscando o sucessor, mas tamb??m ?? poss??vel utilizar o antecessor para realizar a remo????o):
    node *successor, *successorFather;
    successor = son->right;
    successorFather = son;

    // (4.2) Percorrer a ??rvore at?? encontrar o sucessor e o pai do sucessor:
    while(successor->left != RB->nullRoot){
        successorFather = successor;
        successor = successor->left;
    }
    // Obs.: note que andando pro filho a direita do n?? removido e depois indo at?? o n?? folha...
    // ... mais ?? esquerda temos ent??o o n?? com o menor valor maior que o valor do n?? a ser removido,...
    // ... ou seja, temos ent??o o n?? sucessor.

    // (4.3) Trocar o sucessor do n?? a ser removido de lugar com o n?? a ser removido:
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

// Avisar sobre o problema de rota????o em inser????es para o professor:

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
    // Obs.: teremos que retornar para um dos ponteiros do pai do n?? rotacionado.
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
    // Obs.: teremos que retornar para um dos ponteiros do pai do n?? rotacionado.
    // return leftRoot;
}