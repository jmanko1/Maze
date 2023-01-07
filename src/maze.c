#include <stdio.h>
#include <stdlib.h>
#include "maze.h"
#include "stack.h"

void generate_conns(w_t *maze, int *gen, int i, int j, int n)
{
    double random;
    int is_conn;
    *gen += 1;
    maze[i * n + j].visited = 1;

    if(i - 1 >= 0 && maze[(i - 1) * n + j].visited == 0)
    {
        random = (double)rand() / RAND_MAX * 2;
        is_conn = random;
        if(is_conn == 1)
        {
            maze[i * n + j].conn[0] = &(maze[(i - 1) * n + j]);
            maze[(i - 1) * n + j].conn[2] = &(maze[i * n + j]);
            generate_conns(maze, gen, i - 1, j, n);
        }
    }

    if(i + 1 < n && maze[(i + 1) * n + j].visited == 0)
    {
        random = (double)rand() / RAND_MAX * 2;
        is_conn = random;
        if(is_conn == 1)
        {
            maze[i * n + j].conn[2] = &(maze[(i + 1) * n + j]);
            maze[(i + 1) * n + j].conn[0] = &(maze[i * n + j]);
            generate_conns(maze, gen, i + 1, j, n);
        }
    }

    if(j - 1 >= 0 && maze[i * n + j - 1].visited == 0)
    {
        random = (double)rand() / RAND_MAX * 2;
        is_conn = random;
        if(is_conn == 1)
        {
            maze[i * n + j].conn[3] = &(maze[i * n + j - 1]);
            maze[i * n + j - 1].conn[1] = &(maze[i * n + j]);
            generate_conns(maze, gen, i, j - 1, n);
        }
    }

    if(j + 1 < n && maze[i * n + j + 1].visited == 0)
    {
        random = (double)rand() / RAND_MAX * 2;
        is_conn = random;
        if(is_conn == 1)
        {
            maze[i * n + j].conn[1] = &(maze[i * n + j + 1]);
            maze[i * n + j + 1].conn[3] = &(maze[i * n + j]);
            generate_conns(maze, gen, i, j + 1, n);
        }
    }
}

void generate_maze(w_t *maze, int *gen, int n)
{
    int i, j;
    int w = n*n;
    double ulam;
    int number;

    if(*gen != w)
    {
        do
        {
            for(i = 0; i < n; i++)
            {
                for(j = 0; j < n; j++)
                {
                    if(maze[i*n+j].visited == 0)
                    {
                        do
                        {
                            ulam = (double)rand() / RAND_MAX * 4;
                            number = ulam;
                            switch(number)
                            {
                                case 0:
                                    if(i - 1 >= 0 && maze[(i-1)*n +j].visited == 1)
                                    {
                                        maze[i*n+j].conn[0] = &(maze[(i-1)*n+j]);
                                        maze[(i-1)*n+j].conn[2] = &(maze[i*n+j]);
                                        generate_conns(maze, gen, i, j, n);
                                    }
                                break;

                                case 2:
                                    if(i + 1 < n && maze[(i+1)*n +j].visited == 1)
                                    {
                                        maze[i*n+j].conn[2] = &(maze[(i+1)*n+j]);
                                        maze[(i+1)*n+j].conn[0] = &(maze[i*n+j]);
                                        generate_conns(maze, gen, i, j, n);
                                    }
                                break;

                                case 3:
                                    if(j - 1 >= 0 && maze[i*n+j-1].visited == 1)
                                    {
                                        maze[i*n+j].conn[3] = &(maze[i*n+j-1]);
                                        maze[i*n+j-1].conn[1] = &(maze[i*n+j]);
                                        generate_conns(maze, gen, i, j, n);
                                    }
                                break;

                                case 1:
                                    if(j + 1 < n && maze[i*n+j+1].visited == 1)
                                    {
                                        maze[i*n+j].conn[1] = &(maze[i*n+j+1]);
                                        maze[i*n+j+1].conn[3] = &(maze[i*n+j]);
                                        generate_conns(maze, gen, i, j, n);
                                    }
                                break;
                            }
                        }
                        while(maze[i * n + j].visited == 0);
                    }
                }
            }
        }
        while(*gen != w);
    }
}

void draw_maze(w_t *maze, int n, int vp, int vk)
{
    int i, j;
    int a = 0, b = 0;
    int v = 0;

    printf("\n");
    for(i = 2; i < 2 * n + 1; i += 2)
    {
        printf("####");
        if(v == vp) printf("    ");
        else printf("####");
        v++;
    }
    printf("####\n");

    for(i = 0; i < 2 * n - 1; i++)
    {
        printf("####");
        if(i % 2 == 0)
        {
            for(j = 0; j < 2 * n - 1; j += 2)
            {
                if(a * n + b < 10)
                    printf(" 0%d ", a * n + b);
                else
                    printf(" %d ", a * n + b);
                if(maze[a*n+b].conn[1] == &(maze[a*n+b+1]))
                    printf("    ");
                else
                    printf("####");

                b++;
            }
        }
        else
        {
            for(j = 0; j < 2 * n - 1; j += 2)
            {
                if(maze[a*n+b].conn[2] == &(maze[(a+1)*n+b]))
                    printf("    ");
                else
                    printf("####");
                printf("####");
                b++;
            }
            a++;
        }

        b = 0;
        printf("\n");
    }

    v = a*n + b;
    for(i = 2; i < 2 * n + 1; i += 2)
    {
        printf("####");
        if(v == vk) printf("    ");
        else printf("####");
        v++;
    }
    printf("####\n");

    //for(i = 0; i < 2 * n - 1; i++)
      //  printf("####");
    //printf("    ####\n");
}

void dfs(w_t *maze, int vs, int vk, int n)
{
    stack_t stack;
    int *visited;
    int found;
    int v, u, i;
    int *path;
    w_t *pv;

    int *v_path = malloc(0);
    int v_length = 0;
    double length;

    init_stack(&stack);
    visited = malloc(sizeof(int) * n);
    for(i = 0; i < n; i++)
        visited[i] = 0;

    path = malloc(sizeof(int) * n);
    path[vs] = -1;
    push(&stack, vs);
    visited[vs] = 1;
    found = 0;

    while(stack.data != NULL)
    {
        v = top(&stack);
        pop(&stack);

        if(v == vk)
        {
            found = 1;
            break;
        }

        for(i = 0; i < 4; i++)
        {
            pv = maze[v].conn[i];
            if(pv != NULL)
            {
                u = pv->n;
                if(visited[u] == 0)
                {
                    path[u] = v;
                    push(&stack, u);
                    visited[u] = 1;
                }
            }
        }
    }

    if(found == 0) printf("Brak sciezki\n");
    else
    {
        while(v > -1)
        {
            v_length++;
            v_path = realloc(v_path, sizeof(int) * v_length);
            v_path[v_length - 1] = v;
            v = path[v];
        }
    }
    
    printf("\nŚcieżka: ");
    for(i = 0; i < v_length; i++)
    {
        printf("%d ", v_path[i]);
        if(v_path[i] != vs)
                printf("-> ");
    }

    for(i = 1; i < v_length; i++)
        length += 0.5 * (maze[v_path[i]].waga + maze[v_path[i - 1]].waga);

    printf("\nDlugość ścieżki: %g\n\n", length);

    free(stack.data);
    free(visited);
    free(path);
    free(v_path);
}
