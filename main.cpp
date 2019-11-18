#include <iostream>
#include <getopt.h>
#include <string.h>
#include <stdlib.h>

using namespace std;

struct globalArgs_t {
    string version;
    int list[4];
    string install;
} globalArgs;

static const char *optString = "v:l:i:h?";

static const struct option longOpts[] = {
        {"version", optional_argument, nullptr, 'v'},
        {"help",    no_argument,       nullptr, 'h'},
        {"install", required_argument, nullptr, 'i'},
        {"list",    optional_argument, nullptr, 'l'},
        {nullptr,   no_argument,       nullptr, 0}
};

void display_usage() {
    puts("Usage:"
         "\n    -v, --version - optional, string. "
         "\n    -i, --install - required, string."
         "\n    -l, --list - optional, 4 integer numbers."
         "\n    -h, --help - display help.");
    exit(EXIT_FAILURE);
}

void display_args() {
    cout << "version = " << globalArgs.version << endl;
    cout << "list = " << globalArgs.list[0] << ", " <<
         globalArgs.list[1] << ", " <<
         globalArgs.list[2] << ", " <<
         globalArgs.list[3] << "." << endl;
    cout << "install = " << globalArgs.install << endl;
}

int main(int argc, char *argv[]) {
    int opt = 0;
    int longIndex = 0;

    globalArgs.version = "1.0.0";
    globalArgs.list[0] = 0;
    globalArgs.list[1] = 0;
    globalArgs.list[2] = 0;
    globalArgs.list[3] = 0;

    opt = getopt_long(argc, argv, optString, longOpts, &longIndex);
    while (opt != -1) {
        switch (opt) {
            case 'v':
                globalArgs.version = optarg;
                break;

            case 'i':
                globalArgs.install = optarg;
                break;

            case 'l':
                globalArgs.list[0] = optarg[0] - '0';
                globalArgs.list[1] = optarg[2] - '0';
                globalArgs.list[2] = optarg[4] - '0';
                globalArgs.list[3] = optarg[6] - '0';
                break;

            case 'h':
                display_usage();
                break;

            default:
                break;
        }

        opt = getopt_long(argc, argv, optString, longOpts, &longIndex);
    }

    display_args();

    return EXIT_SUCCESS;
}