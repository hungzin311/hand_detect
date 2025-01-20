#include <bits/stdc++.h>
using namespace std;
#define MAX 50

int n, K, Q;
int d[MAX];    // d[i] is the demand at point i
int x[MAX];    // x[i] is the next point of i (i = 1,...,n), x[i] ∈ {0, 1,..., n}
int y[MAX];    // y[k] is the start point of route k
int load[MAX]; // load[k] is the current load of route k
int c[MAX][MAX];
int visited[MAX];  // visited[i] = 1 means client point i has been visited
int segments;  // number of segments accumulated
int nbRoutes;  // number of routes
int ans;       // number of solutions found
int lower = 1e7 + 9;

void sol2(){
    for (int k = 1; k <= K; k++) {
        int s = y[k];
        printf("Route[%d]: 0 ", k);
        for (int v = s; v != 0; v = x[v]) {
            printf("%d ", v);
        }
        printf("0\n");
    }
    printf("---------------\n");
}
void solution() {
    ans++;
    int sum = 0;
    for (int k = 1; k <= K; k++) {
        int s = y[k];
//        printf("Route[%d]: 0 ", k);
        sum += c[0][s];
        for (int v = s; v != 0; v = x[v]) {
//            printf("%d ", v);
            sum+= c[v][x[v]];
        }
//        printf("0\n");
    }
    if(sum < lower){
        lower = sum;
        sol2();
    }
}


int checkX(int v, int k) {
    if (v > 0 && visited[v]) return 0;   // If v is already visited, return false
    if (load[k] + d[v] > Q) return 0;    // If load exceeds limit, return false
    return 1;
}

void input() {
    scanf("%d %d %d", &n, &K, &Q); // Read values for n, K, and Q
    for (int i = 1; i <= n; i++) {
        scanf("%d", &d[i]);        // Read the demands for each point
    }
    d[0] = 0;  // The demand at point 0 is 0 (the depot)

    for(int i=0; i<= n; i++){
        for(int j=0; j <=n; j++) scanf("%d", &c[i][j]);
    }
}

void TRY_X(int s, int k) {
    for (int v = 0; v <= n; v++) {
        if (checkX(v, k)) {
            x[s] = v;
            visited[v] = 1;
            load[k] += d[v];
            segments++;

            if (v > 0) {
                TRY_X(v, k);
            } else {
                if (k == K) {
                    if (segments == n + nbRoutes) solution();
                } else {
                    TRY_X(y[k + 1], k + 1);
                }
            }

            segments--;
            load[k] -= d[v];
            visited[v] = 0;
        }
    }
}

int checkY(int v, int k) {
    if (v == 0) return 1; // Starting point 0 is always valid
    if (load[k] + d[v] > Q) return 0; // Check load capacity
    return !visited[v];
}

void TRY_Y(int k) {
    for (int v = y[k - 1] + 1; v <= n; v++) { // 0 < y[1] < y[2] < ... < y[K]
        if (checkY(v, k)) {
            y[k] = v;
            segments++;
            visited[v] = 1;
            load[k] += d[v];

            if (k < K) {
                TRY_Y(k + 1);
            } else {
                nbRoutes = segments;
                TRY_X(y[1], 1); // Start checking next points after y[1]
            }

            load[k] -= d[v];
            visited[v] = 0;
            segments--;
        }
    }
}

void solve() {
    for (int v = 1; v <= n; v++) visited[v] = 0; // Initialize visited array
    y[0] = 0; // Starting point
    ans = 0; // Reset the solution counter
    TRY_Y(1); // Start recursion with TRY_Y
}

int main() {
    input(); // Read input values
    solve(); // Solve the problem
    printf("%d", lower);
    return 0;
}
