#include "lua.h"

#define TEA_TCURSOR_WORKLOAD 32
#define TEA_TCURSOR_INITITAL 48

#define TEA_TCURSOR_KV_WORKLOAD 16
#define TEA_TCURSOR_KV_INITIAL 24

struct tea_tcursor_part {
	size_t used;
	size_t vlen[TEA_TCURSOR_WORKLOAD];
	const char *value[TEA_TCURSOR_WORKLOAD];
	struct tea_tcursor_part *next;
};

struct tea_tcursor {
	size_t size;
	size_t parts;
	size_t vlen[TEA_TCURSOR_INITITAL];
	const char *value[TEA_TCURSOR_INITITAL];
	struct tea_tcursor_part *first;
	struct tea_tcursor_part *current;
};

int tea_tcursor_add(struct tea_tcursor *, const char *, size_t);
void tea_tcursor_dump(lua_State *L, struct tea_tcursor *);

struct tea_tcursor_kv_part {
	size_t used;
	size_t klen[TEA_TCURSOR_KV_WORKLOAD];
	size_t vlen[TEA_TCURSOR_KV_WORKLOAD];
	const char *key[TEA_TCURSOR_KV_WORKLOAD];
	const char *value[TEA_TCURSOR_KV_WORKLOAD];
	struct tea_tcursor_kv_part *next;
};

struct tea_tcursor_kv {
	size_t size;
	size_t parts;
	size_t klen[TEA_TCURSOR_KV_INITIAL];
	size_t vlen[TEA_TCURSOR_KV_INITIAL];
	const char *key[TEA_TCURSOR_KV_INITIAL];
	const char *value[TEA_TCURSOR_KV_INITIAL];
	struct tea_tcursor_kv_part *first;
	struct tea_tcursor_kv_part *current;
};

int tea_tcursor_kv_add(struct tea_tcursor_kv *, const char *, size_t, const char *, size_t);
void tea_tcursor_kv_dump(lua_State *L, struct tea_tcursor_kv *);
