#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <locale.h>
#include <vector>
#include <stack>
#include <iostream>
using namespace std;
FILE* f;
stack<int> st;
vector<int> res;
bool flag;


void DFS(int start, int n, int** G) {

    st.push(start);
    while (!st.empty())
    {
        int v = st.top();
        int i;
        for (i = 0;i < n;i++)
            if (G[v][i]) // если есть связь прерываем цикл
                break;
        if (i == n) // когда пройдет весь цикл,
        {
            res.push_back(v); // вставляем элемент в конец вектора посещений
            st.pop(); // удаляет элемент из начала стека 
        }
        else
        {

            --G[v][i];
            --G[i][v];
            st.push(i);
        }

    }
}

int eiler(int n, int** G, int vert) {
    vector<int> deg(n); // динамический массив данных
    for (int i = 0; i < n; ++i) // цикл прохода по матрице
        for (int j = 0; j < n; ++j)
            deg[i] += G[i][j]; // в ячейку массива записывается кол-во связей одной вершины


    for (int i = 0;i < n;i++)
        if ((deg[i] > 0) && (deg[i] % 2 == 0))
            flag = true;
        else
        {
            flag = false;
            printf("Граф не содержит Эйлеровый цикл!\n");
            fprintf(f, "Граф не содержит Эйлеровый цикл!\n");
            return 0;
        }
    printf("Найден Эйлеров цикл:\n");
    fprintf(f, "Найден Эйлеров цикл:\n");

    int** H = new int* [n];
    for (int i = 0;i < n;i++)
        H[i] = new int[n];
    for (int k = 0;k < n;k++)
    {
        for (int i = 0;i < n;i++)
            for (int j = 0;j < n;j++)
                H[i][j] = G[i][j];
        DFS(k, n, &(&H)[0][0]);
        for (size_t j = 0; j < res.size();++j)
        {
            printf("%d->", res[j]);
            fprintf(f, "%d->", res[j]);
        }
        printf("\n");
        fprintf(f, "\n");
        res.clear();
    }
    return 0;
}

int main() {
    int how = -1;
    int n = 0;
    srand(time(NULL));
    setlocale(LC_ALL, "Russian");
    while (n <= 1)
    {
        printf("Введите количество вершин графа: ");
        scanf_s("%d", &n);
        if (n <= 1)
            printf("Задано слишком мало вершин!\n");
    }
    int** G = new int* [n];
    for (int i = 0;i < n;i++)
    {
        G[i] = new int[n];

    }
    while (how != 1 and how != 2)
    {
        menu:
            printf("Выберите способ заполнения матрицы\n1.Генератор случайных чисел\n2.Ввод чисел с клавиатуры\n3.Выход из программы\nВыбор: ");
            scanf_s("%d", &how);
            switch (how)
            {
            case(1):
                for (int i = 0; i < n; i++)
                {
                    for (int j = i; j < n; j++)
                    {
                        if (i == j)
                        {
                            G[i][j] = 0;
                        }
                        else if (i != j)
                        {
                            G[i][j] = rand() % 2;
                            G[j][i] = G[i][j];
                        }
                    }
                }
                break;
            case(2):
                for (int i = 0; i < n; i++)
                {
                    for (int j = 0; j < n; j++)
                    {
                        while (G[i][j] != 0 and G[i][j] != 1)
                        {
                            printf("\nG[%d][%d] = ", i, j);
                            scanf_s("%d", &G[i][j]);
                        }
                    }
                }
                break;
            case(3):
                return 0;
            default:
                printf("Выбран неверный вариант!\n");
            }
    }

    f = fopen("база", "w+");
    if (how == 1 || how == 2)
    {
        printf("Матрица смежности:\n");
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                printf("%d ", G[i][j]);
                fprintf(f, "%d ", G[i][j]);
            }
            printf("\n");
            fprintf(f, "\n");
        }
    }

    do
    {
        eiler(n, &(&G)[0][0], 0);
        goto menu;
    } while (flag != true);

    free(G);
    fclose(f);
}



