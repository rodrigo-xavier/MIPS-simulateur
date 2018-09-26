#include "../include/memory.h"
#include "../include/recorder.h"
#include "../include/global.h"
#include "../include/init.h"

int main(int argc, char *argv[])
{
    DEBUG = false;
    strcpy(DIR, "teste");

    init();

    return 0;
}