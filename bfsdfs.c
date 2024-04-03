#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

void bfs(int s_array[], int startVertex, int node_num, int visited[])
{
    int queue[MAX];
    int front = 0;
    int rear = 0;

    visited[startVertex] = 1;
    queue[rear++] = startVertex;

    while (front != rear && rear < node_num)
    {
        int check = s_array[queue[front]];
        int check_next = s_array[queue[front] + 1];
        printf("%d ", queue[front++]);
        while (check < check_next)
        {
            if (visited[s_array[check]] == 0)
            {
                queue[rear++] = s_array[check];
                visited[s_array[check]] = 1;
            }
            check++;
        }
    }
}

void dfs(int s_array[], int startVertex, int visited[])
{
    visited[startVertex] = 1;
    printf("%d ", startVertex);

    int check = s_array[startVertex];
    int check_next = s_array[startVertex + 1];

    while (check < check_next)
    {
        int next = s_array[check];
        check++;
        if (visited[next] != 1)
        {
            dfs(s_array, next, visited);
        }
    }
}

int main()
{
    FILE *inp;
    char name[MAX];

    int node_num, i = 0;
    int s_array[MAX];
    int visited[MAX] = {0}; // 檢查該節點是否被拜訪過

    printf("輸入檔案檔名(必須為.txt) => ");
    scanf("%s", name);
    inp = fopen(name, "r");

    // 儲存sequential representation array
    while (fscanf(inp, "%d", &s_array[i]) == 1)
    {
        i++;
    };

    node_num = s_array[0] - 1;

    fclose(inp);

    printf("\nDFS:\n");
    for (int i = 0; i < node_num; i++)
    {
        if (visited[i] == 0)
        {
            dfs(s_array, i, visited);
            printf("\n");
        }
    }

    for (int i = 0; i < node_num; i++)
    {
        visited[i] = 0;
    }

    printf("\nBFS:\n");
    for (int i = 0; i < node_num; i++)
    {
        if (visited[i] == 0)
        {
            bfs(s_array, i, node_num, visited);
            printf("\n");
        }
    }

    return 0;
}

// 9 11 13 15 17 18 20 22 23 1 2 0 3 0 3 1 2 5 4 6 5 7 6
// 2 2 0