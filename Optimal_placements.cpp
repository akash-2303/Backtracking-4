// Time Complexity: O(w * h * n * (w + h)), where w is width, h is height, and n is number of buildings
// Space Complexity: O(w * h), for the grid and distance array
// Does this run on playground? Yes

// Approach: 
// 1. Use backtracking to place buildings in the grid.
// 2. For each placement, perform BFS to calculate the maximum distance from any building to the farthest empty cell.
// 3. Keep track of the minimum of these maximum distances.

#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

class Solution {
    int w, h, n;
    int minDist = INT_MAX;

public:
    int findMinDistance(int width, int height, int buildings) {
        w = width;
        h = height;
        n = buildings;
        vector<vector<int>> grid(h, vector<int>(w, -1));  // -1 = empty
        backtrack(grid, 0, n);
        return minDist;
    }

private:
    void backtrack(vector<vector<int>>& grid, int start, int remaining) {
        // TODO: Try placing buildings and recurse
        if(remaining == 0){
            int dist = bfs(grid);
            minDist = min(minDist, dist);
            return;
        }
        int rows = grid.size();
        int cols = grid[0].size();
        
        for(int i = start; i < rows * cols; i++){
            int r = i / cols;
            int c = i % cols;
            
            if(grid[r][c] == -1){
                grid[r][c] = 0;
                backtrack(grid, i + 1, remaining - 1);
                grid[r][c] = -1;
            }
        }
    }

    int bfs(vector<vector<int>>& grid) {
        // TODO: Perform BFS from all buildings and return the max distance
        int rows = grid.size();
        int cols = grid[0].size();
        queue<pair<int, int>> q;
        vector<vector<int>> dist(rows, vector<int>(cols, -1));
        
        for(int r = 0; r < rows; r++){
            for(int c = 0; c < cols; c++){
                if(grid[r][c] == 0){
                    q.push({r, c});
                    dist[r][c] = 0;
                }
            }
        }
        vector<pair<int, int>> dirs = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};
        int maxDist = 0;
        
        while(!q.empty()) {
            auto [r, c] = q.front();
            q.pop();
            
            for(auto& [dr, dc] : dirs){
                int nr = r + dr;
                int nc = c + dc;
                if(nr >= 0 && nr < rows && nc >= 0 && nc < cols && dist[nr][nc] == -1){
                    dist[nr][nc] = dist[r][c] + 1;
                    maxDist = max(maxDist, dist[nr][nc]);
                    q.push({nr, nc});
                }
            }
        }
        return maxDist;
    }
};

int main() {
    Solution sol;
    int width = 4, height = 4, buildings = 3;
    int result = sol.findMinDistance(width, height, buildings);
    cout << "Minimum max distance: " << result << endl;
    return 0;
}
