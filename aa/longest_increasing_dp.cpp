#include<bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 7;
int seg[4*maxn];
int a[maxn];
int n;

void update(int id, int l , int r, int i, int val){
    if(i < l || r < i) return;

    if(l == r){
        seg[id] = max(seg[id], val);
        return;
    }

    int mid = (l+r) >> 1;
    if(i <= mid) update(id*2, l, mid, i, val);
    else update(id*2+1, mid+1, r, i, val);

    seg[id] = max(seg[id*2], seg[id*2+1]);
}

int get(int id, int l, int r, int u, int v){
    if(u > r || v < l){
        return 0;
    }

    if(l >= u && r <= v){
        return seg[id];
    }

    int mid = (l+r) >> 1;
    int get1 = get(id*2, l, mid, u, v);
    int get2 = get(id*2+1, mid+1, r, u, v);

    return max(get1, get2);
}


int main(){
    cin >> n;
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }

    for(int i= 0; i < n; i++){
        int num = a[i];
        int max_lis = get(1, 1, maxn, 1, num-1);
        update(1, 1, maxn, num, max_lis+1);
    }

    cout << get(1,1,maxn, 1, maxn);

}
