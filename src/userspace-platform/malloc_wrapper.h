#pragma once

#ifdef USERSPACE
# define malloc(p) heap_caps_malloc(p, MALLOC_CAP_8BIT | MALLOC_CAP_INTERNAL)
# define free(p) heap_caps_free(p)
#endif /* USERSPACE */
