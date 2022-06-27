#include <iostream>
#include <vector>
#include <climits>
#include <set>
using namespace std;

int main(){
    int m;
    cin >> m;
    vector<bool> tmp;
    tmp.assign(10, false);
    vector<vector<bool>> edge;
    edge.assign(10, tmp);
    for(int i = 0; i < m; ++i){
        int u, v;
        cin >> u >> v;
        edge[u][v] = true;
        edge[v][u] = true;
    }
    vector<int> pos;
    pos.assign(10, 0);
    for(int i = 1; i < 9; ++i){
        int p;
        cin >> p;
        pos[p] = i;
    }
    int count = 0;
    set<vector<int>> state;
    set<vector<int>> used_state;
    state.insert(pos);
    used_state.insert(pos);
    while(state.size() > 0){
        set<vector<int>> tmp_state;
        for(auto i : state){
            vector<int> goal = {0,1,2,3,4,5,6,7,8,0};   
            if(i == goal){
                cout << count;
                return 0;
            }else{
                int n = -1;
                for(int j = 1; j < 10; ++j){
                    if(i[j] == 0){
                        n = j;
                        break;
                    }
                }
                for(int j = 1; j < 10; ++j){
                    if(edge[n][j] == true) {
                        vector<int> tmp_pos = i;
                        swap(tmp_pos[n], tmp_pos[j]);
                        if(used_state.find(tmp_pos) == used_state.end()){
                            tmp_state.insert(tmp_pos);
                            used_state.insert(tmp_pos);
                        }
                    }
                }
            }
        }
        state = tmp_state ;
        count ++ ;
    }
    cout << "-1";
}