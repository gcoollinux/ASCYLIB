#ifndef _BST_ARAVIND_H_INCLUDED_
#define _BST_ARAVIND_H_INCLUDED_

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "lock_if.h"
#include "common.h"
#include "atomic_ops_if.h"
#include "ssalloc.h"
#include "ssmem.h"

#define TRUE 1
#define FALSE 0

#define INF2 (KEY_MAX + 2)
#define INF1 (KEY_MAX + 1)
#define INF0 (KEY_MAX)

#define MAX_KEY KEY_MAX
#define MIN_KEY 0

typedef uint8_t bool_t;

extern __thread ssmem_allocator_t* alloc;

typedef ALIGNED(64) struct node_t node_t;

struct node_t{
    skey_t key;
    sval_t value;
    node_t* right;
    node_t* left;
};

typedef struct seekRecord{
    node_t* ancestor;
    node_t* successor;
    node_t* parent;
    node_t* leaf;
} seekRecord_t;


node_t* initialize_tree();
void bst_init_local();
node_t* create_node(skey_t k, sval_t value, int initializing);
seekRecord_t * bst_seek(skey_t key, node_t* node_r, node_t* node_s);
sval_t bst_search(skey_t key, node_t* node_r, node_t* node_s);
bool_t bst_insert(skey_t key, sval_t val, node_t* node_r, node_t* node_s);
sval_t* bst_remove(skey_t key, node_t* node_r, node_t* node_s);
bool_t bst_cleanup(skey_t key);
uint32_t bst_size(node_t* r);

static inline uint64_t GETFLAG(update_t ptr) {
    return ((uint64_t)ptr) & 3;
}

static inline uint64_t FLAG(update_t ptr, uint64_t flag) {
    return (((uint64_t)ptr) & 0xfffffffffffffffc) | flag;
}

static inline uint64_t UNFLAG(update_t ptr) {
    return (((uint64_t)ptr) & 0xfffffffffffffffc);
}

#endif
