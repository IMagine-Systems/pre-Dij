#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define INF 10000000
#define TRUE 1
#define FALSE 0
#define VERTICES 18

typedef struct Subway {
	char name[20];
	int array_cost[VERTICES];
}Subway;

Subway subway[VERTICES] = {
	{ "계양",{ 0, 17, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF } }, //계양 : 부평구청
	{ "부평구청",{ 17, 0, 18,INF, INF, INF, 3, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF } }, // 부평구청 : 온수, 부평
	{ "온수",{ INF, 18, 0, 10, 10, INF, INF, 5, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF } }, // 부평구청 : 온수 
	{ "구로",{ INF, INF, 10, 0, 5, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF } },
	{ "가산디지털단지",{ INF, INF, 10, 5, 0, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 18, INF } },
	{ "검암",{ INF, INF, INF, INF, INF, 0, INF, INF, 21, INF, INF, INF, INF, INF, INF, INF, INF, INF } },
	{ "부평",{ INF, 3, INF, INF, INF, INF, 0, 11, 9, 9, INF, INF, INF, INF, INF, INF, INF, INF } },
	{ "소사",{ INF, INF, 5, INF, INF, INF, 11, 0, INF, INF, INF, INF, INF, INF, INF, 27, INF, INF } },
	{ "주안",{ INF, INF, INF, INF, INF, 21, 9, INF, 0, 5, INF, 12, INF, INF, INF, INF, INF, INF } },
	{ "인천시청",{ INF, INF, INF, INF, INF, INF, 9, INF, 5, 0, 12, INF, INF, INF, INF, INF, INF, INF } },
	{ "운연",{ INF, INF, INF, INF, INF, INF, INF, INF, INF, 12, 0, INF, INF, INF, INF, INF, INF, INF } },
	{ "인천",{ INF, INF, INF, INF, INF, INF, INF, INF, 12, INF, INF, 0, 15, INF, INF, INF, INF, INF } },
	{ "원인재",{ INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 15, 0, 16, 15, INF, INF, INF } },
	{ "국제업무지구",{ INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 16, 0, INF, INF, INF, INF } },
	{ "오이도",{ INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 15, INF, 0, 12, INF, INF } },
	{ "초지",{ INF, INF, INF, INF, INF, INF, INF, 27, INF, INF, INF, INF, INF, INF, 12, 0, 25, 5 } },
	{ "금정",{ INF, INF, INF, INF, 18, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 25, 0, INF } },
	{ "원시",{ INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 5, 0 } },
};

int distance[VERTICES];
int found[VERTICES];
int weight[VERTICES][VERTICES];

int choose(int distance[], int found[])
{
	int i, min, minpos;
	min = INT_MAX;
	minpos = -1;
	for (i = 0; i < VERTICES; i++) {
		if (distance[i] < min && found[i] == FALSE) { 
			min = distance[i];
			minpos = i;
		}
	}
	return minpos;
}

int name_macthing(char* str) {
	int k;
	k = 0;
	for (int i = 0; i < VERTICES; i++) {
		if (strcmp(str, subway[i].name) != 0)
			k++;
		if (strcmp(str, subway[i].name) == 0)
			break;
	}
	return k;
}

void Dijkstra(int start, int end) {
	int i, u, w, c;
	int top = 0;
	int stack[VERTICES];
	int preStation[VERTICES];
	int foundRecord[VERTICES];
	for (i = 0; i < VERTICES; i++) {
		
		found[i] = FALSE;
		preStation[i] = INT_MAX;
		stack[i] = INT_MAX;
		
		foundRecord[i] = INT_MAX;
		
	}
	for (i = 0; i < VERTICES; i++) {
		for (u = 0; u < VERTICES; u++) 
			weight[i][u] = subway[i].array_cost[u];
	}
	for (i = 0; i < VERTICES; i++) {
		distance[i] = weight[start][i];
	}
	for (i = 0; i < VERTICES; i++) {
		if (weight[start][i] < INF && i != start)
			preStation[i] = start;
	}
	found[start] = TRUE;
	distance[start] = 0;
	preStation[start] = -1;
	foundRecord[0] = start;
	for (i = 0; i < VERTICES; i++) {
		u = choose(distance, found);
		found[u] = TRUE;
		if(i!=0)
		   foundRecord[i] = u;
		for (w = 0; w < VERTICES; w++) {
			if (found[w] == FALSE) {
				if (distance[u] + weight[u][w] < distance[w]) {
					preStation[w] = u; // 상위 역을 가리킨다.
					distance[w] = distance[u] + weight[u][w];
				}
			}
			
			
		}
	}
	//경로출력
	printf("경로: ");
	c = preStation[end];
	while(1) {
		stack[top++] = c;
		if (c == -1) break;
		c = preStation[c];
		
	}
	for (i = top-1; i >= 0; i--) {
		if (stack[i] == -1) 
			continue;
		printf("%s->", subway[stack[i]].name);
		
	}
	printf("%s\n", subway[end].name);
	printf("소요시간: %d\n\n\n", distance[end]);
}

int main() {
	char s[20], e[20];
	int start, end;
	
	while (1) {
		printf("0을 입력하면 종료됩니다.\n");
		printf("=========================================\n");
		printf("출발지 입력:");
		scanf_s("%s", &s, sizeof(s));
		if (strcmp(s, "0") == 0) break;
		printf("도착지 입력:");
		scanf_s("%s", &e, sizeof(e));
		if (strcmp(e, "0") == 0) break;
		printf("=========================================\n");
		start = name_macthing(s);
		end = name_macthing(e);
		if (start == 18 || end == 18) {
			printf("존재하지않는 역입니다.\n\n\n");
			continue;
		}
		Dijkstra(start, end);
	}
	return 0;
}