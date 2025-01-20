// djikstra
#include<bits/stdc++.h>
using namespace std;

const int maxn = 1e6 + 7;

struct node{
    int u;
    int dist_u;
};

struct cmp{
    bool operator() (node a, node b){
        return a.dist_u > b.dist_u;
    }
};

int n, m, s;
vector<pair<int,int>> g[maxn];
int optimized[maxn];
int dist[maxn];
priority_queue<node, vector<node>, cmp> q;

void dijkstra(int s){
    dist[s] = 0;
    q.push({s, dist[s]});
    while(!q.empty()){
        auto x = q.top();
        q.pop();

        int ubest = x.u;
        if(optimized[ubest]) continue;

        optimized[ubest] = 1;

        for(auto x : g[ubest]){
            int v = x.first;
            int w = x.second;
            if(dist[ubest] +  w < dist[v]){
                dist[v] = dist[ubest] +  w;
                q.push({v, dist[v]});
            }
        }

    }

}

int main(){
    cin >> n >> m >> s;
    while(m--){
        int a,b,c;
        cin >> a >> b >> c;
        g[a].push_back(make_pair(b,c));
    }
    for(int i= 1; i < n;i ++) dist[i] = maxn;
    dijkstra(s);
    for(int i= 0; i < n; i++) cout << dist[i] << " ";
}
