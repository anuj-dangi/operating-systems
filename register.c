#include<stdio.h>
#include<time.h>


int main()
{
    register clock_t start = clock(), end;
    register int i;
    register double elapsed;

    register char s = 'a';

    for(i=0;i<10000;i++)
    {
        printf("%c\n", s);
    }

    end = clock();
    elapsed = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("%f", elapsed);

    return 0;
}
