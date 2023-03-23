#include <iostream>
#include "command_parser.h"
#include "bmp.h"
#include "filters.h"
#include "filter_producing.h"
#include "application.h"

void Test1(int argc, char* argv[]) {
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
    try {

        Application app(argc, argv);
        app.Run();
    } catch (const std::exception& e) {

    }
    return 0;
}
