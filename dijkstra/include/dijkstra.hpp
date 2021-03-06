#ifndef _DIJKSTRA_H_
#define _DIJKSTRA_H_

#include <graph.hpp>


class Dijkstra
{
public:
    Dijkstra();
    ~Dijkstra();

    std::vector<int> find_path(Graph& g, std::size_t start, std::size_t end);

private:
    /* data */
};

#endif /* _DIJKSTRA_H_ */
