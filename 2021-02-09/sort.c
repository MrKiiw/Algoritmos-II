#include <stdlib.h>
#include <stdio.h>
#include "sorted_list.h"
#include "sort.h"

sorted_list_t array_to_list (int a[], unsigned int length) {
	sorted_list_t list = sorted_list_empty();
	unsigned int i = 0;
	while(length > i) {
		list = sorted_list_append(list, a[i]);
		i++;
	}
	return list;
}

void sort(int a[], unsigned int length) {
	sorted_list_t list = array_to_list(a, length);
	sorted_list_print(list);
	sorted_list_destroy(list);
}