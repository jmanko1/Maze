#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "maze.h"

int main(int argc, char **argv)
{
    int k = argc > 1 ? atoi(argv[1]) : 5;
    int vp = argc > 2 ? atoi(argv[2]) : 0;
    int vk = argc > 3 ? atoi(argv[3]): k*k-1;

    if(k > 10 || k < 5)
    {
        fprintf(stderr, "%s: Podano nieprawidłową długość krawędzi. Długość krawędzi musi być w przedziale od 5 do 10 włącznie\n", argv[0]);
        return 1;
    }
    else if(vp < 0 || vp >= k)
    {
        fprintf(stderr, "%s: Wybrano nieprawidłowy wierzchołek początkowy. Wierzchołek początkowy musi być na górnej krawędzi labiryntu\n", argv[0]);
        return 1;
    }
    else if(vk < k*k-k || vk >= k*k)
    {
        fprintf(stderr, "%s: Wybrano nieprawidłowy wierzchołek końcowy. Wierzchołek końcowy musi być na dolnej krawędzi labiryntu\n", argv[0]);
        return 1;
    }

    int w = k*k;
    int i, j;
    double ulam;
    
    w_t *maze;
    int gen = 0;

    maze = malloc(sizeof *maze * w);

    srand(time(NULL));
    for(i = 0; i < w; i++)
    {
        ulam = (double)rand() / RAND_MAX * 10;
	ulam *= 100;
	ulam = floor(ulam);
	ulam /= 100;

        maze[i].waga = ulam;
        maze[i].n = i;
        maze[i].conn = malloc(sizeof(w_t) * 4);
    }

    maze[0].visited = 1;
    gen++;
    
    generate_maze(maze, &gen, k);
    draw_maze(maze, k, vp, vk);
    dfs(maze, vk, vp, w);

    for(i = 0; i < w; i++)
        free(maze[i].conn);
    free(maze);

    return 0;
}
