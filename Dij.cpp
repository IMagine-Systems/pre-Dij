#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <limits.h>
#include <string.h>


#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 18
#define SIZE 20
#define INF 1000000

typedef struct Way {
	char name[SIZE];
	int array_cost[MAX_VERTICES];
}Way;
Way way[MAX_VERTICES] = {
	 { "���",        {0, 17, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF } }, 
   { "����û",      {17, 0, 18,INF, INF, INF, 3, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF } }, 
   { "�¼�",          {INF, 18, 0, 10, 10, INF, INF, 5, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF } }, 
   { "����",          {INF, INF, 10, 0, 5, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF } },
   { "��������д���",{INF, INF, 10, 5, 0, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 18, INF } },
   { "�˾�",          {INF, INF, INF, INF, INF, 0, INF, INF, 21, INF, INF, INF, INF, INF, INF, INF, INF, INF } },
   { "����",          {INF, 3, INF, INF, INF, INF, 0, 11, 9, 9, INF, INF, INF, INF, INF, INF, INF, INF } },
   { "�һ�",          {INF, INF, 5, INF, INF, INF, 11, 0, INF, INF, INF, INF, INF, INF, INF, 27, INF, INF } },
   { "�־�",          {INF, INF, INF, INF, INF, 21, 9, INF, 0, 5, INF, 12, INF, INF, INF, INF, INF, INF } },
   { "��õ��û",      {INF, INF, INF, INF, INF, INF, 9, INF, 5, 0, 12, INF, INF, INF, INF, INF, INF, INF } },
   { "�",          {INF, INF, INF, INF, INF, INF, INF, INF, INF, 12, 0, INF, INF, INF, INF, INF, INF, INF } },
   { "��õ",          {INF, INF, INF, INF, INF, INF, INF, INF, 12, INF, INF, 0, 15, INF, INF, INF, INF, INF } },
   { "������",        {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 15, 0, 16, 15, INF, INF, INF } },
   { "������������",  {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 16, 0, INF, INF, INF, INF } },
   { "���̵�",        {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 15, INF, 0, 12, INF, INF } },
   { "����",          {INF, INF, INF, INF, INF, INF, INF, 27, INF, INF, INF, INF, INF, INF, 12, 0, 25, 5 } },
   { "����",          {INF, INF, INF, INF, 18, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 25, 0, INF } },
   { "����",          {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 5, 0 } },

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
void init_1(int n) {
	int i, j;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			weight[i][j] = way[i].array_cost[j];
		}
	}
}
void init_2(int n) {
	int i, j;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
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
			printf("���� = %s ----> ���� = %s\n �ҿ�ð� = %d��\n  ", way[start].name, way[end].name, distance[end]);
			printf("�ڽ��� : %s -> %s \n", way[start].name, way[end].name);

			for (j = 0; j < n; j++) {
				if (record[i][j] >= 0) {
					printf("%s ->", way[record[i][j]].name);
				}
				if (way[record[i][j]].name == way[end].name)
					return;
				
			}
		}
	}
}

int name_matching(char* str) {
	int k = 0;

	for (int i = 0; i < MAX_VERTICES; i++) {
		if (strcmp(str, way[i].name) != 0) {
			k++;
		}
		if (strcmp(str, way[i].name) == 0) {
			break;
		}
	}
	return k;
}
int main() {
	char x[SIZE], y[SIZE];
	int k;
	int e;

	printf("��� ���� �Է��Ͻÿ� : ");
	scanf("%s", x);
	printf("���� ���� �Է��Ͻÿ� : ");
	scanf("%s", y);

	k = name_matching(x);
	e = name_matching(y);

	init_1(MAX_VERTICES);
	init_2(MAX_VERTICES);
	shortest_path(k, MAX_VERTICES);
	print_distance(k,e, MAX_VERTICES);
	
	return 0;
}