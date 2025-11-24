#include <stdio.h>
#include <stdlib.h>
#include "sorted_list.h"
#include "sort.h"

#define MAX_LENGTH 10
/* ----------------------------------TESTS DE TAD----------------------------------
void test_drop(void) {
	sorted_list_t input = sorted_list_empty();
	input = sorted_list_append(input, 3);
	input = sorted_list_append(input, 5);
	input = sorted_list_append(input, 10);
	input = sorted_list_append(input, 17);
	input = sorted_list_append(input, 20);
	sorted_list_t dropped = sorted_list_drop(input, 3);

	printf("Testing drop. Expected: [17, 20]\nResult:");
	sorted_list_print(dropped);
	sorted_list_destroy(dropped);
	sorted_list_destroy(input);
//-----------------------
	sorted_list_t input2 = sorted_list_empty();
	input2 = sorted_list_append(input2, 3);
	input2 = sorted_list_append(input2, 5);
	input2 = sorted_list_append(input2, 10);

	sorted_list_t dropped2 = sorted_list_drop(input2, 3);

	printf("Testing drop. Expected: []\nResult:");
	sorted_list_print(dropped2);
	sorted_list_destroy(dropped2);
	sorted_list_destroy(input2);
}

void test_take(void) {
	sorted_list_t input = sorted_list_empty();
	input = sorted_list_append(input, 3);
	input = sorted_list_append(input, 5);
	input = sorted_list_append(input, 10);
	input = sorted_list_append(input, 17);
	input = sorted_list_append(input, 20);

	sorted_list_t taken = sorted_list_take(input, 3);

	printf("Testing take. Expected: [3, 5, 10]\nResult:");
	sorted_list_print(taken);
	sorted_list_destroy(taken);
	sorted_list_destroy(input);
	//-----------------------
	sorted_list_t input2 = sorted_list_empty();
	input2 = sorted_list_append(input2, 3);
	input2 = sorted_list_append(input2, 5);
	input2 = sorted_list_append(input2, 10);
	input2 = sorted_list_append(input2, 17);
	input2 = sorted_list_append(input2, 20);

	sorted_list_t taken2 = sorted_list_take(input2, 1);

	printf("Testing take. Expected: [3]\nResult:");
	sorted_list_print(taken2);
	sorted_list_destroy(taken2);
	sorted_list_destroy(input2);
	//-----------------------
	sorted_list_t input3 = sorted_list_empty();
	input3 = sorted_list_append(input3, 3);
	input3 = sorted_list_append(input3, 5);
	input3 = sorted_list_append(input3, 10);
	input3 = sorted_list_append(input3, 17);
	input3 = sorted_list_append(input3, 20);

	sorted_list_t taken3 = sorted_list_take(input3, 0);

	printf("Testing take. Expected: []\nResult:");
	sorted_list_print(taken3);
	sorted_list_destroy(taken3);
	sorted_list_destroy(input3);
	//-----------------------
	sorted_list_t input4 = sorted_list_empty();
	input4 = sorted_list_append(input4, 3);
	input4 = sorted_list_append(input4, 5);
	input4 = sorted_list_append(input4, 10);
	input4 = sorted_list_append(input4, 17);
	input4 = sorted_list_append(input4, 20);

	sorted_list_t taken4 = sorted_list_take(input4, 5);

	printf("Testing take. Expected: [3, 5, 10, 17, 20]\nResult:");
	sorted_list_print(taken4);
	sorted_list_destroy(taken4);
	sorted_list_destroy(input4);
}

void test_tail(void) {
	sorted_list_t input = sorted_list_empty();
	input = sorted_list_append(input, 3);
	input = sorted_list_append(input, 5);
	input = sorted_list_append(input, 10);
	input = sorted_list_append(input, 17);
	input = sorted_list_append(input, 20);

	input = sorted_list_tail(input);

	printf("Testing tail. Expected: [5, 10, 17, 20]\nResult:");
	sorted_list_print(input);
	//-----------------------
	input = sorted_list_tail(input);

	printf("Testing tail. Expected: [10, 17, 20]\nResult:");
	sorted_list_print(input);
	//-----------------------
	input = sorted_list_tail(input);

	printf("Testing tail. Expected: [17, 20]\nResult:");
	sorted_list_print(input);
	//-----------------------
	input = sorted_list_tail(input);

	printf("Testing tail. Expected: [20]\nResult:");
	sorted_list_print(input);
	//-----------------------
	input = sorted_list_tail(input);

	printf("Testing tail. Expected: []\nResult:");
	sorted_list_print(input);
	sorted_list_destroy(input);
}

void test_head(void) {
	sorted_list_t input = sorted_list_empty();
	input = sorted_list_append(input, 3);
	input = sorted_list_append(input, 5);
	input = sorted_list_append(input, 10);
	input = sorted_list_append(input, 17);
	input = sorted_list_append(input, 20);

	elem_t head = sorted_list_head(input);

	printf("Testing head. Expected: 3\nResult: %d\n", head);
	sorted_list_destroy(input);
	//-----------------------
	sorted_list_t input2 = sorted_list_empty();
	input2 = sorted_list_append(input2, 3);

	elem_t head2 = sorted_list_head(input2);

	printf("Testing head. Expected: 3\nResult: %d\n", head2);
	sorted_list_destroy(input2);
	//-----------------------
	sorted_list_t input3 = sorted_list_empty();
	input3 = sorted_list_append(input3, 100);
	input3 = sorted_list_append(input3, 1001);
	input3 = sorted_list_append(input3, 1002);

	elem_t head3 = sorted_list_head(input3);

	printf("Testing head. Expected: 100\nResult: %d\n", head3);
	sorted_list_destroy(input3);
}

void test_index(void) {
	sorted_list_t input = sorted_list_empty();
	input = sorted_list_append(input, 3);
	input = sorted_list_append(input, 5);
	input = sorted_list_append(input, 10);
	input = sorted_list_append(input, 17);
	input = sorted_list_append(input, 20);

	elem_t index = sorted_list_elem_at(input, 1);

	printf("Testing index. Expected: 3\nResult: %d\n", index);
	sorted_list_destroy(input);
	//-----------------------
	sorted_list_t input2 = sorted_list_empty();
	input2 = sorted_list_append(input2, 1000);
	input2 = sorted_list_append(input2, 1001);
	input2 = sorted_list_append(input2, 1002);

	elem_t index2 = sorted_list_elem_at(input2, 3);

	printf("Testing index. Expected: 1002\nResult: %d\n", index2);
	sorted_list_destroy(input);
}

void test_length(void) {
	sorted_list_t input = sorted_list_empty();
	input = sorted_list_append(input, 3);
	input = sorted_list_append(input, 5);
	input = sorted_list_append(input, 10);
	input = sorted_list_append(input, 17);
	input = sorted_list_append(input, 20);

	unsigned int length = sorted_list_length(input);

	printf("Testing length. Expected: 5\nResult: %u\n", length);
	sorted_list_destroy(input);
//-----------------------
	sorted_list_t input2 = sorted_list_empty();

	unsigned int length2 = sorted_list_length(input2);

	printf("Testing length. Expected: 0\nResult: %u\n", length2);
	sorted_list_destroy(input2);
}

void test_append(void) {
	sorted_list_t input = sorted_list_empty();
	input = sorted_list_append(input, 6);
	input = sorted_list_append(input, 100);
	input = sorted_list_append(input, 105);
	input = sorted_list_append(input, 1000);

	printf("Testing append. Expected: [6, 100, 105, 1000].\nResult:");
	sorted_list_print(input);
	printf("Length of append should be 4. Length is: %u\n", sorted_list_length(input));
	sorted_list_destroy(input);
}

int main() {
	test_drop();
	test_take();
	test_tail();
	test_head();
	test_index();
	test_length();
	test_append();
} */
/* ----------------------------------TESTS DE SORT---------------------------------- */
int main() {
	int array[MAX_LENGTH] = {7, 3, 10, 5, 13, 0, -1, 89, 2, 5};
	sort(array, 10);
	int array2[MAX_LENGTH] = {8, 0, 0, 0, 1, -100, 91};
	sort(array2, 7);
	int array3[MAX_LENGTH] = {0};
	sort(array3, 0);
}