//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section E - Binary Trees Questions
Purpose: Implementing the required functions for Question 7 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
// #include <limits.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _btnode
{
    int item;
    struct _btnode *left;
    struct _btnode *right;
} BTNode; // You should not change the definition of BTNode

/////////////////////////////////////////////////////////////////////////////////

typedef struct _stackNode
{
    BTNode *btnode;
    struct _stackNode *next;
} StackNode;

typedef struct _stack
{
    StackNode *top;
} Stack;

///////////////////////// Function prototypes ////////////////////////////////////

// You should not change the prototypes of these functions
int smallestValue(BTNode *node);

BTNode *createBTNode(int item);

BTNode *createTree();
void push(Stack *stack, BTNode *node);
BTNode *pop(Stack *stack);

void printTree(BTNode *node);
void removeAll(BTNode **node);

///////////////////////////// main() /////////////////////////////////////////////

int main()
{
    char e;
    int c, value;
    BTNode *root;

    c = 1;
    root = NULL;

    printf("1: Create a binary tree.\n");
    printf("2: Smallest value;\n");
    printf("0: Quit;\n");

    while (c != 0)
    {
        printf("Please input your choice(1/2/0): ");
        if (scanf("%d", &c) > 0)
        {
            switch (c)
            {
            case 1:
                removeAll(&root);
                root = createTree();
                printf("The resulting binary tree is: ");
                printTree(root);
                printf("\n");
                break;
            case 2:
                value = smallestValue(root);
                printf("Smallest value of the binary tree is: %d\n", value);
                removeAll(&root);
                break;
            case 0:
                removeAll(&root);
                break;
            default:
                printf("Choice unknown;\n");
                break;
            }
        }
        else
        {
            scanf("%c", &e);
        }
    }
    return 0;
}

//////////////////////////////////////////////////////////////////////////////////

int smallestValue(BTNode *node)
{
    /* AI 코드 (내 논리를 살리면서 include 하지 않는 버전) */
    // (예외 처리) 트리가 비어 있는 경우
    if (node == NULL)
    {
        return 0;
    }

    int min = node->item;

    if (node->left != NULL)
    {
        int left_min = smallestValue(node->left);
        if (left_min < min)
        {
            min = left_min;
        }
    }

    if (node->right != NULL)
    {
        int right_min = smallestValue(node->right);
        if (right_min < min)
        {
            min = right_min;
        }
    }

    return min;

    /* AI 코드 (include <limits.h> 필요한 버전) */
    // if (node == NULL)
    // {
    //     return INT_MAX;
    // }

    // int left_min = smallestValue(node->left);
    // int right_min = smallestValue(node->right);

    // int min = node->item;
    // if (left_min < min) min = left_min;
    // if (right_min < min) min = right_min;

    // return min;

    /* 내 코드 */
    // if (node->left == NULL && node->right == NULL)
    // {
    //     return node->item;
    // }

    // int not_min_val = node->item + 1;
    // int left_min, right_min;
    // left_min = right_min = not_min_val;
    // if (node->left != NULL)
    // {
    //     left_min = smallestValue(node->left);
    // }
    // if (node->right != NULL)
    // {
    //     right_min = smallestValue(node->right);
    // }

    // int total_min = (left_min < right_min) ? left_min : right_min;

    // return (node->item < total_min) ? node->item : total_min;
}

//////////////////////////////////////////////////////////////////////////////////

BTNode *createBTNode(int item)
{
    BTNode *newNode = malloc(sizeof(BTNode));
    newNode->item = item;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

//////////////////////////////////////////////////////////////////////////////////

BTNode *createTree()
{
    Stack stack;
    BTNode *root, *temp;
    char s;
    int item;

    stack.top = NULL;
    root = NULL;
    printf("Input an integer that you want to add to the binary tree. Any Alpha value will be treated as NULL.\n");
    printf("Enter an integer value for the root: ");
    if (scanf("%d", &item) > 0)
    {
        root = createBTNode(item);
        push(&stack, root);
    }
    else
    {
        scanf("%c", &s);
    }

    while ((temp = pop(&stack)) != NULL)
    {

        printf("Enter an integer value for the Left child of %d: ", temp->item);

        if (scanf("%d", &item) > 0)
        {
            temp->left = createBTNode(item);
        }
        else
        {
            scanf("%c", &s);
        }

        printf("Enter an integer value for the Right child of %d: ", temp->item);
        if (scanf("%d", &item) > 0)
        {
            temp->right = createBTNode(item);
        }
        else
        {
            scanf("%c", &s);
        }

        if (temp->right != NULL)
            push(&stack, temp->right);
        if (temp->left != NULL)
            push(&stack, temp->left);
    }
    return root;
}

void push(Stack *stack, BTNode *node)
{
    StackNode *temp;

    temp = malloc(sizeof(StackNode));
    if (temp == NULL)
        return;
    temp->btnode = node;
    if (stack->top == NULL)
    {
        stack->top = temp;
        temp->next = NULL;
    }
    else
    {
        temp->next = stack->top;
        stack->top = temp;
    }
}

BTNode *pop(Stack *stack)
{
    StackNode *temp, *top;
    BTNode *ptr;
    ptr = NULL;

    top = stack->top;
    if (top != NULL)
    {
        temp = top->next;
        ptr = top->btnode;

        stack->top = temp;
        free(top);
        top = NULL;
    }
    return ptr;
}

void printTree(BTNode *node)
{
    if (node == NULL)
        return;

    printTree(node->left);
    printf("%d ", node->item);
    printTree(node->right);
}

void removeAll(BTNode **node)
{
    if (*node != NULL)
    {
        removeAll(&((*node)->left));
        removeAll(&((*node)->right));
        free(*node);
        *node = NULL;
    }
}
