#include "utl.c"
#include <utl/assert.h>
#include <utl/log.h>
#include <utl/test.h>

#include <cmc/treemap.h>

CMC_GENERATE_TREEMAP(tm, treemap, size_t, size_t)

struct treemap_ftab_key *tm_ftab_key =
    &(struct treemap_ftab_key){ .cmp = cmp,
                                .cpy = copy,
                                .str = str,
                                .free = custom_free,
                                .hash = hash,
                                .pri = pri };

struct treemap_ftab_val *tm_ftab_val =
    &(struct treemap_ftab_val){ .cmp = cmp,
                                .cpy = copy,
                                .str = str,
                                .free = custom_free,
                                .hash = hash,
                                .pri = pri };

CMC_CREATE_UNIT(treemap_test, true, {
    CMC_CREATE_TEST(new, {
        struct treemap *map = tm_new(tm_ftab_key, tm_ftab_val);

        cmc_assert_not_equals(ptr, NULL, map);

        tm_free(map);
    });

    CMC_CREATE_TEST(clear[count], {
        struct treemap *map = tm_new(tm_ftab_key, tm_ftab_val);

        cmc_assert_not_equals(ptr, NULL, map);

        for (size_t i = 0; i < 50; i++)
            tm_insert(map, i, i);

        cmc_assert_equals(size_t, 50, tm_count(map));

        tm_clear(map);

        cmc_assert_equals(size_t, 0, tm_count(map));
        cmc_assert_equals(ptr, NULL, map->root);

        tm_free(map);
    });
});
