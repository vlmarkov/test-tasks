#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <queue>
#include <vector>
#include <iostream>


class Graph
{
private:
    std::size_t vertices_;
    std::vector<std::vector<bool>> graph_;
    std::vector<bool> visited_;

    void dfs_(const size_t vertex)
    {
        std::cout << "[dfs] = " << vertex << std::endl;
        visited_[vertex] = true;
        for (std::size_t neighbor = 0; neighbor < vertices_; ++neighbor)
        {
            if (graph_[vertex][neighbor] && !visited_[neighbor])
            {
                visited_[neighbor] = true;
                dfs_(neighbor);
            }
        }
    }

public:
    Graph(const std::size_t n)
    {
        vertices_ = n;
        graph_ = std::vector<std::vector<bool>>(n, std::vector<bool>(n, false));
        visited_ = std::vector<bool>(n, false);
    }

    ~Graph()
    {
        ;
    }

    void set_edge(std::size_t i, std::size_t j, std::size_t value)
    {
        if (i > vertices_ || j > vertices_)
        {
            throw "not in range";
        }
        graph_[i][j] = value;
    }

    bool get_edge(std::size_t i, std::size_t j) const
    {
        if (i > vertices_ || j > vertices_)
        {
            throw "not in range";
        }
        return graph_[i][j];
    }

    void print()
    {
        for (const auto& g : graph_)
        {
            for (const auto& i : g)
            {
                std::cout << i << " ";
            }
            std::cout << std::endl;
        }
    }

    void dfs(const size_t start = 0)
    {
        visited_.clear();
        dfs_(start);
    }

    void bfs(const size_t start, const size_t end)
    {
        std::queue<std::size_t> queue;

        visited_.clear();

        visited_[start] = true;
        queue.push(start);

        while (!queue.empty())
        {
            auto v = queue.front();
            queue.pop();
            std::cout << "[bfs] = " << v << std::endl;
            for (std::size_t neighbor = 0; neighbor < vertices_; ++neighbor)
            {
                if (graph_[v][neighbor] && !visited_[neighbor])
                {
                    queue.push(neighbor);
                    visited_[neighbor] = true;
                    if (neighbor == end)
                    {
                        std::cout << "[bfs] = " << neighbor << std::endl;
                        std::cout << "[bfs][found] route from " << start << " to " << end << std::endl;
                        return;
                    }
                }
            }
        }
        std::cout << "[bfs][not found] route from " << start << " to " << end << std::endl;
    }
};

#endif /* _GRAPH_H_ */
