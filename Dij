#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <limits.h>
#include <string.h>


#define MAX_VERTICES 18
#define INF 10000000
#define SIZE 20


typedef struct Metro {
    char name[SIZE];
    int array_cost[MAX_VERTICES];
}Metro;

Metro metro[MAX_VERTICES] = {
   {"계양", {0, 17, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF}}, 
   {"부평구청",{17, 0, 18,INF, INF, INF, 3, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF}}, 
   {"온수",{INF, 18, 0, 10, 10, INF, INF, 5, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF}}, 
   {"구로",{INF, INF, 10, 0, 5, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 18, INF, INF}}, 
   {"가산디지털단지",{INF, INF, 10, 5, 0, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 18, INF}}, 
   {"검암",{INF, INF, INF, INF, INF, 0, INF, INF, 21, INF, INF, INF, INF, INF, INF, INF, INF, INF}}, 
   {"부평",{INF, 3, INF, INF, INF, INF, 0, 11, 9, INF, INF, INF, INF, INF, INF, INF, INF, 9}}, 
   {"소사",{ INF, INF, 5, INF, INF, INF, 11, 0, INF, INF, INF, INF, INF, INF, 27, INF, INF, INF }}, 
   {"주안",{ INF, INF, INF, INF, INF, 21, 9, INF, 0, INF, 12, INF, INF, INF, INF, INF, INF, 5 }}, 
   {"운연",{ INF, INF, INF, INF, INF, INF, INF, INF, INF, 0, INF, INF, INF, INF, INF, INF, INF, 12 }},
   {"인천",{ INF, INF, INF, INF, INF, INF, INF, INF, 12, INF, 0, 15, INF, INF, INF, INF, INF, INF }},
   {"원인재",{INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 15, 0, 16, 15, INF, INF, INF, INF}},
   {"국제업무지구",{ INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 16, 0, INF, INF, INF, INF, INF }},
   {"오이도",{INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 15, INF, 0, 12, INF, INF, INF}},
   {"초지",{ INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 12, 0, 25, 5, INF }},
   {"금정",{ INF, INF, INF, INF, 18, INF, INF, INF, INF, INF, INF, INF, INF, INF, 25, 0, INF, INF }},
   {"원시",{ INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 5, INF, 0, INF }},
   {"인천시장",{ INF, INF, INF, INF, INF, INF, 9, INF, 5, INF, INF, INF, INF, INF, INF, INF, INF, 0 }}
};

int weight[MAX_VERTICES][MAX_VERTICES];
int record[MAX_VERTICES][MAX_VERTICES];
int distance[MAX_VERTICES];
int found[MAX_VERTICES];

int choose(int distance[], int n, int found[]) {
    int i, min, minpos;
    min = INT_MAX;
    minpos = -1;
    for (i = 0; i < n; i++) {
        if (distance[i] < min && !found[i]) {
            min = distance[i];
            minpos = i;
        }
    }
    return minpos;
}
void init(int n) {
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            weight[i][j] = metro[i].array_cost[j];
            record[i][j] = INT_MIN;
        }
    }
}
void shortest_path(int start, int n) {
    int i, j, u, w;
    for (i = 0; i < n; i++) {
        if (weight[start][i] != INF) {
            record[i][0] = start;
            record[i][1] = i;
        }
        distance[i] = weight[start][i];
        found[i] = 0;
    }
    found[start] = 1;
    distance[start] = 0;
    for (i = 0; i < n - 2; i++) {
        u = choose(distance, n, found);
        found[u] = 1;
        for (w = 0; w < n; w++) {
            if (!found[w])
                if (distance[u] + weight[u][w] < distance[w]) {
                    distance[w] = distance[u] + weight[u][w];
                    for (j = 0; j < n; j++) {
                        record[w][j] = INT_MIN;
                    }
                    for (j = 0; j < n; j++) {
                        if (record[u][j] != INT_MIN)
                            record[w][j] = record[u][j];
                        else
                            break;
                    }
                    record[w][j] = w;
                }
        }
    }
}
void print_distance(int start, int end, int n) {
    int i, j;
    for (i = 0; i <= end; i++) {
        if (distance[i] != INF && i == end) {
            printf("===================================\n");
            printf("소요시간 : %d\n", distance[i]);
            printf("경로 %s 에서 %s 까지 : \n", metro[start].name, metro[end].name);

            for (j = 0; j < n; j++) {
                if (record[i][j] >= 0)
                    printf("--> %s", metro[record[i][j]].name);
                if (metro[record[i][j]].name == metro[end].name) {
                    return;
                }
            }
        }
    }
}
int name_macthing(char* str) {
    int k;
    k = 0;
    for (int i = 0; i < MAX_VERTICES; i++) {
        if (strcmp(str, metro[i].name) != 0)
            k++;
        if (strcmp(str, metro[i].name) == 0)
            break;
    }
    return k;
}
void main() {
    char x[SIZE];
    char y[SIZE];
    int start;
    int end;

    printf("출발 역을 입력하세요 :"); scanf("%s", x);
    printf("도착 역을 입력하세요 :"); scanf("%s", y);

    start = name_macthing(x);
    end = name_macthing(y);

    init(MAX_VERTICES);
    shortest_path(start, MAX_VERTICES);
    print_distance(start, end, MAX_VERTICES);

    return;
}
