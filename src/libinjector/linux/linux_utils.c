#include "linux_utils.h"

void free_memtraps(injector_t injector)
{
    GSList* loop = injector->memtraps;
    injector->memtraps = NULL;

    while (loop)
    {
        drakvuf_remove_trap(injector->drakvuf, loop->data, (drakvuf_trap_free_t)free);
        loop = loop->next;
    }
    g_slist_free(loop);
}

void free_injector(injector_t injector)
{
    if (!injector) return;

    PRINT_DEBUG("Injector freed\n");

    if (injector->memtraps)
        free_memtraps(injector);

    if (injector->memdata.data)
        g_free((void*)injector->memdata.data);
    if (injector)
        g_free((void*)injector);

    injector = NULL;
}
