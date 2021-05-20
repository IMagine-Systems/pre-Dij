#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <limits.h>
#define MAX_STATION 18
#define INF 1000000000
#define SIZE 20  

typedef struct Station {
    char name[SIZE];
    int array_cost[MAX_STATION];
}Station;

Station station[MAX_STATION] = {
   {"계암",               { 0, 17, INF, INF, INF, INF,  INF,INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF}},
   {"부평구청",           { 17,  0, 18, INF, INF,   3,  INF,INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF}},
   {"온수",               {INF,  18,   0,  10, INF, INF, 10, INF, INF,  5, INF, INF, INF, INF, INF, INF, INF, INF}},
   {"구로",               {INF, INF,  10,   0,INF, INF,  5, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF}},
   {"검암",               {INF, INF, INF, INF,  0, INF, INF, 21, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF}},
   {"부평",               {INF,  3, INF, INF, INF,  0,  INF,  9,  9,   11, INF, INF, INF, INF, INF, INF, INF, INF}},
   {"가산디지털단지",     {INF, INF, 10,   5, INF, INF,  0, INF, INF, INF, INF, INF, INF, INF,  18, INF, INF, INF}},
   {"주안",               {INF, INF, INF, INF, 21,  9,  INF,  0,  5, INF,   12, INF, INF, INF, INF, INF, INF, INF}},
   {"인천시청",           {INF, INF, INF, INF, INF, 9,  INF,  5,  0, INF,  INF, INF,  12, INF, INF, INF, INF, INF}},
   {"소사",               {INF, INF,  5,  INF, INF, 11, INF, INF, INF, 0,  INF, INF, INF,  27, INF, INF, INF, INF}},
   {"인천",               {INF, INF, INF, INF, INF, INF,INF, 12, INF,INF,   0,   15, INF, INF, INF, INF, INF, INF}},
   {"원인재",             {INF, INF, INF, INF, INF, INF,INF, INF,INF,INF,  15,    0, INF, INF, INF,  16,  15, INF}},
   {"운연",               {INF, INF, INF, INF, INF, INF,INF, INF, 12,INF, INF,  INF,   0, INF, INF, INF, INF, INF}},
   {"초지",               {INF, INF, INF, INF, INF, INF,INF, INF,INF, 27, INF,  INF, INF,   0,  25, INF,  12,   5}},
   {"금정",               {INF, INF, INF, INF, INF, INF, 18, INF,INF,INF, INF,  INF, INF,  25,   0, INF, INF, INF}},
   {"국제업무지구",       {INF, INF, INF, INF, INF, INF,INF, INF,INF,INF, INF,   16, INF, INF, INF,   0, INF, INF}},
   {"오이도",             {INF, INF, INF, INF, INF, INF,INF, INF,INF,INF, INF,   15, INF,  12, INF, INF,   0, INF}},
   {"원시",               {INF, INF, INF, INF, INF, INF,INF, INF,INF,INF, INF,  INF, INF,   5, INF, INF, INF,   0}},
};


int weight[MAX_STATION][MAX_STATION];      //가중치
int record[MAX_STATION][MAX_STATION];      //경로 기록
int time[MAX_STATION];                  //소요시간
int found[MAX_STATION];

int choose(int time[], int n, int found[]) {
    int min, minpos;
    min = INT_MAX;
    minpos = -1;
    for (int i = 0; i < n; i++) {
        if (time[i] < min && !found[i]) {
            min = time[i];
            minpos = i;
        }
    }
    return minpos;
}

int matching(char* str) {
    int matching_station = 0;
    for (int i = 0; i < MAX_STATION; i++) {
        if (strcmp(str, station[i].name) != 0) {
            matching_station++;
        }
        if (strcmp(str, station[i].name) == 0) {
            break;
        }
    }
    return matching_station;
}

void init_weight(int n) {   // weight 배열 초기화
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            weight[i][j] = station[i].array_cost[j];
        }
    }
}

void init_record(int n) {   // record 배열 초기화
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            record[i][j] = INT_MIN;
        }
    }
}

void short_path(int start, int n) {
    for (int i = 0; i < n; i++) {
        if (weight[start][i] != INF) {
            record[i][0] = start;
            record[i][1] = i;
        }
        time[i] = weight[start][i];
        found[i] = 0;
    }
    found[start] = 1;
    time[start] = 0;
    for (int i = 0; i < n - 2; i++) {
        int u = choose(time, n, found);
        found[u] = 1;
        for (int w = 0; w < n; w++) {
            if (!found[w]) {
                if (time[u] + weight[u][w] < time[w]) {
                    time[w] = time[u] + weight[u][w];
                    int j;
                    for (j = 0; j < n; j++) {
                        record[w][j] = INT_MIN;
                    }
                    for (j = 0; j < n; j++) {
                        if (record[u][j] != INT_MIN) {
                            record[w][j] = record[u][j];
                        }
                        else {
                            break;
                        }
                    }
                    record[w][j] = w;
                }
            }
        }
    }
}

void print_time(int start, int end, int n) {
    for (int i = 0; i <= end; i++) {
        if (i == end && time[i]!=INF) {
            printf("소요시간 : %d\n", time[end]);
            printf("경로 : 출발(%s) -> 도착(%s)\n\n", station[start].name, station[end].name);
            // 경로 출력
            for (int j = 0; j < n; j++) {
                if (record[i][j] >= 0) {
                    printf(" -> %s", station[record[i][j]].name);

                }
                if (station[record[i][j]].name == station[end].name) {
                    return;
                }
            }
        }
    }
}

int main() {
    char input_start_station[SIZE];
    char input_end_station[SIZE];
    int start_station;
    int end_station;

    printf("출발지 입력 : ");
    scanf("%s", input_start_station);
    printf("도착지 입력 : ");
    scanf("%s", input_end_station);

    start_station = matching(input_start_station);
    end_station = matching(input_end_station);

    init_weight(MAX_STATION);
    init_record(MAX_STATION);

    short_path(start_station, MAX_STATION);
    print_time(start_station, end_station, MAX_STATION);
    return 0;
}