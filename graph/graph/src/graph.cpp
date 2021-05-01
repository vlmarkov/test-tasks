#include <graph.hpp>

#include <queue>


Graph::Graph(const std::size_t n) : vertices_{n}
{
    graph_ = std::vector<std::vector<bool>>(n, std::vector<bool>(n, false));
}

void Graph::set_edge(std::size_t i, std::size_t j, std::size_t value)
{
    graph_.at(i).at(j) = value;
}

bool Graph::get_edge(std::size_t i, std::size_t j) const
{
    return graph_.at(i).at(j);
}

void Graph::print() const
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

std::size_t Graph::size() const
{
    return vertices_;
}

static void dfs_(const Graph& graph, std::vector<bool>& visited, const size_t vertex)
{
    std::cout << "[dfs] = " << vertex << std::endl;
    visited[vertex] = true;

    for (std::size_t neighbor = 0; neighbor < graph.size(); ++neighbor)
    {
        if (graph.get_edge(vertex, neighbor) && !visited[neighbor])
        {
            visited[neighbor] = true;
            dfs_(graph, visited, neighbor);
        }
    }
}

void dfs(const Graph& graph, const size_t vertex)
{
    auto visited = std::vector<bool>(graph.size(), false);
    dfs_(graph, visited, vertex);
}

void bfs(const Graph& graph, const size_t start, const size_t end)
{
    std::queue<std::size_t> queue;

    auto visited = std::vector<bool>(graph.size(), false);

    visited[start] = true;
    queue.push(start);

    while (!queue.empty())
    {
        auto v = queue.front();
        queue.pop();

        std::cout << "[bfs] = " << v << std::endl;

        for (std::size_t neighbor = 0; neighbor < graph.size(); ++neighbor)
        {
            if (graph.get_edge(v, neighbor) && !visited[neighbor])
            {
                queue.push(neighbor);
                visited[neighbor] = true;
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
