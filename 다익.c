/*
출발역, 도착역 입력 시 걸리는 소요시간 및 경로 출력하는 프로그램
다익스트라 알고리즘
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <limits.h>



#define INF 1000000000            //인접하지 않은 경우 무한으로 처리
#define SIZE 20                  //역 이름의 사이즈
#define STATION_COUNT 18         //역 개수



typedef struct Station {
	char station_name[SIZE];
	int arr_cost[STATION_COUNT];
}Station;

/*
0계양 1부평구청 2온수 3구로 4검암 5부평 6주안 7인천시청 8소사 9가산디지털단지 10인천
11원인재 12운연 13초지 14금정 15국제업무지구 16오이도 17원시
*/
Station station[STATION_COUNT] = {
   {"계양",         {  0, 17,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF}},
   {"부평구청",      { 17,  0, 18,INF,INF,  3,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF}},
   {"온수",         {INF, 18,  0, 10,INF,INF,INF,INF,  5, 10,INF,INF,INF,INF,INF,INF,INF,INF}},
   {"구로",         {INF,INF, 10,  0,INF,INF,INF,INF,INF,  5,INF,INF,INF,INF,INF,INF,INF,INF}},
   {"검암",         {INF,INF,INF,INF,  0,INF, 21,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF}},
   {"부평",         {INF,  3,INF,INF,INF,  0,  9,  9, 11,INF,INF,INF,INF,INF,INF,INF,INF,INF}},
   {"주안",         {INF,INF,INF,INF, 21,  9,  0,  5,INF,INF, 12,INF,INF,INF,INF,INF,INF,INF}},
   {"인천시청",      {INF,INF,INF,INF,INF,  9,  5,  0,INF,INF,INF,INF, 12,INF,INF,INF,INF,INF}},
   {"소사",         {INF,INF,  5,INF,INF, 11,INF,INF,  0,INF,INF,INF,INF, 27,INF,INF,INF,INF}},
   {"가산디지털단지",   {INF,INF, 10,  5,INF,INF,INF,INF,INF,  0,INF,INF,INF,INF, 18,INF,INF,INF}},
   {"인천",         {INF,INF,INF,INF,INF,INF, 12,INF,INF,INF,  0, 15,INF,INF,INF,INF,INF,INF}},
   {"원인재",         {INF,INF,INF,INF,INF,INF,INF,INF,INF,INF, 15,  0,INF,INF,INF, 16, 15,INF}},
   {"운연",         {INF,INF,INF,INF,INF,INF,INF, 12,INF,INF,INF,INF,  0,INF,INF,INF,INF,INF}},
   {"초지",         {INF,INF,INF,INF,INF,INF,INF,INF, 27,INF,INF,INF,INF,  0, 25,INF, 12,  5}},
   {"금정",         {INF,INF,INF,INF,INF,INF,INF,INF,INF, 18,INF,INF,INF, 25,  0,INF,INF,INF}},
   {"국제업무지구",   {INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF, 16,INF,INF,INF,  0,INF,INF}},
   {"오이도",         {INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF, 15,INF, 12,INF,INF,  0,INF}},
   {"원시",         {INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,  5,INF,INF,INF,  0}},
};


int weight[STATION_COUNT][STATION_COUNT];      //가중치
int record[STATION_COUNT][STATION_COUNT];      //경로 기록
int time[STATION_COUNT];                  //소요시간
int found[STATION_COUNT];

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
	for (int i = 0; i < STATION_COUNT; i++) {
		// strcmp : 문자열이 같으면 0을 반환함
		if (strcmp(str, station[i].station_name) != 0) {
			matching_station++;
		}
		else if (strcmp(str, station[i].station_name) == 0) {
			break;
		}
	}
	return matching_station;
}

void fast_path(int start, int n) {
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
		if (time[i] != INF && i == end) {
			printf("경로 : %s -> %s\n", station[start].station_name, station[end].station_name);
			printf("소요시간 : %d\n", time[end]);
			// 경로 출력
			for (int j = 0; j < n; j++) {
				if (record[i][j] >= 0) {
					printf(" -> %s", station[record[i][j]].station_name);

				}
				if (station[record[i][j]].station_name == station[end].station_name) {
					return;
				}
			}
		}
	}
}

// 배열 초기화 부분
void set_weight(int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			weight[i][j] = station[i].arr_cost[j];
		}
	}
}

void set_record(int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			record[i][j] = INT_MIN;
		}
	}
}

int main() {
	char start_input[SIZE];
	char end_input[SIZE];
	int start_station;
	int end_station;

	printf("출발역 : ");
	scanf("%s", start_input);
	printf("도착역 : ");
	scanf("%s", end_input);

	start_station = matching(start_input);
	end_station = matching(end_input);

	set_weight(STATION_COUNT);
	set_record(STATION_COUNT);

	fast_path(start_station, STATION_COUNT);
	print_time(start_station, end_station, STATION_COUNT);
	return 0;
}