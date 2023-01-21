#ifndef MAZE_H
#define MAZE_H

typedef struct wezel
{
    int n;
    double waga;
    int visited;
    struct wezel **conn;
} w_t;

void generate_conns(w_t *, int *, int, int, int);
void generate_maze(w_t *, int *, int);
void draw_maze(w_t *, int, int, int);
void dfs(w_t *, int, int, int);

#endif // MAZE_H
