#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <vector>
#include <iostream>


class Graph
{
public:
    explicit Graph(const std::size_t vertices);
    ~Graph() = default;

    void set_edge(const std::size_t i, const std::size_t j, const std::size_t value);
    uint32_t get_edge(const std::size_t i, const std::size_t j) const;
    std::size_t size() const;
    void print() const;

private:
    std::size_t vertices_;
    std::vector<std::vector<uint32_t>> graph_;
};

#endif /* _GRAPH_H_ */
