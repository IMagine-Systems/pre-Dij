// 201702003 �չμ� 
// ����ö ��߿� ���� ������ ���� �ҿ�ð� ���� ��� �����ִ� ���α׷�.
#include<stdio.h>
#include<limits.h>
#include<string.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 18
#define INF 1000000000 // ���� 
#define SIZE 30

typedef struct Metro{
	char name[SIZE];
	int array_cost[MAX_VERTICES];
}Metro;

Metro metro[MAX_VERTICES] = {
	{"����",{0,10,5,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF}}, // 0 ���� : �¼�, ���������
	{"�¼�",{10,0,10,INF,5,INF,INF,18,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF}}, // 1 �¼� : ����, ���������, �һ�, ����û
	{"��������д���",{5,10,0,18,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF}}, // ��������� 2
	{"����",{INF,INF,18,0,INF,25,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF} }, // ���� 3
	{"�һ�",	{INF,5,INF,INF,0,27,INF,INF,INF,11,INF,INF,INF,INF,INF,INF,INF,INF}}, // �һ� 4
	{"����",{INF,INF,INF,25,27,0,5,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,12}}, // ���� 5
	{"����",{INF,INF,INF,INF,INF,5,0,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF}}, // ���� 6
	{"����û",	{INF,18,INF,INF,INF,INF,INF,0,17,3,INF,INF,INF,INF,INF,INF,INF,INF}}, // ����û 7
	{"���",	{INF,INF,INF,INF,INF,INF,INF,17,0,INF,INF,INF,INF,INF,INF,INF,INF,INF}}, // ��� 8
	{"����",{INF,INF,INF,INF,11,INF,INF,3,INF,0,INF,9,9,INF,INF,INF,INF,INF}}, // ���� 9
	{"�˾�",{INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,0,21,INF,INF,INF,INF,INF,INF}}, // �˾� 10
	{"�־�",{INF,INF,INF,INF,INF,INF,INF,INF,9,INF,21,0,5,INF,12,INF,INF,INF}}, // �־� 11
	{"��õ����",{INF,INF,INF,INF,INF,INF,INF,INF,INF,9,INF,5,0,12,INF,INF,INF,INF} }, // ��õ���� 12
	{"�",{INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,12,0,INF,INF,INF,INF}}, // � 13
	{"��õ",{INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,12,INF,INF,0,15,INF,INF}}, // ��õ 14
	{"������",{INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,15,0,16,15}}, // ������ 15rnf
	{"������������",{INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,16,0,INF}}, // ������������ 16
	{"���̵�",{INF,INF,INF,INF,INF,12,INF,INF,INF,INF,INF,INF,INF,INF,INF,15,INF,0}} 
};  // ���̵� 17

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

void shortest_path(int start, int n) { // ������ ������ ������ ������ �ִܰ�� ���ϱ�
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
			printf("��� : %s�� ------> ���� : %s��\n�ҿ� �ð� : %d��\n ", metro[start].name, metro[end].name, distance[end]);
			printf("---------------------------------���-------------------------------------------------\n");
			for (j = 0; j < n; j++) {
				if (record[i][j] >= 0) {
					printf("%s��", metro[record[i][j]].name);
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

	printf("����� : ");
	scanf("%s", station1);
	printf("������ : ");
	scanf("%s", station2);

	k = name_matching(station1);
	e = name_matching(station2);

	weight_init(MAX_VERTICES);
	record_init(MAX_VERTICES);
	shortest_path(k, MAX_VERTICES);
	print_distance(k, e, MAX_VERTICES);

	return 0;
}