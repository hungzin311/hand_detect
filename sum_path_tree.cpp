// Sum path tree
#include<bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 1;

int n;
vector<pair<int,int>> g[maxn];
int root;
int d[maxn];
int f[maxn];
int p[maxn];
int num[maxn];

void dfs1(int u){
    for(auto x: g[u]){
        int v = x.first;
        int w = x.second;
        if(p[v] == 0){
            p[v] = u;
            dfs1(v);
            d[u] = d[u] + d[v] + num[v]*w;
            num[u] += num[v];
        }

    }
}

void dfs2(int u){
    for(auto x: g[u]){
        int v = x.first;
        int w = x.second;

        if(p[v] == 0){
            f[v] = f[u] -w*num[v] + w*(n-num[v]);
            p[v] = u;
            dfs2(v);
        }
    }
}

int main(){
    cin >> n;
    for(int i = 1; i < n; i++){
        int u,v,w;
        cin >> u >> v >> w;
        g[u].push_back(make_pair(v,w));
        g[v].push_back(make_pair(u,w));
    }

    for(int v = 1; v <= n; v++) num[v] = 1;
    root = 1;
    p[root] = root;
    dfs1(root);

    for(int v = 1; v <= n; v++) p[v] = 0;
    root = 1;
    f[root] = d[root];
    p[root] = root;
    dfs2(root);

    int ans = 0;
    for(int v = 1; v <= n; v++) ans = max(ans, f[v]);
    cout << ans;
}

