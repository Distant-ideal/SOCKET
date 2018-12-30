/*************************************************************************
	> File Name: search.h
	> Author: gongpixi
	> Mail: 1371854096@qq.com
	> Created Time: 2018年12月23日 星期日 16时05分52秒
 ************************************************************************/

#ifndef _SEARCH_H
#define _SEARCH_H

int search(Queue *q, char *ip) {
    for(int i = 0; i < q->cnt; i++) {
        char ip2[1000];
        strcpy(ip2, q->data[i]);
        if(!strcmp(ip, ip2)) {
            return 1;
        }
    }
    return 0;
}

int search_in(int a[], int n) {
    int min = 20000, ans = 0;
    for(int i = 0; i < n; i++) {
        if(a[i] < min) {
            min = a[i];
            ans = i;
        }
    }
    return ans;
}

#endif
