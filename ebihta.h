/*-----------------------------------------------------------------------*
 |                               EBIHTA                                  |
 |    EBITHA is Binary heap - type-Agnostic - library implementation     |
 |         (c) 2012 Daniele Lacamera <root@danielinux.net>               |
 |           Released under the terms of WTFPL, version 2.               |
 |                                                                       |
 |            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE                |
 |                      Version 2, December 2004                         |
 |                                                                       |
 |                                                                       |
 |  Everyone is permitted to copy and distribute verbatim or modified    |
 | copies of this license document, and changing it is allowed as long   |
 |                      as the name is changed.                          |
 |                                                                       |
 |            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE                |
 |  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION      |
 |                                                                       |
 |              0. You just DO WHAT THE FUCK YOU WANT TO.                |
 |                                                                       |
 |                                                                       |
 *-----------------------------------------------------------------------*/

#include <stdint.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#define DECLARE_HEAP(type, orderby) \
struct heap_##type { 	\
	uint32_t size; 		\
	uint32_t n; 		\
	type *top;  		\
}; \
typedef struct heap_##type heap_##type; \
static inline int heap_insert(struct heap_##type *heap, type *el) \
{ \
	int i; \
    if (++heap->n >= heap->size) {													\
		heap->top = realloc(heap->top, (heap->n + 1) * sizeof(type));				\
		if (!heap->top) {															\
			heap->n--;																\
			return -1;																\
		}																			\
		heap->size++;																\
	}																				\
	if (heap->n == 1) {															\
		memcpy(&heap->top[1], el, sizeof(type));									\
		return 0;																	\
	}																				\
	for (i = heap->n; (i > 1) && (heap->top[i / 2].orderby > el->orderby; i /= 2)) {			\
		memcpy(&heap->top[i], &heap->top[i / 2], sizeof(type));						\
	}				\
	memcpy(&heap->top[i], el, sizeof(type));										\
	return 0; 																		\
} \
static inline int heap_peek(struct heap_##type *heap, type *first) \
{ \
	type *ptr = NULL; 		\
	type *last;				\
	int i, child;			\
	if(heap->n == 0) {		\
		errno = ENOENT;		\
		return -1; 			\
	}						\
	memcpy(first, &heap->top[1], sizeof(type));		\
	last = &heap->top[heap->n--];					\
	for(i = 1; (i * 2) <= heap->n; i = child) {		\
		child = 2 * i;								\
		if ((child != heap->n) && 					\
			(heap->top[child + 1]).orderby 			\
			< (heap->top[child]).orderby)			\
			child++;								\
		if (last->orderby > 						\
			heap->top[child].orderby)				\
			memcpy(&heap->top[i], &heap->top[child],\
					sizeof(type));					\
		else										\
			break;									\
	}												\
	memcpy(&heap->top[i], last, sizeof(type));		\
	return 0;										\
} \
static inline type *heap_first(heap_##type *heap)	\
{ \
	if (heap->n == 0)		\
		return NULL;		\
	return &heap->top[1];	\
} \
static inline heap_##type *heap_init(void) \
{ \
	heap_##type *p = calloc(1, sizeof(heap_##type));	\
	return p;		\
} \
static inline void heap_destroy(heap_##type *h) \
{ \
	free(h->top); 	\
	free(h); 		\
} \


