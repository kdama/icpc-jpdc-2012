#include <iostream>
#include <vector>

typedef std::vector<std::vector<int>> Matrix;

// INF (Infinity) must be larger than MAX_DIST and MAX_COST.
// MAX_DIST ==      200 *  99 == 19800.
// MAX_COST == MAX_DIST * 100 == 1980000.
const int INF = 10000000;

// Floyd-Warshall algorithm.
void floyd(int n, Matrix& matrix) {
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                matrix[i][j] = matrix[j][i] = std::min(matrix[i][j], matrix[i][k] + matrix[k][j]);
            }
        }
    }
}

// Calculate cost by given fare table of a railway company.
int calc_cost(int dist, std::vector<int> q, std::vector<int> r) {
    if (dist == INF) return INF;
    
    int cost = 0;
    for (int i = 0; i < q.size(); i++) {
    	if (i == 0) {
    		if (dist <= q[i]) {
    			cost += dist * r[i];
    			dist -= dist;
    			break;
    		} else {
    			cost += q[i] * r[i];
    			dist -= q[i];
    		}
    	} else {
    		if (dist <= q[i] - q[i - 1]) {
    			cost += dist * r[i];
    			dist -= dist;
    			break;
    		} else {
    			cost += (q[i] - q[i - 1]) * r[i];
    			dist -= (q[i] - q[i - 1]);
    		}
    	}
    }
    cost += dist * r.back();
    
    return cost;
}

int main(int argc, char* argv[]) {
    int n, m, c, s, g;
    while ((std::cin >> n >> m >> c >> s >> g) && (n | m | c | s | g))	{
        s--, g--;
        
        std::vector<Matrix> min_dist(c, Matrix(n, std::vector<int>(n, INF)));
        Matrix min_cost(n, std::vector<int>(n, INF));
        
        for (int ni = 0; ni < n; ni++) {
            for (int ci = 0; ci < c; ci++) {
                min_dist[ci][ni][ni] = 0;
            }
            min_cost[ni][ni] = 0;
        }
        
        for (int mi = 0; mi < m; mi++) {
            int xi, yi, di, ci;
            std::cin >> xi >> yi >> di >> ci;
            xi--, yi--, ci--;
            min_dist[ci][xi][yi] = min_dist[ci][yi][xi] = std::min(min_dist[ci][xi][yi], di);
        }
        
        std::vector<int> p;
        for (int ci = 0; ci < c; ci++) {
            int pi;
            std::cin >> pi;
            p.push_back(pi);
        }
        
        for (int ci = 0; ci < c; ci++) {
            std::vector<int> q;
            std::vector<int> r;
            
            for (int pi = 0; pi < p[ci] - 1; pi++) {
                int qi;
                std::cin >> qi;
                q.push_back(qi);
            }
            
            for (int pi = 0; pi < p[ci]; pi++) {
                int ri;
                std::cin >> ri;
                r.push_back(ri);
            }
            
            floyd(n, min_dist[ci]);

            for (int xi = 0; xi < n; xi++) {
                for (int yi = 0; yi < n; yi++) {
                    min_cost[xi][yi] = min_cost[yi][xi] = std::min(min_cost[xi][yi], calc_cost(min_dist[ci][xi][yi], q, r));
                }
            }
        }
        
        floyd(n, min_cost);
        
        std::cout << (min_cost[s][g] < INF ? min_cost[s][g] : -1) << std::endl;
    }
    return 0;
}

/*
VERSION 01 13:50--10:01 http://ideone.com/a2KCNd
*/
