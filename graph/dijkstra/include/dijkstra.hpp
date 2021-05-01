#ifndef _DIJKSTRA_H_
#define _DIJKSTRA_H_

#include <graph.hpp>


class Dijkstra
{
public:
    Dijkstra() = default;
    ~Dijkstra() = default;

    std::vector<int> find_path(Graph& g, std::size_t start, std::size_t end);
};

#endif /* _DIJKSTRA_H_ */
