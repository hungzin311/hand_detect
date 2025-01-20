//bell man
#include<bits/stdc++.h>
using namespace std;

const int maxn = 1e6 + 7;

int n, m, s;
int dist[maxn];
int neg[maxn];

vector<pair<int,pair<int,int>>> g;

void bellman(int s){
    dist[s] = 0;

    for(int i = 1; i < n; i++){
        for(auto x: g){
            int u = x.first;
            int v = x.second.first;
            int w = x.second.second;

            dist[v] = min(dist[v], dist[u] + w);
        }

    }
}

void negative(){
    for(int i = 0; i < n; i++){
        for(auto x:g){
            int u = x.first;
            int v = x.second.first;
            int w = x.second.second;
            if(dist[v] > dist[u] + w){
                dist[v] = dist[u] + w;
                neg[v] = 1;
            }
        }
    }
    return;
}

int main(){
    cin >> n >> m >> s;
    while(m--){
        int a,b,c;
        cin >> a >> b >> c;
        g.push_back(make_pair(a,make_pair(b,c)));
    }
    for(int i = 0; i < n; i++) dist[i] = maxn;

    bellman(s);
    negative();
    for(int i =0; i < n; i++){
        if(neg[i]) cout << "-INF" << endl;
        else if(dist[i] == maxn) cout << "Impossible" << endl;
        else cout << dist[i] << endl;
    }

}
