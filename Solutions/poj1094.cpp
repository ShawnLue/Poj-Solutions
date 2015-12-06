#include <iostream>
#include <queue>
#include <vector>
#include <stdio.h>
#include <numeric>

using namespace std;
struct V{
    int i;
    int size;
    bool operator < (const V& v) const{
        return size < v.size;
    }
};

int change(char s){
    return s - 'A';
}

void floyd(vector<vector<int> >& map){
    int n = map.size();
    for (int k = 0; k < n; k++){
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                int temp = map[i][k] * map[k][j];
                if (temp == 1)
                    map[i][j] = map[i][k] * map[k][j];
            }
        }
    }
}

bool sorted(const vector<vector<int> >& map){
    int n = map.size();
    int total = 0;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            total += map[i][j];
        }
    }
    if (total == (n * (n - 1) / 2))
        return true;
    else
        return false;
}

bool inconsistence(const vector<vector<int> >& map){
    int n = map.size();
    for (int i = 0; i < n; i++){
        if (map[i][i] == 1){
            return true;
        }
    }
    return false;
}

int main(){
    int n, m;
    while(~scanf("%d %d", &n, &m) && !((n == 0) && (m == 0))){
        int item = 0, item_num;
        priority_queue<V> q;
        bool cal_on = true;
        vector<vector<int> >map(n, vector<int>(n));
        for (int i = 0; i < m; i++){
            char a, b, op;
            cin >> a >> op >> b;
            if (!cal_on)
                continue;
            map[change(a)][change(b)] = 1;
            floyd(map);
            if (sorted(map)){
                cal_on = false;
                item_num = i;
                item = 1;
                V tmp;
                for (int i = 0; i < map.size(); i++){
                    tmp.i = i;
                    tmp.size = accumulate(map[i].begin(), map[i].end(), 0);
                    q.push(tmp);
                }
            }
            if (inconsistence(map)){
                cal_on = false;
                item_num = i;
                item = 2;
            }
        }
        if (item == 0)
            printf("Sorted sequence cannot be determined.\n");
        if (item == 1){
            printf("Sorted sequence determined after %d relations: ", item_num + 1);
            while(!q.empty()){
                printf("%c", 'A' + q.top().i);
                q.pop();
            }
            printf(".\n");
        }
        if (item == 2){
            printf("Inconsistency found after %d relations.\n", item_num + 1);
        }
    }
    return 0;
}