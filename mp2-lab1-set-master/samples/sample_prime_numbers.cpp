#include "tlist.h"
#include <iostream>
#include <stdio.h>
#include <string>

int main()
{
    TList<int> a;
    int v1 = 1, v2 = 2, v3 = 3, v4 = 4, v5 = 5, v6 = 6;
    a.PushBegin(&v1);
    a.PushEnd(&v2);
    a.PushBegin(&v3);
    a.PushEnd(&v4);
    a.PushBegin(&v5);
    a.PushEnd(&v6);

    for (auto i = a.begin(); i != a.end(); ++i)
        printf("%d\n", **i);
    printf("\n\n");
    TList<int> b = a;

    for (auto i = a.begin(); i != a.end(); ++i)
        printf("%d\n", **i);
    printf("\n\n");


    for (auto i : a)
        printf("%d\n", *i);
    printf("\n\n");
    //std::list<int> c;

    //c.push_front(1);
    //c.push_back(2);
    //c.push_front(3);
    //c.push_back(4);
    //c.push_front(5);
    //c.push_back(6);

    //for (auto i = c.begin(); i != c.end(); ++i)
    //  printf("%d\n", *i);
    //printf("\n\n");
    //  std::cout << *i <<std::endl;
    return 0;
}

