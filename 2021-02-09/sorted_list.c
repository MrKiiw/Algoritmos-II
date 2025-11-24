#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "sorted_list.h"

struct list_t {
	elem_t data;
	struct list_t* next;
};

struct _node {
	unsigned int size;
	struct list_t* first;
};

static bool invariant(sorted_list_t list) {
	assert(list != NULL);
	struct list_t* aux_list = list->first;
	bool is_sorted = true;
	while(aux_list != NULL && aux_list->next != NULL && is_sorted){
		if(aux_list->data > aux_list->next->data) {
			is_sorted = false;
		}
		aux_list = aux_list->next;
	}
	aux_list = NULL;
	return is_sorted;
}

static sorted_list_t copy_list(sorted_list_t list) {
	unsigned int i = list->size;
	sorted_list_t copied_list = sorted_list_empty();
	struct list_t* aux = list->first;
	while(i > 0 && aux != NULL) {
		copied_list = sorted_list_append(copied_list, aux->data);
		aux = aux->next;
		i--;
	}
	aux = NULL;
	return copied_list;
}

static struct list_t* destroy_node(struct list_t* list) {
	assert(list != NULL);
	list->next = NULL;
	free(list);
	list = NULL;

	assert(list == NULL);
	return list;
}

static struct list_t* where_to_insert(sorted_list_t list, struct list_t* previous, elem_t elem) {
	assert(list != NULL && previous == list->first);
	while(previous != NULL && previous->next != NULL && previous->next->data <= elem) {
		previous = previous->next;
	}

	assert(invariant(list));
	return previous;
}

static sorted_list_t insert(sorted_list_t list, struct list_t* previous, elem_t elem) {
	assert(list != NULL && invariant(list));
	if(previous != NULL && previous->data <= elem) {
		struct list_t* aux = previous->next;
		struct list_t* new = malloc(sizeof(struct list_t));
		new->data = elem;
		new->next = aux;
		previous->next = new;
		aux = NULL;
		previous = NULL;
	}
	else {
		struct list_t* aux = list->first;
		list->first = malloc(sizeof(struct list_t));
		list->first->data = elem;
		list->first->next = aux;
		aux = NULL;
	}
	assert(invariant(list));
	return list;
}

sorted_list_t sorted_list_empty() {
	sorted_list_t new_list = malloc(sizeof(struct _node));
	new_list->size = 0;
	new_list->first = NULL;

	assert(new_list != NULL && invariant(new_list));
	return new_list;
}

bool sorted_list_is_empty(sorted_list_t list) {
	assert(list != NULL);
	return list->first == NULL && list->size == 0;
}

elem_t sorted_list_head(sorted_list_t list) {
	assert(list->first != NULL && list != NULL && invariant(list));
	return list->first->data;
}

sorted_list_t sorted_list_append(sorted_list_t list, elem_t elem) {
	assert(invariant(list) && list != NULL);
	struct list_t* previous = list->first;
	previous = where_to_insert(list, previous, elem);
	list = insert(list, previous, elem);
	list->size++;
	previous = NULL;
	assert(invariant(list));
	return list;
}

sorted_list_t sorted_list_tail(sorted_list_t list) {
	assert(invariant(list) && list != NULL && !sorted_list_is_empty(list));
	if (list->size == 1) {
		destroy_node(list->first);
		list->first = NULL;
		list->size--;
	}
	else {
		struct list_t* aux = list->first;
		list->first = list->first->next;
		aux = destroy_node(aux);
		list->size--;
		aux = NULL;
	}
	assert(invariant(list) && list != NULL);
	return list;
}

unsigned int sorted_list_length(sorted_list_t list) {
	assert(invariant(list) && list != NULL);
	return list->size;
}

elem_t sorted_list_elem_at(sorted_list_t list, unsigned int index) {
	assert(invariant(list) && list != NULL && index > 0 && index <= list->size);
	struct list_t* aux = list->first;
	unsigned int i = 1;
	while(i != index && aux->next != NULL) {
		aux = aux->next;
	}

	assert(invariant(list) && list != NULL);
	return aux->data;
}

sorted_list_t sorted_list_take(sorted_list_t list, unsigned int num) {
	assert(invariant(list) && list != NULL && num <= list->size);
	sorted_list_t taken_list = sorted_list_empty();
	sorted_list_t aux = copy_list(list);
	while(num > 0) {
		taken_list = sorted_list_append(taken_list, sorted_list_head(aux));
		aux = sorted_list_tail(aux);
		num--;
	}
	sorted_list_destroy(aux);
	aux = NULL;

	assert(invariant(list) && list != NULL && taken_list != NULL);
	return taken_list;
}

sorted_list_t sorted_list_drop(sorted_list_t list, unsigned int num) {
	assert(invariant(list) && list != NULL && num <= list->size && num > 0);
	sorted_list_t dropped_list = copy_list(list);
	while(num != 0) {
		dropped_list = sorted_list_tail(dropped_list);
		num--;
	}
	return dropped_list;
}

void sorted_list_print(sorted_list_t list) {
	assert(invariant(list) && list != NULL);
	unsigned int i = list->size;
	struct list_t* aux = list->first;
	printf("[");
	while(i > 0 && aux != NULL) {
		if(i == 1) {
			printf("%d", aux->data);
		}
		else {
			printf("%d, ", aux->data);
		}
		aux = aux->next;
		i--;
	}
	printf("]\n");
	aux = NULL;
}

sorted_list_t sorted_list_destroy(sorted_list_t list) {
	assert(invariant(list) && list != NULL);
	struct list_t* current = list->first;
	while(current != NULL) {
		struct list_t* next = current->next;
		destroy_node(current);
		current = next;
	}
	current = NULL;
	free(list);
	list = NULL;

	return list;
}
