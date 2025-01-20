// strong connected
#include<bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 7;

int n, m;
int low[maxn];
int num[maxn];
int timedfs;
int deleted[maxn];
int scc;
vector <int> g[maxn];
stack <int> st;

void dfs(int u){
    num[u] = low[u] = ++timedfs;
    st.push(u);
    for(int v: g[u]){
        if(deleted[v]) continue;
        if(!num[v]){
            dfs(v);
            low[u] = min(low[u], low[v]);
        }
        else low[u] = min(low[u], num[v]);
    }

    if(low[u] == num[u]){
        scc++;
        int v;
        do{
            v = st.top();
            st.pop();
            deleted[v] = 1;
        }
        while(v != u);
    }

}
int main(){
    cin >> n >> m;
    while(m--){
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
    }

    for(int i= 1; i <=n; i++){
        if(!num[i]) dfs(i);
    }
    cout << scc;
}

