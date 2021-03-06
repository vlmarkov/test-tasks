#include <graph.hpp>
#include <dijkstra.hpp>

#include <iostream>


int main(int argc, char const *argv[])
{
    Graph g(5);
    g.set_edge(0, 0, 0);
    g.set_edge(0, 1, 10);
    g.set_edge(0, 2, 0);
    g.set_edge(0, 3, 30);
    g.set_edge(0, 4, 100);

    g.set_edge(1, 0, 10);
    g.set_edge(1, 1, 0);
    g.set_edge(1, 2, 50);
    g.set_edge(1, 3, 0);
    g.set_edge(1, 4, 0);

    g.set_edge(2, 0, 0);
    g.set_edge(2, 1, 50);
    g.set_edge(2, 2, 0);
    g.set_edge(2, 3, 20);
    g.set_edge(2, 4, 10);

    g.set_edge(3, 0, 30);
    g.set_edge(3, 1, 0);
    g.set_edge(3, 2, 20);
    g.set_edge(3, 3, 0);
    g.set_edge(3, 4, 60);

    g.set_edge(4, 0, 100);
    g.set_edge(4, 1, 0);
    g.set_edge(4, 2, 10);
    g.set_edge(4, 3, 60);
    g.set_edge(4, 4, 0);

    g.print();

    Dijkstra d;
    auto path = d.find_path(g, 0, 4);
    for (auto p : path)
    {
        std::cout << p << " ";
    }
    std::cout << std::endl;
    return 0;
}
