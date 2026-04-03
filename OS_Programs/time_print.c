#include <stdio.h>
#include <time.h>
int main()
 {
    time_t now;
    time(&now); 
    printf("Current system time: %s", ctime(&now)); 
    return 0;
}
