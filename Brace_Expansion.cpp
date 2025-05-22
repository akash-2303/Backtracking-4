// Brace Expansion
// Time Complexity: O(n * m * log(m)), where n is the number of groups and m is the maximum size of a group.
// Space Complexity: O(n * m), for the groups and the result
// Does this code run on leetcode? Yes

// Approach:
// 1. Parse the input string to create groups of characters.
// 2. Sort each group to ensure lexicographical order.
// 3. Use backtracking to generate all combinations of characters from the groups.
// 4. Store the results in a vector and return it.

class Solution {
    vector<string> result;
public:
    vector<string> expand(string s) {
        vector<vector<char>> groups;
        for(int i = 0; i < s.size(); i++){
            if(s[i] == '{'){
                ++i;
                vector<char> group;
                while(s[i] != '}'){
                    if(s[i] != ','){
                        group.push_back(s[i]);
                    }
                    i++;
                }
                sort(group.begin(), group.end());
                groups.push_back(group);
            }else{
                groups.push_back({s[i]});
            }
        }
        // sort(groups.begin(), groups.end());
        string path;
        backtrack(groups, 0, path);
        return result;
    }
private: 
    void backtrack(vector<vector<char>>& groups, int index, string& path){
        // base case
        if(index == groups.size()){
            result.push_back(path);
            return;
        }
        for(char c : groups[index]){
            path.push_back(c);
            backtrack(groups, index + 1, path);
            path.pop_back();
        }
    }
};