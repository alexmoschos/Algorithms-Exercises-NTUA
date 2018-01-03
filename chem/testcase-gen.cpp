#include <iostream>
#include <cstdio>
#include <time.h>
#include <stdlib.h>
using namespace std;


int main(int argc, char const *argv[])
{
    FILE* f = freopen(argv[1],"w",stdout);
    int N,K;
    std::ios_base::sync_with_stdio(false);
    srand (time(NULL));
    N = 2500;
    K = 700;
    for (int i = 0; i < N; ++i)
    {
        for (int j = i+1; j < N; ++j)
        {
            int a = rand()%99 + 1;
            cout << a;
        }
        cout << endl;
    }


    return 0;
}