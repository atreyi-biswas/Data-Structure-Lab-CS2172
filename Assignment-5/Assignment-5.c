#include <stdio.h>
#include <stdlib.h>

// Structure definition
typedef struct node {
    int data;
    struct node *lchild;
    struct node *rchild;
    struct node *parent;
} treenode;

/* 
FUNCTIONS
1. int isEmpty(treenode *t);
2. treenode *createNode(int val);
3. treenode *insertNode(treenode *t, int val);
4. int getCount(treenode *t);
5. int inorder(treenode *t);
6. int preorder(treenode *t);
7. int postorder(treenode *t);

EXTENSION FUNCTIONS
8.  int height(treenode *t);
9.  int max(treenode *t);
10. int min(treenode *t);
11. int equal(treenode *t1, treenode *t2);
12. treenode *search(treenode *t, int key);
13. treenode *insucc(treenode *t, int key);
14. treenode *deleteNode(treenode *t, int val);
*/

// ------------------------------------------------------------------------

int isEmpty(treenode *t) { // Check if BST is empty
    return (t == NULL);
}

// ------------------------------------------------------------------------

treenode *createNode(int val) { // Create a new node
    treenode *newNode = (treenode *)malloc(sizeof(treenode));
    newNode->data = val;
    newNode->lchild = newNode->rchild = newNode->parent = NULL;
    return newNode;
}

// ------------------------------------------------------------------------

treenode *insertNode(treenode *t, int val) { // Insert a node into BST
    if (t == NULL)
        return createNode(val);

    if (val < t->data) {
        t->lchild = insertNode(t->lchild, val);
        if (t->lchild) t->lchild->parent = t;
    } else if (val > t->data) {
        t->rchild = insertNode(t->rchild, val);
        if (t->rchild) t->rchild->parent = t;
    }
    return t; // unchanged root pointer
}

// ------------------------------------------------------------------------

int getCount(treenode *t) { // Count total nodes in BST
    if (t == NULL)
        return 0;
    return 1 + getCount(t->lchild) + getCount(t->rchild);
}

// ------------------------------------------------------------------------

int inorder(treenode *t) { // Inorder traversal
    if (t == NULL)
        return 0;
    inorder(t->lchild);       // Visit left child
    printf("%d ", t->data);   // Visit root
    inorder(t->rchild);       // Visit right child
    return 1;
}

// ------------------------------------------------------------------------

int preorder(treenode *t) { // Preorder traversal
    if (t == NULL)
        return 0;
    printf("%d ", t->data);  // Visit root first
    preorder(t->lchild);     // Then left subtree
    preorder(t->rchild);     // Then right subtree
    return 1;
}

// ------------------------------------------------------------------------

int postorder(treenode *t) { // Postorder traversal
    if (t == NULL)
        return 0;
    postorder(t->lchild);    // Visit left subtree
    postorder(t->rchild);    // Visit right subtree
    printf("%d ", t->data);  // Visit root
    return 1;
}

// ------------------------------------------------------------------------

int height(treenode *t) {  //height of tree node
    if (t == NULL)
        return -1;
    int lh = height(t->lchild);
    int rh = height(t->rchild);
    return (lh > rh ? lh : rh) + 1;
}

// ------------------------------------------------------------------------

int max(treenode *t) {  //maximum element in the tree node
    if (t == NULL) {
        printf("Tree is empty!\n");
        return -1;
    }
    while (t->rchild != NULL)
        t = t->rchild;
    return t->data;
}

// ------------------------------------------------------------------------

int min(treenode *t) {  //minimum element in the tree node
    if (t == NULL) {
        printf("Tree is empty!\n");
        return -1;
    }
    while (t->lchild != NULL)
        t = t->lchild;
    return t->data;
}

// ------------------------------------------------------------------------

int equal(treenode *t1, treenode *t2) {  //to check if treenode 1 and 2 are equal or not
    if (t1 == NULL && t2 == NULL)
        return 1;
    if (t1 == NULL || t2 == NULL)
        return 0;
    return (t1->data == t2->data &&
            equal(t1->lchild, t2->lchild) &&
            equal(t1->rchild, t2->rchild));
}

// ------------------------------------------------------------------------

treenode *search(treenode *t, int key) {  //search an element in treenode
    if (t == NULL || t->data == key)
        return t;
    if (key < t->data)
        return search(t->lchild, key);
    return search(t->rchild, key);
}

// ------------------------------------------------------------------------

treenode *insucc(treenode *t, int key) {  
    treenode *current = search(t, key);
    if (current == NULL)
        return NULL;

    // Case 1: has right subtree
    if (current->rchild != NULL) {
        treenode *temp = current->rchild;
        while (temp->lchild != NULL)
            temp = temp->lchild;
        return temp;
    }

    // Case 2: no right child so, go to ancestor
    treenode *p = current->parent;
    while (p != NULL && current == p->rchild) {
        current = p;
        p = p->parent;
    }
    return p;
}

// ------------------------------------------------------------------------

treenode *deleteNode(treenode *t, int val) {  //delete node from tree node of a certain value
    if (t == NULL)
        return t;

    if (val < t->data) {
        t->lchild = deleteNode(t->lchild, val);
        if (t->lchild) t->lchild->parent = t; // maintain parent
    }
    else if (val > t->data) {
        t->rchild = deleteNode(t->rchild, val);
        if (t->rchild) t->rchild->parent = t; // maintain parent
    }
    else {
        // Node found
        if (t->lchild == NULL) {
            treenode *temp = t->rchild;
            if (temp) temp->parent = t->parent;
            free(t);
            return temp;
        } else if (t->rchild == NULL) {
            treenode *temp = t->lchild;
            if (temp) temp->parent = t->parent;
            free(t);
            return temp;
        }

        // Two children: get inorder successor
        treenode *succ = t->rchild;
        while (succ->lchild != NULL)
            succ = succ->lchild;

        t->data = succ->data;
        t->rchild = deleteNode(t->rchild, succ->data);
        if (t->rchild) t->rchild->parent = t;
    }
    return t;
}


// ------------------------------------------------------------------------

int main() {
    treenode *root = NULL;
    treenode *root2 = NULL; // for equality check
    int choice, val;

    while (1) {
        printf("\n\n========= BINARY SEARCH TREE MENU =========\n");
        printf("1. Insert a Node\n");
        printf("2. Display Inorder Traversal\n");
        printf("3. Display Preorder Traversal\n");
        printf("4. Display Postorder Traversal\n");
        printf("5. Count Total Nodes\n");
        printf("6. Check if Tree is Empty\n");
        printf("7. Height of Tree\n");
        printf("8. Maximum Key\n");
        printf("9. Minimum Key\n");
        printf("10. Search a Key\n");
        printf("11. Inorder Successor of a Key\n");
        printf("12. Delete a Node\n");
        printf("13. Check Equality of Two Trees\n");
        printf("14. Exit\n");
        printf("===========================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("Enter value to insert: ");
            scanf("%d", &val);
            root = insertNode(root, val);
            printf("Node inserted successfully!\n");
            break;

        case 2:
            if (isEmpty(root))
                printf("Tree is empty!\n");
            else {
                printf("Inorder Traversal: ");
                inorder(root);
                printf("\n");
            }
            break;

        case 3:
            if (isEmpty(root))
                printf("Tree is empty!\n");
            else {
                printf("Preorder Traversal: ");
                preorder(root);
                printf("\n");
            }
            break;

        case 4:
            if (isEmpty(root))
                printf("Tree is empty!\n");
            else {
                printf("Postorder Traversal: ");
                postorder(root);
                printf("\n");
            }
            break;

        case 5:
            printf("Total number of nodes: %d\n", getCount(root));
            break;

        case 6:
            if (isEmpty(root))
                printf("Tree is empty.\n");
            else
                printf("Tree is not empty.\n");
            break;

        case 7:
            printf("Height of tree: %d\n", height(root));
            break;

        case 8:
            if (isEmpty(root))
                printf("Tree is empty!\n");
            else
                printf("Maximum key: %d\n", max(root));
            break;

        case 9:
            if (isEmpty(root))
                printf("Tree is empty!\n");
            else
                printf("Minimum key: %d\n", min(root));
            break;

        case 10:
            printf("Enter key to search: ");
            scanf("%d", &val);
            if (search(root, val))
                printf("Key %d found in tree.\n", val);
            else
                printf("Key %d NOT found in tree.\n", val);
            break;

        case 11: {
            printf("Enter key to find inorder successor: ");
            scanf("%d", &val);
            treenode *s = insucc(root, val);
            if (s)
                printf("Inorder successor of %d is %d\n", val, s->data);
            else
                printf("Inorder successor not found (key may not exist or no successor).\n");
            break;
        }

        case 12:
            printf("Enter value to delete: ");
            scanf("%d", &val);
            root = deleteNode(root, val);
            printf("If node existed, it has been deleted (tree updated).\n");
            break;

        case 13: {
            root2 = NULL;
            int n2;
            printf("Create second tree for equality check.\n");
            printf("Enter nodes in second tree: ");
            scanf("%d", &n2);
            if (n2 <= 0) {
                printf("Second tree empty.\n");
            } else {
                printf("Enter %d values:\n", n2);
                for (int i = 0; i < n2; i++) {
                    scanf("%d", &val);
                    root2 = insertNode(root2, val);
                }
            }
            if (equal(root, root2))
                printf("Both trees are EQUAL.\n"); 
            else
                printf("Trees are NOT equal.\n");
            break;
        }

        case 14:
            printf("Exiting program!\n");
            exit(0);

        default:
            printf("Invalid choice!\n");
        }
    }

    return 0;
}
