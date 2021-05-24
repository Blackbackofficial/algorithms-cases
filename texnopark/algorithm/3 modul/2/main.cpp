// Задача 2. Количество различных путей (3 балла). Дан невзвешенный неориентированный граф.
// В графе может быть несколько кратчайших путей между какими-то вершинами.
// Найдите количество различных кратчайших путей между заданными вершинами.
#include <iostream>
#include <queue>
#include <vector>
#include <list>

class IGraph {
public:
    virtual ~IGraph() = default;
    virtual void AddEdge(int from, int to) = 0;
    virtual int VerticesCount() const = 0;
    virtual std::vector<int> GetNextVertices(int ver) const = 0;
    virtual std::vector<int> GetPrevVertices(int ver) const = 0;
};

class CListGraph : public IGraph {
public:
    explicit CListGraph(int n) : ver_size(n) {
        contiguity.resize(n);
        for (int i = 0; i < n; ++i)
            contiguity.resize(0);
    };
    ~CListGraph() override = default;

    [[nodiscard]] int VerticesCount() const override {
        return ver_size;
    };

    std::vector<int> GetNextVertices(int ver) const override {
        std::vector<int> answer;
        for (int i : contiguity[ver])
            answer.push_back(i);
        return answer;
    };

    std::vector<int> GetPrevVertices(int ver) const override {
        std::vector<int> answer;
        for (int i = 0; i < contiguity.size(); ++i)
            for (auto j = contiguity[i].begin(), end = contiguity[i].end(); j != end; ++j)
                if (*j == ver)
                    answer.push_back(i);
        return answer;
    };

    void AddEdge(int from, int to) override {
        contiguity[from].push_front(to);
        contiguity[to].push_front(from);
    };

private:
    int ver_size;
    std::vector<std::list<int>> contiguity;
};

int Way(const IGraph& graph, int u, int w) {
    std::vector<std::pair<int, int>> fortunes(graph.VerticesCount());
    std::queue<int> q;

    q.push(u);
    fortunes[u].second = 1;

    while (!q.empty()) {
        int vert = q.front();
        q.pop();
        auto nextVert = graph.GetNextVertices(vert);

        for (auto i : nextVert) {
            if (!fortunes[i].second) {
                fortunes[i].first = fortunes[vert].first + 1;
                fortunes[i].second = fortunes[vert].second;
                q.push(i);
            } else if (fortunes[i].first == fortunes[vert].first + 1)
                fortunes[i].second += fortunes[vert].second;
        }
    }
    return fortunes[w].second;
}

int main() {
    int v;
    std::cin >> v;
    int n;
    std::cin >> n;
    CListGraph graph(v);
    for (int i = 0; i < n; ++i) {
        int from;
        std::cin >> from;
        int to;
        std::cin >> to;
        graph.AddEdge(from, to);
    }

    int u;
    int w;
    std::cin >> u;
    std::cin >> w;

    std::cout << Way(graph, u, w);
}