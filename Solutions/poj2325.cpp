#include <iostream>
#include <stdio.h>
#include <queue>
#include <functional>

using namespace std;

int divide(int& t){
    int i = 9;
    for (; i > 0; i--){
        if (t % i == 0){
            t /= i;
            break;
        }
    }
    if ((i == 1) && (t != 1))
        return -1;
    return i;
}

void per(int t){
    if (t == 0) {
        printf("%d%d\n", 1, 0);
        return;
    }
    if (t == 1){
        printf("%d%d\n", 1, 1);
        return;
    }
    priority_queue<int, vector<int>, greater<int> > q;
    while (true){
        int num = divide(t);
        if (num == -1){
            printf("There is no such number.\n");
            return;
        }
        if (num == 1 && q.size() == 1){
            q.push(num);
            break;
        }
        if (num == 1) break;
        q.push(num);
    }
    while(!q.empty()){
        printf("%d", q.top());
        q.pop();
    }
    printf("\n");
}

int main(){
    int n;
    while (~scanf("%d", &n) && (n != -1)){
        per(n);
    }
    return 0;
}