#define _CRT_SECURE_NO_WARNINGS 
#include <cstdio>
#include <memory>
#include <queue>
#include <utility>
#include <cmath>

// SegmentTree1D 구현하세요. 직접 스크래치로 전부 구현하셔도 무관합니다.
// 원소 합을 return 해주는 sum 함수와 원소 수정에 대한 modify 함수 구현

long long* tree;
long long* arr;


    // 초기화
long long initialize(int s, int e, int node) {
        int middle;
        if (s == e) {
            return tree[node] = arr[s];
           // return tree[node];
        }
        else {
            middle = (s + e) / 2;
            long long a = initialize(s, middle, node * 2);
            long long b = initialize(middle + 1, e, node * 2+1);
            tree[node] = a + b;

        }
        return tree[node];


        /*  int sum = 0;
          for (int i = 0;i < n;i++) {
              sum += array[i];
              cum_array[i] = sum;
          }
          */
    }

long long sum(int x, int y, int s, int e, int node) {
        /*
            x에서 y 까지의 합
        */
        int middle = (s + e) / 2;
        if (e < x || y < s) {
            return 0;
        }
        if (e <= y && x <= s) {
            return tree[node];
        }
        else {
            return sum(x, y, s, middle, node * 2) + sum(x, y, middle + 1, e, node * 2);
        }
    }

void modify(int idx, int num, int s, int e, int node) {
        /*
            idx에 위치한 원소를 num으로 교체
        */
        if (idx<s || idx>e) {
            return;
        }
        tree[node] = tree[node] + num;
        if (s == e)    return;
        int middle = (s + e) / 2;
        modify(idx, num, s, middle, node * 2);
        modify(idx, num, middle + 1, e, node * 2);
    }



int main() {

    int n, m;

    FILE* in = fopen("input_assignment1.txt", "r");

    fscanf(in, "%d", &n);

    int treesize = 1 << (n + 1);
    tree = new long long[treesize];
    arr = new long long[treesize];

   

    int temp;
    for (int i = 0; i < n; i++) {
        fscanf(in, "%d", &temp);
        printf("%d ", temp);
        arr[i] = temp;
    }
    printf("\n");

    initialize(0, n-1, 1);

    fscanf(in, "%d", &m);
    for (int i = 0; i < m; i++) {

        fscanf(in, "%d\n", &temp);

        if (temp == 0) {
            int st, ed;
            fscanf(in, "%d %d", &st, &ed);
            printf("sum (%d,%d): %d\n", st, ed, sum(st, ed, 0, n-1, 1));

        }
        
        else {
            int idx, num;
            fscanf(in, "%d %d", &idx, &num);
            printf("change %dth elem with %d\n", idx + 1, num);
            num = num - arr[idx];
            arr[idx - 1] = num;
            modify(idx, num,0, n-1, 1);
        }
       
    }

    return 0;

}