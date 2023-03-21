#include <iostream>
#include "command_parser.h"
#include "bmp.h"

void Test1(int argc, char*argv[]) {
    Parser parser;
    parser.Parse(argc, argv);
}

void Test2(int argc, char* argv[]) {
    Parser parser;
    parser.Parse(argc, argv);
    Bitmap bm;
    bm.ReadBmp(static_cast<std::string>(parser.GetInputFileName()));
}

void Test3(int argc, char* argv[]) {
    Parser parser;
    parser.Parse(argc, argv);
    Bitmap bm;
    bm.ReadBmp(static_cast<std::string>(parser.GetInputFileName()));
    bm.WriteBmp(static_cast<std::string>(parser.GetOutputFileName()));
}


int main(int argc, char** argv) {
    Test1(argc, argv);
    Test2(argc, argv);
    Test3(argc, argv);
    return 0;
}
