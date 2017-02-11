#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include "ObjectGuid.h"

int main()
{
    while (1)
    {
        uint64 guid;
        scanf("%llu",&guid);
        if (guid == 0)
            break;
        ObjectGuid guidObj(guid);
        printf("%s\n",guidObj.GetString().data());
    }
    return 0;
}