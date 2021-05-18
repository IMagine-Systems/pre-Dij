// 201702003 손민석 
// 지하철 출발역 부터 도착역 까지 소요시간 적은 경로 보여주는 프로그램.
#include<stdio.h>
#include<limits.h>
#include<string.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 18
#define INF 1000000000 // 무한 
#define SIZE 30

typedef struct Metro{
	char name[SIZE];
	int array_cost[MAX_VERTICES];
}Metro;

Metro metro[MAX_VERTICES] = {
	{"구로",{0,10,5,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF}}, // 0 구로 : 온수, 가산디지털
	{"온수",{10,0,10,INF,5,INF,INF,18,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF}}, // 1 온수 : 구로, 가산디지털, 소사, 부평구청
	{"가산디지털단지",{5,10,0,18,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF}}, // 가산디지털 2
	{"금정",{INF,INF,18,0,INF,25,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF} }, // 금정 3
	{"소사",	{INF,5,INF,INF,0,27,INF,INF,INF,11,INF,INF,INF,INF,INF,INF,INF,INF}}, // 소사 4
	{"초지",{INF,INF,INF,25,27,0,5,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,12}}, // 초지 5
	{"원시",{INF,INF,INF,INF,INF,5,0,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF}}, // 원시 6
	{"부평구청",	{INF,18,INF,INF,INF,INF,INF,0,17,3,INF,INF,INF,INF,INF,INF,INF,INF}}, // 부평구청 7
	{"계양",	{INF,INF,INF,INF,INF,INF,INF,17,0,INF,INF,INF,INF,INF,INF,INF,INF,INF}}, // 계양 8
	{"부평",{INF,INF,INF,INF,11,INF,INF,3,INF,0,INF,9,9,INF,INF,INF,INF,INF}}, // 부평 9
	{"검안",{INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,0,21,INF,INF,INF,INF,INF,INF}}, // 검안 10
	{"주안",{INF,INF,INF,INF,INF,INF,INF,INF,9,INF,21,0,5,INF,12,INF,INF,INF}}, // 주안 11
	{"인천시장",{INF,INF,INF,INF,INF,INF,INF,INF,INF,9,INF,5,0,12,INF,INF,INF,INF} }, // 인천시장 12
	{"운연",{INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,12,0,INF,INF,INF,INF}}, // 운연 13
	{"인천",{INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,12,INF,INF,0,15,INF,INF}}, // 인천 14
	{"원인재",{INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,15,0,16,15}}, // 원인재 15rnf
	{"국제업무지구",{INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,16,0,INF}}, // 국제업무지구 16
	{"오이도",{INF,INF,INF,INF,INF,12,INF,INF,INF,INF,INF,INF,INF,INF,INF,15,INF,0}} 
};  // 오이도 17

int weight[MAX_VERTICES][MAX_VERTICES];
int record[MAX_VERTICES][MAX_VERTICES];
int distance[MAX_VERTICES];
int found[MAX_VERTICES];

int choose(int distance[], int n, int found[]) {
	int i, min, minpos;
	min = INT_MAX;
	minpos = -1;

	for (int i = 0; i < n; i++) {
		if (distance[i] < min && !found[i]) {
			min = distance[i];
			minpos = i;
		}
	}
	return minpos;
}

void weight_init(int n) {
	int i, j;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			weight[i][j] = metro[i].array_cost[j];
		}
	}
}

void record_init(int n) {
	int i, j;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			record[i][j] = INT_MIN;
		}
	}
}

void shortest_path(int start, int n) { // 시작점 노드부터 마지막 노드까지 최단경로 구하기
	int i, j, u, w;
	for (i = 0; i < n; i++) {
		if (weight[start][i] != INF) {
			record[i][0] = start;
			record[i][1] = i;
		}
		distance[i] = weight[start][i];
		found[i] = FALSE;
	}
	found[start] = TRUE;
	distance[start] = 0;
	
	for (i = 0; i < n - 2; i++) {
		u = choose(distance, n, found);
		found[u] = TRUE;
		for (w = 0; w < n; w++) {
			if (!found[w]) {
				if (distance[u] + weight[u][w] < distance[w]) {
					distance[w] = distance[u] + weight[u][w];
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

void print_distance(int start, int end, int n) {
	int i, j;
	for (i = 0; i <= end; i++) {
		if (i == end && distance[i] != INF) {
			printf("출발 : %s역 ------> 도착 : %s역\n소요 시간 : %d분\n ", metro[start].name, metro[end].name, distance[end]);
			printf("---------------------------------경로-------------------------------------------------\n");
			for (j = 0; j < n; j++) {
				if (record[i][j] >= 0) {
					printf("%s역", metro[record[i][j]].name);
				}
				if (metro[record[i][j]].name == metro[end].name)
					return;
				printf("-> ");
			}
		}
	
	}
}

int name_matching(char *str) {
	int k = 0;
	
	for (int i = 0; i < MAX_VERTICES; i++) {
		if (strcmp(str, metro[i].name) != 0) {
			k++;
		}
		if (strcmp(str, metro[i].name) == 0) {
			break;
		}
	}
	return k;
}

int main() {
	char station1[SIZE], station2[SIZE];
	int k;
	int e;

	printf("출발지 : ");
	scanf("%s", station1);
	printf("도착지 : ");
	scanf("%s", station2);

	k = name_matching(station1);
	e = name_matching(station2);

	weight_init(MAX_VERTICES);
	record_init(MAX_VERTICES);
	shortest_path(k, MAX_VERTICES);
	print_distance(k, e, MAX_VERTICES);

	return 0;
}