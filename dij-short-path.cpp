#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <unordered_map>
#include <algorithm>

using namespace std;

const int INF = numeric_limits<int>::max();

struct Edge {
    int to, weight;
};

using Graph = vector<vector<Edge>>;

vector<int> dijkstra(const Graph& graph, int start, vector<int>& dist) {
    int n = graph.size();
    dist.assign(n, INF);
    vector<int> prev(n, -1);
    dist[start] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.emplace(0, start);

    while (!pq.empty()) {
        int d = pq.top().first, u = pq.top().second;
        pq.pop();
        if (d > dist[u]) continue;
        for (const Edge& edge : graph[u]) {
            int v = edge.to, weight = edge.weight;
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                prev[v] = u;
                pq.emplace(dist[v], v);
            }
        }
    }
    return prev;
}

vector<int> reconstruct_path(int start, int end, const vector<int>& prev) {
    vector<int> path;
    for (int at = end; at != -1; at = prev[at]) path.push_back(at);
    reverse(path.begin(), path.end());
    return path.front() == start ? path : vector<int>();
}

void print_path(const vector<int>& path, const vector<string>& indexToCity) {
    for (int i = 0; i < path.size(); ++i) {
        cout << indexToCity[path[i]];
        if (i < path.size() - 1) cout << " -> ";
    }
    cout << endl;
}

int main() {
    unordered_map<string, int> cityToIndex = {
        {"Delhi", 0}, {"Mumbai", 1}, {"Bangalore", 2},
        {"Hyderabad", 3}, {"Chennai", 4}, {"Lucknow", 5}
    };

    vector<string> indexToCity = {
        "Delhi", "Mumbai", "Bangalore", "Hyderabad", "Chennai", "Lucknow"
    };

    Graph graph = {
        {{1, 1400}, {2, 2100}, {5, 500}},
        {{0, 1400}, {2, 1000}, {3, 700}},
        {{0, 2100}, {1, 1000}, {3, 570}, {4, 350}},
        {{1, 700}, {2, 570}, {4, 630}},
        {{2, 350}, {3, 630}},
        {{0, 500}}
    };

    string startCity = "Lucknow", endCity = "Bangalore";
    int start = cityToIndex[startCity], end = cityToIndex[endCity];

    vector<int> dist, prev = dijkstra(graph, start, dist);
    vector<int> path = reconstruct_path(start, end, prev);

    cout << "Shortest path from " << startCity << " to " << endCity << ": ";
    print_path(path, indexToCity);
    cout << "Total distance: " << dist[end] << " km" << endl;

    return 0;
}
