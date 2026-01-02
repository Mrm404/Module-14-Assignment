#include <bits/stdc++.h>
using namespace std;

class TarjanSCC {
private:
    vector<vector<int>> graph;
    vector<int> index, lowlink;
    vector<bool> onStack;
    stack<int> st;

    int currentIndex;
    vector<vector<int>> sccs;

    void dfs(int u) {
        index[u] = lowlink[u] = currentIndex++;
        st.push(u);
        onStack[u] = true;

        for (int v : graph[u]) {
            if (index[v] == -1) {
                
                dfs(v);
                lowlink[u] = min(lowlink[u], lowlink[v]);
            } 
            else if (onStack[v]) {

                lowlink[u] = min(lowlink[u], index[v]);
            }
        }

        if (lowlink[u] == index[u]) {
            vector<int> scc;
            int v;
            do {
                v = st.top();
                st.pop();
                onStack[v] = false;
                scc.push_back(v);
            } while (v != u);

            sccs.push_back(scc);
        }
    }

public:
    TarjanSCC(int n) {
        graph.resize(n);
        index.assign(n, -1);
        lowlink.assign(n, -1);
        onStack.assign(n, false);
        currentIndex = 0;
    }

    void addEdge(int u, int v) {
        graph[u].push_back(v);
    }

    vector<vector<int>> tarjan_scc() {
        for (int i = 0; i < graph.size(); i++) {
            if (index[i] == -1) {
                dfs(i);
            }
        }
        return sccs;
    }
};


int main() {
    int n = 8;
    TarjanSCC tarjan(n);

    tarjan.addEdge(0, 1);
    tarjan.addEdge(1, 2);
    tarjan.addEdge(2, 0);
    tarjan.addEdge(2, 3);
    tarjan.addEdge(3, 4);
    tarjan.addEdge(4, 5);
    tarjan.addEdge(5, 3);
    tarjan.addEdge(6, 5);
    tarjan.addEdge(6, 7);
    tarjan.addEdge(7, 6);

    vector<vector<int>> sccs = tarjan.tarjan_scc();

    cout << "Strongly Connected Components:\n";
    for (auto &scc : sccs) {
        for (int v : scc)
            cout << v << " ";
        cout << endl;
    }

    return 0;
}
