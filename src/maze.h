#ifndef MAZE_H
#define MAZE_H

typedef struct wezel
{
    int n;
    double waga;
    int visited;
    struct wezel **conn;
} w_t;

void generate_conns(w_t *, int *, int i, int j, int n);
void generate_maze(w_t *, int *, int n);
void draw_maze(w_t *, int n, int vp, int vk);
void dfs(w_t *, int vs, int vk, int n);

#endif // MAZE_H
