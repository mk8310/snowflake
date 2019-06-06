/**
You need libevent2 to compile this piece of code
Please see: http://libevent.org/
Or you can simply run this command to install on Mac: brew install libevent
**/

#include <iostream>
#include <evdns.h>
#include <unistd.h>
#include <getopt.h>

#include "netUtils.h"
#include "SnowFlake.h"

using namespace std;

int main(int argc, char *const argv[]) {
    int port = 9999, listenNum = 10;

//    const char *optString = "p:l";
//    int opt = 0;
//    while ((opt = getopt(argc, argv, optString)) != -1) {
//        char optChar = (char) opt;
//        const char *optargStr = optarg == nullptr ? "" : (char *) optarg;
//        cout << optChar << ":" << optargStr << endl;
////        opt = getopt(argc, argv, optString);
//    }

    /* start id service */
    serve(port, listenNum);

    return 0;
}
