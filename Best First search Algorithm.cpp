#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <set>
using namespace std;
// Comparator for the priority queue (min-heap based on heuristic)
struct CompareHeuristic {
  bool operator()(pair<string, int> a, pair<string, int> b) {
     return a.second > b.second;
 }
};
void bestFirstSearch(unordered_map<string, vector<string>> &graph,
  unordered_map<string, int> &heuristic,
  string start, string goal) {
  priority_queue<pair<string, int>, vector<pair<string, int>>, CompareHeuristic> pq;
  set<string> visited;
  pq.push({start, heuristic[start]});
  cout << "Path: ";
  while (!pq.empty()) {
    auto current = pq.top();
    pq.pop();
    string node = current.first;
    if (visited.find(node) != visited.end()) continue;
    cout << node << " ";
    visited.insert(node);
    if (node == goal) {
       cout << "\nGoal reached!" << endl;
       return;
    }
    for (string neighbor : graph[node]) {
      if (visited.find(neighbor) == visited.end()) {
        pq.push({neighbor, heuristic[neighbor]});
     }
 }
}
 cout << "\nGoal not reachable." << endl;
}
//main function
int main() {
 // Define the graph (adjacency list)
  unordered_map<string, vector<string>> graph = {
   {"A", {"B", "C"}},
   {"B", {"D", "E"}},
   {"C", {"F"}},
   {"D", {}},
   {"E", {"G"}},
   {"F", {}},
   {"G", {}}
   };
 // Define heuristic values for each node
  unordered_map<string, int> heuristic = {
   {"A", 6},
   {"B", 4},
   {"C", 5},
   {"D", 2},
   {"E", 3},
   {"F", 6},
   {"G", 0} // Goal
   };
   string start = "A";
   string goal = "G";
   bestFirstSearch(graph, heuristic, start, goal);
   return 0;
}
