#pragma once
#include<iostream>
#include<cstring>
//#include<conio.h>
using namespace std;

struct PCB {
	int pid;
	string status;
	int priority;
	PCB* next;
	int life;
	void operator = (PCB p) {
		pid = p.pid;
		status = p.status;
		priority = p.priority;
		next = p.next;
		life = p.life;
	}
};

struct ready_queue_node {
	PCB block;
	ready_queue_node* next;
	void operator = (ready_queue_node rqn) {
		block = rqn.block;
		next = rqn.next;
	}
};

class graph_link
{
public:
	graph_link();
	ready_queue_node get_top();
	void inseart(ready_queue_node* target);
	void print_low_priority(int priority);
	void print_same_priority(ready_queue_node* target);
	ready_queue_node get_graph();
	ready_queue_node** graph;
private:
	
};

graph_link::graph_link() {
	graph = new ready_queue_node * [50];
	for (int i = 0; i < 50; i++) {
		graph[i] = new ready_queue_node;
		graph[i]->next = NULL;
	}
}

ready_queue_node graph_link::get_top() {
	ready_queue_node* target = new ready_queue_node;
	target->block.pid = -1;
	for (int i = 49; i >= 0; i--) {
		if (graph[i]->next != NULL) {
			target = graph[i]->next;
			graph[i]->next = target->next;
			return *target;
		}
}
	return *target;
}

void graph_link::inseart(ready_queue_node* target) {
	target->next = graph[target->block.priority]->next;
	graph[target->block.priority]->next = target;
}

ready_queue_node graph_link::get_graph() {
	return **graph;
}

void graph_link::print_same_priority(ready_queue_node* target) {
	ready_queue_node* temp = target->next;
	while (temp != NULL)
	{
		printf("Process pid: %d, status: %s, priority: %d, life: %d \n", temp->block.pid, temp->block.status.c_str(), temp->block.priority, temp->block.life);
		temp = temp->next;
	}
}

void graph_link::print_low_priority(int priority) {
	for (int i = priority - 1; i >= 0; i--) {
		if (graph[i]->next != NULL) {
			print_same_priority(graph[i]);
		}
	}
}