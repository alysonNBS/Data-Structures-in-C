#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// data structs: stack, queue and priority queue
struct stack {
	int top;
	int stack[1000];
};
struct queue {
	int begin;
	int end;
	int queue[1000];
};
struct priority_queue {
	int bigger;
	struct priority_queue *left, *right, *parent;
	int size;
};


// functions for the data structs
// functions for stack
struct stack new_stack();
void stack_push(struct stack *stack, int x);
void stack_pop(struct stack *stack);
int stack_top(struct stack *stack);
int stack_size(struct stack *stack);
bool stack_empty(struct stack *stack);
// functions for queue
struct queue new_queue();
void queue_push(struct queue *queue, int x);
void queue_pop(struct queue *queue);
int queue_front(struct queue *queue);
int queue_back(struct queue *queue);
int queue_size(struct queue *queue);
bool queue_empty(struct queue *queue);
// functions for priority queue
void new_priority_queue(struct priority_queue *pq);
void pq_push(struct priority_queue *pq, int x);
void pq_pop(struct priority_queue *pq);
int pq_top(struct priority_queue *pq);
int pq_size(struct priority_queue *pq);
bool pq_empty(struct priority_queue *pq);



// functions for stack
struct stack new_stack() {
	struct stack stack;
	stack.top = -1;
	
	return stack;
}
void stack_push(struct stack *stack, int x) {
	stack->stack[++stack->top] = x;
}
void stack_pop(struct stack *stack) {
	stack->top--;
}
int stack_top(struct stack *stack) {
	return stack->stack[stack->top];
}
int stack_size(struct stack *stack) {
	return stack->top+1;
}
bool stack_empty(struct stack *stack) {
	return stack->top == -1;
}

// functions for queue
struct queue new_queue() {
	struct queue queue;
	queue.begin = 0;
	queue.end = -1;
	
	return queue;
}
void queue_push(struct queue *queue, int x) {
	queue->queue[++queue->end] = x;
}
void queue_pop(struct queue *queue) {
	queue->begin++;
}
int queue_front(struct queue *queue) {
	return queue->queue[queue->begin];
}
int queue_back(struct queue *queue) {
	return queue->queue[queue->end];
}
int queue_size(struct queue *queue) {
	return queue->end - queue->begin + 1;
}
bool queue_empty(struct queue *queue) {
	return queue->begin > queue->end;
}

// functions for priority queue
void new_priority_queue(struct priority_queue *pq) {
	pq->bigger = -1; // -INFINITE
	pq->size = 0;
	pq->parent = pq->left = pq->right = NULL;
	
}
void pq_push(struct priority_queue *pq, int x) {
	if( pq_empty(pq) ) {
		pq->bigger = x;

		pq->left = (struct priority_queue *) malloc(sizeof(struct priority_queue));
		pq->right = (struct priority_queue *) malloc(sizeof(struct priority_queue));

		new_priority_queue(pq->left);
		new_priority_queue(pq->right);

		pq->left->parent = pq->right->parent = pq;
	}
	else {
		if( pq->bigger < x ) {
			int aux = pq->bigger;
			pq->bigger = x;
			x = aux;
		}
		
		if( pq->left->size > pq->right->size )
			pq_push(pq->right, x);
		else
			pq_push(pq->left, x);
	}
	
	pq->size++;
}
void pq_pop(struct priority_queue *pq) {
	if( pq_empty(pq) ) {
		if(pq->parent)
			free(pq);
		return;
	}
	
	pq->size--;

	if( pq->left->bigger > pq->right->bigger ) {
		pq->bigger = pq->left->bigger;

		pq_pop(pq->left);
	}
	else {
		pq->bigger = pq->right->bigger;

		pq_pop(pq->right);
	}
}
int pq_top(struct priority_queue *pq) {
	return pq->bigger;
}
int pq_size(struct priority_queue *pq) {
	return pq->size;
}
bool pq_empty(struct priority_queue *pq) {
	return pq->size == 0;
}