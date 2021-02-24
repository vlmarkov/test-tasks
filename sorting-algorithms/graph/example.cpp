#include <graph.hpp>

#include <iostream>


int main(int argc, char const *argv[])
{
    Graph g(3);
    g.set_edge(0, 0, false);
    g.set_edge(0, 1, true);
    g.set_edge(0, 2, false);

    g.set_edge(1, 0, false);
    g.set_edge(1, 1, false);
    g.set_edge(1, 2, true);

    g.set_edge(2, 0, false);
    g.set_edge(2, 1, false);
    g.set_edge(2, 2, false);

    g.bfs(0, 2);
    g.dfs(0);
    g.print();

    return 0;
}
