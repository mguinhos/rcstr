#include <stdio.h>
#include "rcstr.h"

int main()
{
    rcstr banana = rcstr__new("banana");
    rcstr pijama = rcstr__new("pijama");

    for (int i=0; i < 4; i++)
    {
        printf("iteration: %i\n", i);
        puts(banana.raw);
        puts(pijama.raw);
        
        banana = rcstr__copy(&banana);
        pijama = rcstr__copy(&pijama);
    }
}
