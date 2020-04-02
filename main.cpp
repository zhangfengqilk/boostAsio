#include <iostream>
#include <string.h>
#include "serialport/CodeScannerComConnect.h"
#include "testconsumer.h"
using namespace std;

int main()
{
    testConsumer tc;

    while(1){
        tc.sendstr("hello world \r\n");
        sleep(1);
    }
    return 0;
}
