#include <iostream>
#include "command_parser.h"
#include "bmp.h"
#include "filters.h"
#include "filter_producing.h"

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
//    Test1(argc, argv);
//    Test2(argc, argv);
//    Test3(argc, argv);
    Parser parser;
    parser.Parse(argc, argv);
    Bitmap bm;
    bm.ReadBmp(static_cast<std::string>(parser.GetInputFileName()));

//    for (auto descriptor : parser.GetFilterDescriptors()) {
//        auto filter = pipeline.
//    }


    bm.WriteBmp(static_cast<std::string>(parser.GetOutputFileName()));
    return 0;
}
