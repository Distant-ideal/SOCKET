/*************************************************************************
	> File Name: Queue.h
	> Author: gongpixi
	> Mail: 1371854096@qq.com
	> Created Time: 2018年12月23日 星期日 16时03分58秒
 ************************************************************************/

#ifndef _QUEUE_H
#define _QUEUE_H

typedef struct Queue {
    char **data;
    int *port;
    int head, tail, length, cnt;
    pthread_mutex_t mutex;
    pthread_cond_t is_full;
    pthread_cond_t is_empty;
} Queue;

Queue *init(int n) {
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->length = n; 
    q->cnt = 0;
    q->data = (char **)malloc(sizeof(char*) * n );
    q->port = (int *)malloc(sizeof(int) * n);
    q->head = 0;
    q->tail = -1;
    pthread_mutex_init(&q->mutex, NULL);
    pthread_cond_init(&q->is_full, NULL);
    pthread_cond_init(&q->is_empty, NULL);
    return q;
}

int push (Queue *q, char *ip, int port) {
    if(pthread_mutex_lock(&q->mutex) != 0) {
        return -1;
    }
    if(q->cnt == q->length) return 0;
    q->tail += 1;
    if(q->tail >= q->length) q->tail -= q->length;
    q->cnt += 1;
    q->data[q->tail] = strdup(ip);
    q->port[q->tail] = port;
	if(pthread_mutex_unlock(&q->mutex) != 0) {
        return  -1;
    }
    return 1;
}

int empty(Queue *q) {
    return q->head > q->tail;
}

void pop(Queue *q) {
    //if(pthread_mutex_lock(&q->mutex) != 0) {
    //    return (void)-1;
    //}
    //if(empty(q)) return ;
    q->head += 1;
    if(q->head > q->length) q->head -= q->length;
    q->cnt -= 1;
    //if(pthread_mutex_unlock(&q->mutex) != 0) {
    //    return (void)-1;
    //} 
    return ;
}
 
int front(Queue *q) {
    if(empty(q)) return 0;
    return q->data[q->head], q->port[q->head];
}

void output(Queue *q) {
    if(pthread_mutex_lock(&q->mutex) != 0) {
        return (void)-1;
    }
    for(int i = 0 ; i < q->cnt; i++) {
        int ind = (q->head + i) % q->length;
        printf("%s %d\n", q->data[ind], q->port[ind]);
    }
	if(pthread_mutex_unlock(&q->mutex) != 0) {
        return (void)-1;
    }
    return ;
}

/*void clear(Queue *q) {
    if(q == NULL) return ;
    free(q->data);
    free(q);
    return ;
}*/
#endif
