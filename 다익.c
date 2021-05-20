/*
��߿�, ������ �Է� �� �ɸ��� �ҿ�ð� �� ��� ����ϴ� ���α׷�
���ͽ�Ʈ�� �˰���
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <limits.h>



#define INF 1000000000            //�������� ���� ��� �������� ó��
#define SIZE 20                  //�� �̸��� ������
#define STATION_COUNT 18         //�� ����



typedef struct Station {
	char station_name[SIZE];
	int arr_cost[STATION_COUNT];
}Station;

/*
0��� 1����û 2�¼� 3���� 4�˾� 5���� 6�־� 7��õ��û 8�һ� 9��������д��� 10��õ
11������ 12� 13���� 14���� 15������������ 16���̵� 17����
*/
Station station[STATION_COUNT] = {
   {"���",         {  0, 17,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF}},
   {"����û",      { 17,  0, 18,INF,INF,  3,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF}},
   {"�¼�",         {INF, 18,  0, 10,INF,INF,INF,INF,  5, 10,INF,INF,INF,INF,INF,INF,INF,INF}},
   {"����",         {INF,INF, 10,  0,INF,INF,INF,INF,INF,  5,INF,INF,INF,INF,INF,INF,INF,INF}},
   {"�˾�",         {INF,INF,INF,INF,  0,INF, 21,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF}},
   {"����",         {INF,  3,INF,INF,INF,  0,  9,  9, 11,INF,INF,INF,INF,INF,INF,INF,INF,INF}},
   {"�־�",         {INF,INF,INF,INF, 21,  9,  0,  5,INF,INF, 12,INF,INF,INF,INF,INF,INF,INF}},
   {"��õ��û",      {INF,INF,INF,INF,INF,  9,  5,  0,INF,INF,INF,INF, 12,INF,INF,INF,INF,INF}},
   {"�һ�",         {INF,INF,  5,INF,INF, 11,INF,INF,  0,INF,INF,INF,INF, 27,INF,INF,INF,INF}},
   {"��������д���",   {INF,INF, 10,  5,INF,INF,INF,INF,INF,  0,INF,INF,INF,INF, 18,INF,INF,INF}},
   {"��õ",         {INF,INF,INF,INF,INF,INF, 12,INF,INF,INF,  0, 15,INF,INF,INF,INF,INF,INF}},
   {"������",         {INF,INF,INF,INF,INF,INF,INF,INF,INF,INF, 15,  0,INF,INF,INF, 16, 15,INF}},
   {"�",         {INF,INF,INF,INF,INF,INF,INF, 12,INF,INF,INF,INF,  0,INF,INF,INF,INF,INF}},
   {"����",         {INF,INF,INF,INF,INF,INF,INF,INF, 27,INF,INF,INF,INF,  0, 25,INF, 12,  5}},
   {"����",         {INF,INF,INF,INF,INF,INF,INF,INF,INF, 18,INF,INF,INF, 25,  0,INF,INF,INF}},
   {"������������",   {INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF, 16,INF,INF,INF,  0,INF,INF}},
   {"���̵�",         {INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF, 15,INF, 12,INF,INF,  0,INF}},
   {"����",         {INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,  5,INF,INF,INF,  0}},
};


int weight[STATION_COUNT][STATION_COUNT];      //����ġ
int record[STATION_COUNT][STATION_COUNT];      //��� ���
int time[STATION_COUNT];                  //�ҿ�ð�
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
		// strcmp : ���ڿ��� ������ 0�� ��ȯ��
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
			printf("��� : %s -> %s\n", station[start].station_name, station[end].station_name);
			printf("�ҿ�ð� : %d\n", time[end]);
			// ��� ���
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

// �迭 �ʱ�ȭ �κ�
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

	printf("��߿� : ");
	scanf("%s", start_input);
	printf("������ : ");
	scanf("%s", end_input);

	start_station = matching(start_input);
	end_station = matching(end_input);

	set_weight(STATION_COUNT);
	set_record(STATION_COUNT);

	fast_path(start_station, STATION_COUNT);
	print_time(start_station, end_station, STATION_COUNT);
	return 0;
}