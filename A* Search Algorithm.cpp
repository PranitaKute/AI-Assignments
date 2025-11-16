#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <set>
#include <limits>
using namespace std;
struct Node {
string name;
int g; // cost so far
int h; // heuristic
int f; // total cost
vector<string> path;
Node(string n, int g_cost, int h_cost, vector<string> p) {
  name = n;
  g = g_cost;
  h = h_cost;
  f = g + h;
  path = p;
  path.push_back(n);
  }
};
// Comparator for priority queue (min-heap)
struct CompareNode {
 bool operator()(Node const &a, Node const &b) {
 return a.f > b.f;
 }
};
void aStarSearch(unordered_map<string, vector<pair<string, int>>> &graph,
    unordered_map<string, int> &heuristic,
    string start, string goal)
priority_queue<Node, vector<Node>, CompareNode> pq;
 set<string> visited;
 pq.push(Node(start, 0, heuristic[start], {}));
 while (!pq.empty()) {
   Node current = pq.top();
   pq.pop();
   if (visited.find(current.name) != visited.end())
     continue;
    visited.insert(current.name);
   if (current.name == goal) {
     cout << "Path found: ";
   for (const string &step : current.path) {
     cout << step << " ";
   }
   cout << "\nTotal cost: " << current.g << endl;
   return;
 }
 for (auto neighbor : graph[current.name]) {
   string next = neighbor.first;
   int cost = neighbor.second;
   if (visited.find(next) == visited.end()) {
     int new_g = current.g + cost;
     int h = heuristic[next];
     pq.push(Node(next, new_g, h, current.path));
   }
 }
 }
 cout << "Goal not reachable." << endl;
}

int main() {
 // Graph with edge costs
 unordered_map<string, vector<pair<string, int>>> graph = {
 {"A", {{"B", 1}, {"C", 3}}},
 {"B", {{"D", 3}, {"E", 1}}},
 {"C", {{"F", 5}}},
 {"D", {}},
 {"E", {{"G", 2}}},
 {"F", {}},
 {"G", {}}
 };
 // Heuristic values (estimated cost to goal)
 unordered_map<string, int> heuristic = {
 {"A", 7},
 {"B", 6},
 {"C", 5},
 {"D", 3},
 {"E", 2},
 {"F", 4},
 {"G", 0} // Goal node
 };
 string start = "A";
 string goal = "G";
 aStarSearch(graph, heuristic, start, goal);
 return 0;
}
