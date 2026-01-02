#include <bits/stdc++.h>
using namespace std;

bool checkMapping(const vector<vector<int>>& g1,
                  const vector<vector<int>>& g2,
                  const vector<int>& perm) {
    int n = g1.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (g1[i][j] != g2[perm[i]][perm[j]])
                return false;
        }
    }
    return true;
}

bool are_isomorphic(vector<vector<int>> g1, vector<vector<int>> g2) {
    int n = g1.size();
    if (g2.size() != n)
        return false;

    vector<int> deg1(n, 0), deg2(n, 0);
    int edges1 = 0, edges2 = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (g1[i][j]) {
                deg1[i]++;
                if (i < j) edges1++;
            }
            if (g2[i][j]) {
                deg2[i]++;
                if (i < j) edges2++;
            }
        }
    }

    if (edges1 != edges2)
        return false;

    sort(deg1.begin(), deg1.end());
    sort(deg2.begin(), deg2.end());
    if (deg1 != deg2)
        return false;

    vector<int> perm(n);
    iota(perm.begin(), perm.end(), 0);

    do {
        if (checkMapping(g1, g2, perm))
            return true;
    } while (next_permutation(perm.begin(), perm.end()));

    return false;
}

int main() {
    vector<vector<int>> graph1 = {
        {0,1,1,0},
        {1,0,1,1},
        {1,1,0,0},
        {0,1,0,0}
    };

    vector<vector<int>> graph2 = {
        {0,1,0,1},
        {1,0,1,1},
        {0,1,0,0},
        {1,1,0,0}
    };

    if (are_isomorphic(graph1, graph2))
        cout << "Graphs are Isomorphic\n";
    else
        cout << "Graphs are NOT Isomorphic\n";

    return 0;
}
