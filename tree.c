#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct bst_node
{
    int value;
    struct bst_node *leftChild, *rightChild;
};

// �ܧ�R�W
typedef struct bst_node Tnode;

Tnode *new_node(int);
void inorder(Tnode *);
Tnode *search_node(Tnode *, int);
void getLeftNodeNum(Tnode *, int *);
Tnode *search_nth(Tnode *, int);
Tnode *insert_node(Tnode *, int);
Tnode *minValueNode(Tnode *);
Tnode *delete_node(Tnode *, int);

// �Ыطs�`�I
Tnode *new_node(int value)
{
    // malloc���t�`�I�Ŷ�
    Tnode *tmp = (Tnode *)malloc(sizeof(Tnode));

    tmp->value = value;
    tmp->leftChild = tmp->rightChild = NULL;
    return tmp;
}

// ���ǰl��
void inorder(Tnode *root_node)
{
    if (root_node != NULL)
    {
        inorder(root_node->leftChild);
        printf("%d ", root_node->value);
        inorder(root_node->rightChild);
    }
}

// �M��`�I
Tnode *search_node(Tnode *node, int value)
{
    // �S���
    if (node == NULL)
        return NULL;

    // ���`�I
    if (value == node->value)
        return node;

    // �Q�M�䪺�ƭȤp���e�`�I�A�~�򩹥����j�M��
    else if (value < node->value)
        return search_node(node->leftChild, value);

    // �Q�M�䪺�ƭȤj���e�`�I�A�~�򩹥k���j�M��
    else if (value > node->value)
        return search_node(node->rightChild, value);
}

// �p��l��`�I���ƶq
void getLeftNodeNum(Tnode *node, int *rank)
{
    if (node == NULL)
        return;

    // �p�⦹�`�I���l�𪺼ƶq
    getLeftNodeNum(node->leftChild, rank);

    // �p�⦹�`�I�k�l�𪺼ƶq
    getLeftNodeNum(node->rightChild, rank);

    // ���`�I�����k�l��`�I���䧹��A�N���`�I��J
    *rank += 1;
}

// �M���n�p���ƭ�
Tnode *search_nth(Tnode *node, int n)
{
    int rank = 0;

    // �S���
    if (node == NULL)
        return NULL;

    // leftsize=���l�𪺼ƶq+1
    getLeftNodeNum(node->leftChild, &rank);
    rank++;

    // ����n�p���`�I
    if (n == rank)
    {
        return node;
    }

    // �p�Gn�p��rank�A�~�򩹥����j
    else if (n < rank)
        return search_nth(node->leftChild, n);

    // �p�Gn�j��rank�A�~�򩹥k���j�A�ܦ���k�l�𪺲�n-rank(���)�p
    else
        return search_nth(node->rightChild, n - rank);
}

// ���J�`�I
Tnode *insert_node(Tnode *node, int value)
{
    // �p�G�Ӹ`�I��NULL�A�h���J���`�I
    if (node == NULL)
        return new_node(value);

    // �Q���J���ƭȤp���e�`�I�A�~�򩹥����j�M��
    if (value < node->value)
    {
        node->leftChild = insert_node(node->leftChild, value);
    }

    // �Q���J���ƭȤj���e�`�I�A�~�򩹥k���j�M��
    else if (value > node->value)
    {
        node->rightChild = insert_node(node->rightChild, value);
    }

    // �Q���J���ƭȵ����e�`�I(�w�s�b)
    else
        return node;
}

// ��(�k�l��)�̤p�Ȫ��`�I
Tnode *minValueNode(Tnode *node)
{
    Tnode *current = node;

    while (current->leftChild != NULL)
        current = current->leftChild;

    return current;
}

// �R���`�I
Tnode *delete_node(Tnode *node, int value)
{
    // �ƭȤ��s�b�G����
    if (node == NULL)
        return node;

    // �Q�R�����ƭȤp���e�`�I�A�~�򩹥����j�M��
    if (value < node->value)
    {
        node->leftChild = delete_node(node->leftChild, value);
    }

    // �Q�R�����ƭȤj���e�`�I�A�~�򩹥k���j�M��
    else if (value > node->value)
    {
        node->rightChild = delete_node(node->rightChild, value);
    }

    // ���n�R�����`�I
    else
    {
        Tnode *temp;

        // �R�����`�I���@��child�ΨS��child
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

        // �R�����`�I�����child�A��inorder siccessor
        else
        {
            // ��k�l�𪺳̤p��
            temp = minValueNode(node->rightChild);

            // �Υk�l�𪺳̤p��temp�Ӵ��N�쥻�n�R����node
            node->value = temp->value;

            // ��k�l�𪺳̤p�ȭ���Ҧb��node�R��
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
        printf("(A) �q�ɮ�Ū�J�ƭȡAInsert�ƭȨ�G����\n");
        printf("(B) �q��L��J�ƭȡAInsert�ƭȨ�G����\n");
        printf("(C) �d�߯S�w�ƭȬO�_�s�b���G����\n");
        printf("(D) �d�߲ĴX�p���ƭȬ���\n");
        printf("(E) �q���G����Delete�S�w�ƭ�\n");
        printf("(F) �HInorder�ǿ�X���G���𤤪��ƭ�\n");
        printf("(G) �������{��\n");
        scanf(" %c", &choice); // %c�e���[�Ů�O���F��scanf�Y������r��

        // �q�ɮ�Ū�J�ƭ�
        if (choice == 'a' || choice == 'A')
        {
            printf("��J�ɮ��ɦW(������.txt) => ");
            scanf("%s", name);
            inp = fopen(name, "r");

            // �p�GŪ�ɥ��ѫh���X�{��
            if (inp == NULL)
            {
                printf("Ū�ɥ���");
                return 1;
            }

            while (fscanf(inp, "%d", &value) != EOF)
            {
                root_node = insert_node(root_node, value);
            }

            fclose(inp);
        }

        // ���J�ƭ�
        else if (choice == 'b' || choice == 'B')
        {
            printf("��J�ƭȡA�H����Ÿ����� => ");
            while (scanf("%d", &value) == 1)
            {
                if (search_node(root_node, value) != NULL)
                {
                    printf("�ƭ� %d �w�s�b\n", value);
                }
                else
                {
                    root_node = insert_node(root_node, value);
                }

                char c = getchar(); // Ū���Ʀr��誺�Ÿ�(�ť�/����Ÿ�)

                // Ū�촫��Ÿ��h���X�j��
                if (c == '\n')
                {
                    break;
                }
            }
        }

        // �M��S�w�ƭ�
        else if (choice == 'c' || choice == 'C')
        {
            printf("��J�Q�d�ߪ��ƭ� => ");
            scanf("%d", &value);

            if (search_node(root_node, value) == NULL)
                printf("���ƭȤ��s�b\n");
            else
            {
                printf("���ƭȦs�b\n");
            }
        }

        // �M���n�p���ƭ�
        else if (choice == 'd' || choice == 'D')
        {
            printf("��J��N�p�ƭȪ�N�� => ");
            scanf("%d", &value);

            tmp = search_nth(root_node, value);
            if (tmp == NULL)
                printf("���ƭȤ��s�b\n");
            else
            {
                printf("�� %d �p���ƭȬ� %d\n", value, tmp->value);
            }
            tmp = NULL;
        }

        // �R���`�I
        else if (choice == 'e' || choice == 'E')
        {
            printf("��J�Q�R�����ƭ� => ");
            scanf("%d", &value);

            if (search_node(root_node, value) == NULL)
                printf("���ƭȤ��s�b\n");
            else
            {
                root_node = delete_node(root_node, value);
            }
        }

        // ��Xinorder���G
        else if (choice == 'f' || choice == 'F')
        {
            inorder(root_node);
            printf("\n");
        }
    }

    return 0;
}