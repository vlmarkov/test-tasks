#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <vector>
#include <iostream>


class Graph
{
private:
    std::size_t vertices_{0};
    std::vector<std::vector<bool>> graph_;

public:
    Graph(const std::size_t n);
    ~Graph() = default;

    void set_edge(std::size_t i, std::size_t j, std::size_t value);
    bool get_edge(std::size_t i, std::size_t j) const;

    void print() const;
    std::size_t size() const;
};

void dfs(const Graph& graph, const size_t vertex = 0);
void bfs(const Graph& graph, const size_t start, const size_t end);

#endif /* _GRAPH_H_ */
