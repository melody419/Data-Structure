#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct bst_node
{
    int value;
    struct bst_node *leftChild, *rightChild;
};

// 變更命名
typedef struct bst_node Tnode;

Tnode *new_node(int);
void inorder(Tnode *);
Tnode *search_node(Tnode *, int);
void getLeftNodeNum(Tnode *, int *);
Tnode *search_nth(Tnode *, int);
Tnode *insert_node(Tnode *, int);
Tnode *minValueNode(Tnode *);
Tnode *delete_node(Tnode *, int);

// 創建新節點
Tnode *new_node(int value)
{
    // malloc分配節點空間
    Tnode *tmp = (Tnode *)malloc(sizeof(Tnode));

    tmp->value = value;
    tmp->leftChild = tmp->rightChild = NULL;
    return tmp;
}

// 中序追蹤
void inorder(Tnode *root_node)
{
    if (root_node != NULL)
    {
        inorder(root_node->leftChild);
        printf("%d ", root_node->value);
        inorder(root_node->rightChild);
    }
}

// 尋找節點
Tnode *search_node(Tnode *node, int value)
{
    // 沒找到
    if (node == NULL)
        return NULL;

    // 找到節點
    if (value == node->value)
        return node;

    // 想尋找的數值小於當前節點，繼續往左遞迴尋找
    else if (value < node->value)
        return search_node(node->leftChild, value);

    // 想尋找的數值大於當前節點，繼續往右遞迴尋找
    else if (value > node->value)
        return search_node(node->rightChild, value);
}

// 計算子樹節點的數量
void getLeftNodeNum(Tnode *node, int *rank)
{
    if (node == NULL)
        return;

    // 計算此節點左子樹的數量
    getLeftNodeNum(node->leftChild, rank);

    // 計算此節點右子樹的數量
    getLeftNodeNum(node->rightChild, rank);

    // 此節點的左右子樹節點都找完後，將此節點算入
    *rank += 1;
}

// 尋找第n小的數值
Tnode *search_nth(Tnode *node, int n)
{
    int rank = 0;

    // 沒找到
    if (node == NULL)
        return NULL;

    // leftsize=左子樹的數量+1
    getLeftNodeNum(node->leftChild, &rank);
    rank++;

    // 找到第n小的節點
    if (n == rank)
    {
        return node;
    }

    // 如果n小於rank，繼續往左遞迴
    else if (n < rank)
        return search_nth(node->leftChild, n);

    // 如果n大於rank，繼續往右遞迴，變成找右子樹的第n-rank(樹根)小
    else
        return search_nth(node->rightChild, n - rank);
}

// 插入節點
Tnode *insert_node(Tnode *node, int value)
{
    // 如果該節點為NULL，則插入此節點
    if (node == NULL)
        return new_node(value);

    // 想插入的數值小於當前節點，繼續往左遞迴尋找
    if (value < node->value)
    {
        node->leftChild = insert_node(node->leftChild, value);
    }

    // 想插入的數值大於當前節點，繼續往右遞迴尋找
    else if (value > node->value)
    {
        node->rightChild = insert_node(node->rightChild, value);
    }

    // 想插入的數值等於當前節點(已存在)
    else
        return node;
}

// 找(右子樹)最小值的節點
Tnode *minValueNode(Tnode *node)
{
    Tnode *current = node;

    while (current->leftChild != NULL)
        current = current->leftChild;

    return current;
}

// 刪除節點
Tnode *delete_node(Tnode *node, int value)
{
    // 數值不存在二元樹內
    if (node == NULL)
        return node;

    // 想刪除的數值小於當前節點，繼續往左遞迴尋找
    if (value < node->value)
    {
        node->leftChild = delete_node(node->leftChild, value);
    }

    // 想刪除的數值大於當前節點，繼續往右遞迴尋找
    else if (value > node->value)
    {
        node->rightChild = delete_node(node->rightChild, value);
    }

    // 找到要刪除的節點
    else
    {
        Tnode *temp;

        // 刪除的節點有一個child或沒有child
        if (node->leftChild == NULL)
        {
            temp = node->rightChild;
            free(node);
            return temp;
        }
        else if (node->rightChild == NULL)
        {
            temp = node->leftChild;
            free(node);
            return temp;
        }

        // 刪除的節點有兩個child，用inorder siccessor
        else
        {
            // 找右子樹的最小值
            temp = minValueNode(node->rightChild);

            // 用右子樹的最小值temp來替代原本要刪除的node
            node->value = temp->value;

            // 把右子樹的最小值原先所在的node刪除
            node->rightChild = delete_node(node->rightChild, temp->value);
        }
    }
    return node;
}

int main(void)
{
    FILE *inp;
    Tnode *root_node = NULL;
    Tnode *tmp = NULL;
    char choice = ' ';
    char name[100] = "";
    int value = 0;

    while (choice != 'g' && choice != 'G')
    {
        printf("----------------------------------------------\n");
        printf("(A) 從檔案讀入數值，Insert數值到二元樹中\n");
        printf("(B) 從鍵盤輸入數值，Insert數值到二元樹中\n");
        printf("(C) 查詢特定數值是否存在此二元樹中\n");
        printf("(D) 查詢第幾小的數值為何\n");
        printf("(E) 從此二元樹中Delete特定數值\n");
        printf("(F) 以Inorder序輸出此二元樹中的數值\n");
        printf("(G) 結束此程式\n");
        scanf(" %c", &choice); // %c前面加空格是為了讓scanf吃掉換行字元

        // 從檔案讀入數值
        if (choice == 'a' || choice == 'A')
        {
            printf("輸入檔案檔名(必須為.txt) => ");
            scanf("%s", name);
            inp = fopen(name, "r");

            // 如果讀檔失敗則跳出程式
            if (inp == NULL)
            {
                printf("讀檔失敗");
                return 1;
            }

            while (fscanf(inp, "%d", &value) != EOF)
            {
                root_node = insert_node(root_node, value);
            }

            fclose(inp);
        }

        // 插入數值
        else if (choice == 'b' || choice == 'B')
        {
            printf("輸入數值，以換行符號結束 => ");
            while (scanf("%d", &value) == 1)
            {
                if (search_node(root_node, value) != NULL)
                {
                    printf("數值 %d 已存在\n", value);
                }
                else
                {
                    root_node = insert_node(root_node, value);
                }

                char c = getchar(); // 讀取數字後方的符號(空白/換行符號)

                // 讀到換行符號則跳出迴圈
                if (c == '\n')
                {
                    break;
                }
            }
        }

        // 尋找特定數值
        else if (choice == 'c' || choice == 'C')
        {
            printf("輸入想查詢的數值 => ");
            scanf("%d", &value);

            if (search_node(root_node, value) == NULL)
                printf("此數值不存在\n");
            else
            {
                printf("此數值存在\n");
            }
        }

        // 尋找第n小的數值
        else if (choice == 'd' || choice == 'D')
        {
            printf("輸入第N小數值的N值 => ");
            scanf("%d", &value);

            tmp = search_nth(root_node, value);
            if (tmp == NULL)
                printf("此數值不存在\n");
            else
            {
                printf("第 %d 小的數值為 %d\n", value, tmp->value);
            }
            tmp = NULL;
        }

        // 刪除節點
        else if (choice == 'e' || choice == 'E')
        {
            printf("輸入想刪除的數值 => ");
            scanf("%d", &value);

            if (search_node(root_node, value) == NULL)
                printf("此數值不存在\n");
            else
            {
                root_node = delete_node(root_node, value);
            }
        }

        // 輸出inorder結果
        else if (choice == 'f' || choice == 'F')
        {
            inorder(root_node);
            printf("\n");
        }
    }

    return 0;
}