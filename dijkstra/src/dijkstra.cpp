#include <dijkstra.hpp>

#include <limits>
#include <string>
#include <queue>


class PriorityQueue
{
public:
    PriorityQueue();
    ~PriorityQueue();

    void push(uint32_t d, std::size_t v);
    void decrease(uint32_t d, std::size_t v);
    std::pair<uint32_t, std::size_t> remove_min();

private:
    std::vector<std::pair<uint32_t, std::size_t>> v_;
};

PriorityQueue::PriorityQueue()
{
    ;
}

PriorityQueue::~PriorityQueue()
{
    ;
}

void PriorityQueue::push(uint32_t distance, std::size_t vertex)
{
    v_.push_back({distance, vertex});
}

std::pair<uint32_t, std::size_t> PriorityQueue::remove_min()
{
    std::pair<uint32_t, std::size_t> p(v_[0].first, v_[0].second);
    auto it = v_.begin();
    for (auto i = v_.begin(); i != v_.end(); ++i)
    {
        if (i->first < p.first)
        {
            p.first = i->first;
            p.second = i->second;
            it = i;
        }
    }
    v_.erase(it);
    return p;
}

void PriorityQueue::decrease(uint32_t new_distance, std::size_t vertex)
{
    for (auto& i : v_)
    {
        if (i.second == vertex)
        {
            i.first = new_distance;
        }
    }
}

Dijkstra::Dijkstra()
{
    ;
}

Dijkstra::~Dijkstra()
{
    ;
}

std::vector<int> Dijkstra::find_path(Graph& g, std::size_t start, std::size_t end)
{
    const auto size = g.size();
    if (start > size || end > size)
    {
        throw std::string("out of range");
    }

    std::vector<uint32_t> distance(size, std::numeric_limits<uint32_t>::max());
    std::vector<int> prev(size, 0);
    std::vector<bool> visited(size, false);
    PriorityQueue queue;

    for (std::size_t i = 0; i < size; ++i)
    {
        queue.push(distance[i], i);
    }

    distance[start] = 0;
    queue.push(distance[start], start);
    prev[start] = -1;

    for (std::size_t i = 0; i < size; ++i)
    {
        auto p = queue.remove_min();
        visited[p.second] = true;

        for (std::size_t neighbor = 0; neighbor < size; ++neighbor)
        {
            if (g.get_edge(p.second, neighbor) > 0 && !visited[neighbor])
            {
                if (distance[p.second] + g.get_edge(p.second, neighbor) < distance[neighbor])
                {
                    distance[neighbor] = distance[p.second] + g.get_edge(p.second, neighbor);
                    queue.decrease(distance[neighbor], neighbor);
                    prev[neighbor] = p.second;
                }
            }
        }
    }

    for (const auto& d : distance)
    {
        std::cout << d << " ";
    }
    std::cout << std::endl;

    for (const auto& p : prev)
    {
        std::cout << p << " ";
    }
    std::cout << std::endl;


    auto i = end;
    auto path_len = 1;
    while (i != start)
    {
        path_len = path_len + 1;
        i = prev[i];
    }

    std::vector<int> path;
    auto j = 0;
    i = end;
    while (i != start)
    {
        path.push_back(i);
        i = prev[i];
        j = j + 1;
    }
    path.push_back(start);
    return path;
}
