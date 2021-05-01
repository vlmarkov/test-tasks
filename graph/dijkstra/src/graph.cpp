#include <graph.hpp>


Graph::Graph(const std::size_t vertices) : vertices_(vertices)
{
    graph_ = std::vector<std::vector<uint32_t>>(vertices_, std::vector<uint32_t>(vertices_, 0));
}

void Graph::set_edge(const std::size_t i, const std::size_t j, const std::size_t value)
{
    graph_.at(i).at(j) = value;
}

uint32_t Graph::get_edge(const std::size_t i, const std::size_t j) const
{
    return graph_.at(i).at(j);
}

std::size_t Graph::size() const
{
    return vertices_;
}

void Graph::print() const
{
    for (const auto& g : graph_)
    {
        for (const auto& i : g)
        {
            std::cout << i << "\t";
        }
        std::cout << std::endl;
    }
}
