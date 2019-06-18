#pragma once
#include"graph.h"
#include<ctime>
#include<Windows.h>
class process_scheduling
{
public:
	process_scheduling();
	void run();
	bool creat_process();
	bool process();
private:
	bool pid_array[100];
	graph_link graph;

};

process_scheduling::process_scheduling()
{
	memset(pid_array, true, 100);
}

bool process_scheduling::creat_process() {
	ready_queue_node* temp;
	for (int i = 0; i < 100; i++) {
		if (pid_array[i] == true) {
			//srand((unsigned)time(NULL));
			temp = new ready_queue_node;
			temp->block.pid = i;
			pid_array[i] = false;
			temp->block.status = "ready";
			temp->block.priority = rand() % 50;
			temp->block.life = rand() % 5 + 1;
			temp->next = graph.graph[temp->block.priority]->next;
			graph.graph[temp->block.priority]->next = temp;
			cout << graph.graph[temp->block.priority]->next->block.priority << endl;
			return true;
		}
	}
	return false;
}

void process_scheduling::run() {
	while (1) {
		bool flag = true;
			char c = _getch();
			switch (c)
			{
			case 0x6:
				creat_process();
				break;
			case 0x12:
				while (flag) {
					printf("if want to creat a new process just press any key to pause\n");
					if (_kbhit())break;
					flag = process();
				}
				break;
			case 0x11:
				return;
			default:
				break;
			}
	}
}

bool process_scheduling::process() {
	ready_queue_node* temp;
	temp = new ready_queue_node;
	*temp = graph.get_top();
	if (temp->block.pid == -1) {
		printf("There is no process\n");
		return false;
	}
	temp->block.status = "run";
	printf("Process pid: %d, status: %s, priority: %d, life: %d \n", temp->block.pid, temp->block.status.c_str(), temp->block.priority, temp->block.life);
	Sleep(1000);
	graph.print_same_priority(temp);
	graph.print_low_priority(temp->block.priority);
	temp->block.life -= 1;
	if (temp->block.life > 0)
	{
		temp->block.priority /= 2;
		temp->block.status = "ready";
		graph.inseart(temp);
		return true;
	}
	pid_array[temp->block.pid] = true;
	delete temp;
	return true;
}

