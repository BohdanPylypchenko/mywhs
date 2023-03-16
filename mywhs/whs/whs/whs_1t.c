#include "whs/whs.h"

#include "list/list/list.h"
#include "whs/whs_p/whc_p.h"

/**
 * whs_1t implementation
 */
list *whs_1t(const char *filename,
             const char *root_dir_path) {
    whs_p_args a = {root_dir_path, filename };
    return (list *) whs_p((void *) &a);
}
