#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>            /* Definition of bool      */
#include <assert.h>

#include "ugraph.h"

struct s_node {
    vertex elem;
    struct s_node *next;
    struct s_node *succ;

};

typedef struct s_node *node_t;

struct s_ugraph {
    unsigned int size;
    node_t first;
};

static bool invrep1(ugraph g){
	//about main structre consistency
	return g!=NULL;
}

static bool invrep2(ugraph g){
	//about graph size consistency
	node_t node = g->first;
	unsigned int n = 0;
    while (node!=NULL) {
        node = node->next;
        n++;
    }
    return n == g->size;
}

static bool invrep3(ugraph g){
	//about uniqueness of vertexes
	node_t evaluated = g->first;
	bool are_uniq = true;
	node_t compared;
	
	for (unsigned int i = g->size; i != 0 && are_uniq && evaluated != NULL; i--) {
		int to_check = g->size;
		compared = evaluated->next;
		to_check -= to_check;
		while (to_check != 0 && are_uniq) {
			if (evaluated->elem == compared->elem) {
				are_uniq = false;
			}
			compared = compared->next;
			to_check--;
		}
		evaluated = evaluated->next;
	}
	return are_uniq;
}

static bool invrep(ugraph g){
	return invrep1(g) && invrep2(g) && invrep3(g);
}

static node_t create_node(vertex v){
	node_t new_node = malloc(sizeof(struct s_node));
	if (new_node == NULL) {
		fprintf(stderr, "ERROR: memory could not be allocated\n");
		exit(EXIT_FAILURE);
	}

	new_node->elem = v;
	new_node->next = NULL;
	new_node->succ = NULL;

	return new_node;
}

static node_t destroy_node(struct s_node *node){
	assert(node != NULL);
	node->next = NULL;
	node->succ = NULL;
	free(node);
	node = NULL;

	assert(node == NULL);
	return node;
}

static node_t ugraph_get_node(ugraph g,vertex v){
	/*Returns the node of the vertex v*/
	assert(invrep(g) && ugraph_member(g,v));
	node_t node = g->first;
	while (node!=NULL && node->elem != v) {
		node = node->next;
	}
	assert(invrep(g));
	return node;
}

/****************** CONSTRUCTORS ******************/
ugraph ugraph_empty(void) {
	ugraph g = malloc(sizeof(struct s_ugraph));
	g->size = 0;
	g->first = NULL;

	assert(ugraph_is_empty(g) && invrep(g));
	return g;
}

ugraph ugraph_add_vertex(ugraph g, vertex v) {
	assert(invrep(g));
	if(g->first == NULL) {
		g->first = create_node(v);
		g->size++;
	}
	else if (!ugraph_member(g, v)){
			node_t aux_node = g->first;
			while (aux_node->next != NULL) {
				aux_node = aux_node->next;
			}
			aux_node->next = create_node(v);
			aux_node = NULL;
			g->size++;
		}

	assert(invrep(g));
	return g;
}

ugraph ugraph_add_edge(ugraph g, vertex v1, vertex v2){
	assert(invrep(g) && ugraph_member(g,v1) && ugraph_member(g,v2));
	node_t aux_node_v1 = ugraph_get_node(g, v1);
	node_t aux_node_v2 = ugraph_get_node(g, v2);
	aux_node_v1->succ = aux_node_v2;
	aux_node_v1 = NULL;
	aux_node_v2 = NULL;

	assert(invrep(g) && v2 == ugraph_succ(g, v1));
	return g;
}

/******************* OPERATIONS   *******************/
unsigned int ugraph_size(ugraph g){
	assert(invrep(g));
    return g->size;
}

bool ugraph_is_empty(ugraph g){
	assert(invrep(g));
    return g->size==0;
}

bool ugraph_member(ugraph g, vertex v) {
	assert(invrep(g));
	bool is_member = false;
	node_t aux_node = g->first;
	for(int i = g->size; !is_member && aux_node != NULL && i != 0; i--) {
		if(aux_node->elem == v){
			is_member = true;
		}
		aux_node = aux_node->next;
	}
	aux_node = NULL;

	assert(invrep(g));
	return is_member;
}

vertex ugraph_succ(ugraph g, vertex v){
	assert(invrep(g) && ugraph_get_node(g,v)->succ !=NULL);
	node_t node_v = ugraph_get_node(g,v);
	assert(invrep(g));
	return node_v->succ->elem;
}

ugraph ugraph_delete_incoming_edge(ugraph g, vertex v){
	assert(invrep(g));
	if (ugraph_member(g,v)){
		node_t node_v = ugraph_get_node(g,v);
		node_t node = g->first;
		while (node!=NULL){
			if (node->succ == node_v){
				node->succ = NULL;
			}
			node = node->next;
		}
	}
	assert(invrep(g));
	return g;		
}

ugraph ugraph_delete_outcoming_edge(ugraph g, vertex v){
	assert(invrep(g) && ugraph_member(g,v));
	node_t node_v = ugraph_get_node(g,v);
	node_v->succ = NULL;
	assert(invrep(g) && ugraph_get_node(g,v)->succ == NULL);
	return g;		
}

ugraph ugraph_delete_vertex(ugraph g, vertex v){
	assert(invrep(g));
	if(ugraph_member(g, v)) {
		g = ugraph_delete_incoming_edge(g, v);
		node_t prev_node = g->first;
		while(prev_node->next->elem != v && prev_node->next != NULL) {
			prev_node = prev_node->next;
		}
		node_t node_v = ugraph_get_node(g, v);
		prev_node->next = node_v->next;
		node_v = destroy_node(node_v);
		node_v = NULL;
		prev_node = NULL;
		g->size--;
	}

	assert(invrep(g) && !ugraph_member(g, v));
	return g;
}

bool ugraph_path(ugraph g, vertex v1, vertex v2){
	assert(invrep(g) && ugraph_member(g,v1) && ugraph_member(g,v2));
	bool has_path = false;
	node_t aux_node = ugraph_get_node(g, v1);
	if(aux_node->elem == v2) {
		has_path = true;
	}
	aux_node = aux_node->succ;
	for(int i = g->size-1; i != 0 && aux_node != NULL && !has_path; i--) {
		if(aux_node->elem == v2) {
			has_path = true;
		}
		aux_node = aux_node->succ;
	}
	aux_node = NULL;

	assert(invrep(g));
	return has_path;
}

ugraph ugraph_destroy(ugraph g){
    assert(g != NULL && invrep(g));

    node_t current = g->first;
    while (current != NULL) {
        node_t next = current->next;
        destroy_node(current);
        current = next;
    }

	current = NULL;
    free(g);
	g = NULL;
    return g;
}


void ugraph_dump(ugraph g){
	assert(invrep(g));
    // prints the set of vertexes of the unary graph g
    node_t node = g->first;
    printf("Vertexes: ");
    while (node!=NULL ) {
	   printf("%d ", node->elem);
        node = node->next;
    }
    printf("\n");
    // prints the list of edges of the unary graph g
    printf("Edges: \n");
    node = g->first;
    while (node!=NULL ) {
    	if (node->succ != NULL) {
        	printf("\t%d --> %d\n", node->elem, node->succ->elem);
        }
        node = node->next;
    }
   	assert(invrep(g));
}

ugraph ugraph_from_file(const char *filepath){
    FILE *file = NULL;
    file = fopen(filepath, "r");
    if (file == NULL) {
        fprintf(stderr, "File does not exist.\n");
        exit(EXIT_FAILURE);
    }

	//read ugraph size
	int size;
    int res = fscanf(file,"%d", &size);
    if (res != 1) {
    	fprintf(stderr, "Invalid unary graph.\n");
        exit(EXIT_FAILURE);
    }
        
	//load ugraph vertexes
    ugraph g=ugraph_empty();
    int i = 1;
    while (i<=size){
        int elem;
        int res = fscanf(file,"%d", &elem);
        if (res != 1) {
            fprintf(stderr, "1-Invalid unary graph.\n");
            exit(EXIT_FAILURE);
        }
        g = ugraph_add_vertex(g, elem);
        i++;
	}
	//load ugraph edges
    while (!feof(file)){
    int edge1, edge2;
	int res = fscanf(file, "%d --> %d", &edge1, &edge2);
	printf("edge1: %d, edge2: %d\n", edge1, edge2);
	if(res != 2){
		fprintf(stderr, "2-Invalid unary graph.\n");
		exit(EXIT_FAILURE);
	}
	g = ugraph_add_edge(g, edge1, edge2);
    }
   
    fclose(file);
   	assert(invrep(g));
    return g;
}

/*SOLO PARA ALUMNOS LIBRES!!!*/
	/*bool ugraph_cycle(ugraph g){
       	COMPLETAR!!! 
	}*/




