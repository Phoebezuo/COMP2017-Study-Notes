#ifndef ITERATOR_H
#define ITERATOR_H

struct iterator {
	void* cursor;
	void* (*next)(void*);
};

void iter_traverse(struct iterator* iter, void(*fn)(void*));
#endif
