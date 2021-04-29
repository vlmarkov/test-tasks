#include <dijkstra.hpp>

#include <algorithm>
#include <limits>
#include <string>
#include <queue>


class PriorityQueue
{
public:
    PriorityQueue() = default;
    ~PriorityQueue() = default;

    void push(uint32_t distance, std::size_t vertex);
    void decrease(uint32_t distance, std::size_t vertex);
    std::pair<uint32_t, std::size_t> min();

private:
    std::vector<std::pair<uint32_t, std::size_t>> heap_;

    struct comporator
    {
        bool operator() (const std::pair<uint32_t, std::size_t>& a,
                         const std::pair<uint32_t, std::size_t>& b)
        {
            return a.first > b.first ? true : false;
        }
    };
};

void PriorityQueue::push(uint32_t distance, std::size_t vertex)
{
    heap_.push_back({distance, vertex});
    std::push_heap(heap_.begin(), heap_.end(), comporator());
}

std::pair<uint32_t, std::size_t> PriorityQueue::min()
{
    std::pop_heap(heap_.begin(), heap_.end(), comporator());
    const auto minimum = heap_.back();
    heap_.pop_back();
    return minimum;
}

void PriorityQueue::decrease(uint32_t new_distance, std::size_t search_vertex)
{
    for (auto& [distance, vertex] : heap_) {
        if (vertex == search_vertex) {
            distance = new_distance;
            break;
        }
    }
    std::make_heap(heap_.begin(), heap_.end(), comporator());
}


std::vector<int> Dijkstra::find_path(Graph& graph, std::size_t start, std::size_t end)
{
    const auto size = graph.size();
    if (start > size || end > size)
    {
        throw std::string("out of range");
    }

    std::vector<uint32_t> distance(size, std::numeric_limits<uint32_t>::max());
    std::vector<int> prev(size, 0);
    std::vector<bool> visited(size, false);
    PriorityQueue priority_queue;

    for (std::size_t i = 0; i < size; ++i)
    {
        priority_queue.push(distance[i], i);
    }

    distance[start] = 0;
    priority_queue.push(distance[start], start);
    prev[start] = -1;

    for (std::size_t i = 0; i < size; ++i)
    {
        auto [min_distance, min_vertex] = priority_queue.min();
        visited[min_vertex] = true;

        for (std::size_t neighbor = 0; neighbor < size; ++neighbor)
        {
            if (graph.get_edge(min_vertex, neighbor) > 0 && !visited[neighbor])
            {
                if (distance[min_vertex] + graph.get_edge(min_vertex, neighbor) < distance[neighbor])
                {
                    distance[neighbor] = distance[min_vertex] + graph.get_edge(min_vertex, neighbor);
                    priority_queue.decrease(distance[neighbor], neighbor);
                    prev[neighbor] = min_vertex;
                }
            }
        }
    }

    {
        std::cout << "distance: ";
        for (const auto& d : distance)
            std::cout << d << " ";
        std::cout << std::endl;
    }

    {
        std::cout << "index: ";
        for (const auto& p : prev)
            std::cout << p << " ";
        std::cout << std::endl;
    }

    {
        auto i = end;
        while (i != start)
        {
            i = prev[i];
        }
    }

    std::vector<int> path;
    while (end != start)
    {
        path.push_back(end);
        end = prev[end];
    }
    path.push_back(start);

    return path;
}
