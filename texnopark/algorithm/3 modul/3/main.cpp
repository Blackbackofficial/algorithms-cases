//Задача 3. «Города» (4 балла) Требуется отыскать самый выгодный маршрут между городами.
//Требования: время работы O((N+M)logN), где N-количество городов, M-известных дорог между ними.

#include <iostream>
#include <vector>
#include <queue>
#include <list>
#include <utility>
#include <set>

class IGraph {
public:
    virtual ~IGraph() = default;
    virtual void AddEdge(int from, int to, int weight) = 0;
    virtual int VerticesCount() const  = 0;
    virtual std::vector<std::pair<int, int>> GetNextVertices(int vertex) const = 0;
    virtual std::vector<std::pair<int, int>> GetPrevVertices(int vertex) const = 0;
};

class CListGraph : public IGraph {
public:
    explicit CListGraph(int n) {
        ver_size = n;
        contiguity.resize(n);
        for (int i = 0; i < n; ++i) {
            contiguity.resize(0);
        }
    };

    void AddEdge(int from, int to, int weight) override {
        contiguity[from].push_front(std::make_pair(to, weight));
        contiguity[to].push_front(std::make_pair(from, weight));
    };

    std::vector<std::pair<int, int>> GetNextVertices(int vertex) const override {
        std::vector<std::pair<int, int>> answer;
        for (const auto & i : contiguity[vertex]) {
            answer.push_back(i);
        }
        return answer;
    };

    std::vector<std::pair<int, int>> GetPrevVertices(int vertex) const override {
        std::vector<std::pair<int, int>> answer;
        for (const auto & i : contiguity)
            for (const auto & j : i)
                if (j.first == vertex)
                    answer.push_back(j);
        return answer;
    };

    int VerticesCount() const override {
        return ver_size;
    };

    ~CListGraph() override = default;

private:
    int ver_size;
    std::vector<std::list<std::pair<int, int>>> contiguity;
};

int Dekstr(const IGraph& graph, int from = 0, int to = 0) {
    std::vector<int> _way(graph.VerticesCount(), 200000);
    _way[from] = 0;
    std::set<std::pair<int, int>> q;
    q.insert({0, from});
    while (!q.empty()) {
        int v = q.begin()->second;
        q.erase(q.begin());

        std::vector<std::pair<int, int>> _ways = graph.GetNextVertices(v);
        for (auto c : _ways) {
            if (_way[c.first] > _way[v] + c.second) {
                _way[c.first] = _way[v] + c.second;
                q.insert({_way[c.first], c.first});
            }
        }
    }
    return _way[to];
}

int main() {
    int N, M, from_u, to_u, from, to, time;
    std::cin >> N >> M;
    CListGraph graph(N);

    for (int i = 0; i < M; i++) {
        std::cin >> from >> to >> time;
        graph.AddEdge(from, to, time);
    }

    std::cin >> from_u >> to_u;
    std::cout << Dekstr(graph, from_u, to_u);

    return 0;
}