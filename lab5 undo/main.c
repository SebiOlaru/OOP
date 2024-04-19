#include <stdio.h>
#include <ctype.h>
#include <crtdbg.h>
#include "ui.h"
#include "tests.h"

#define _CRTDBG_MAP_ALLOC
int main() {
    //runAllTests();
    app();
    _CrtDumpMemoryLeaks();
    return 0;
}