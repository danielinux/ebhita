# Binary heap - type agnostic

(c) 2012-2016 Daniele Lacamera <root@danielinux.net>

### Introduction

This is a preprocessor-only implementation of a type agnostic binary heap data structure.
Inserting ordered elements is O(logN), peeking the first element is O(1).

For its properties, this data structure is indicated to implement timers.

### Usage

 * Create a data type you want to order, like:
```
        typedef struct potato {
            /* some fields ... */
            uint32_t weight;    /* Field used for sorting */
            /* more fields ... */
        } potato_t; 
```

 * Use the macro `DECLARE_HEAP` to automatically generate the functions tailored on your type and ordering fields. For the structure above this will be:

`DECLARE_HEAP(potato_t, weight);`

 * There is now a new type `heap_potato_t` that describes the binary heap itself. You can create a new binary heap by calling:

`heap_potato_t *pHeap = heap_init();`

 * The macro will also create the following inline functions:

    * `void heap_destroy(heap_type *h)` : dealloc the binary heap and all its content.
    * `int heap_insert(heap_type *heap, element_type *element)` : insert a new element of the given type into the heap. Return value is the new element id which is automatically created. A negative return value indicates an error. `errno` is set accordingly.
    * `int heap_first(heap_type *heap)` : fetch the first element of the heap, without removing it from the structure. Useful to look inside the first element before deciding if it is time to peek.
    * `int heap_peek(heap_type *heap, element_type *element)` : fetch the first element of the heap, and removes it from the structure. Returns 0 in case of success, and the result is put in the element pointed by `element`. Returns  -1 on error and `errno` is set accordingly.
    * `int heap_delete(heap_type *heap, int id)` : deletes the element with id `id` from the heap. `id` is the id number returned by `heap_insert`. Returns 0 in case of success, -1 on error, and `errno` is set accordingly.


### License

See COPYING.

