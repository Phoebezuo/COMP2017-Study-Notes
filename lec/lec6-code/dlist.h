/* dlist.h */

struct dlist {

	void * data;
	
	
	struct dlist *next;
	struct dlist *prev;
};

extern int dlist_size;
