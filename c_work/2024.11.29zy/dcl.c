#include "dcl.h"

void dcl(void)
{
    int ns;
    for (ns = 0; gettoken() == '*'; ) // count *'s
        ns++;
    dirdcl();
    while (ns-- > 0)
        strcat(out, " pointer to");
}