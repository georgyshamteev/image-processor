#include <iostream>
#include "command_parser.h"
#include "bmp.h"
#include "filters.h"
#include "filter_producing.h"
#include "application.h"

// void Test1(int argc, char* argv[]) {
//     Parser parser;
//     parser.Parse(argc, argv);
// }
//
// void Test2(int argc, char* argv[]) {
//     Parser parser;
//     parser.Parse(argc, argv);
//     Bitmap bm;
//     bm.ReadBmp(parser.GetInputFileName());
// }
//
// void Test3(int argc, char* argv[]) {
//     Parser parser;
//     parser.Parse(argc, argv);
//     Bitmap bm;
//     bm.ReadBmp(parser.GetInputFileName());
//     bm.WriteBmp(parser.GetOutputFileName());
// }
//
// void Test4(int argc, char* argv[]) {
//     FilterDescriptors test{"crop", {"1500", "1500"}};
// }
//
// void Test5(int argc, char* argv[]) {
//     FilterDescriptors test{"crop", {"1500", "1500", "1500"}};
// }
//
// void Test6(int argc, char* argv[]) {
//     Bitmap bm;
//     bm.ReadBmp("notbmp.txt");
// }
//
// void Test7(int argc, char* argv[]) {
//     FilterDescriptors test{"crop", {"1500", "1500", "1500"}};
//     FilterDescriptors test1{"blur", {"0.1"}};
//     PipelineGenerator gen({test, test1});
//     gen.CreatePipeline();
// }
//
// void Test8(int argc, char* argv[]) {
//     std::string test = "nice.bmp";
//     Bitmap bm;
//     bm.WriteBmp(test);
// }
//
// void Test9(int argc, char* argv[]) {
//     std::string test = "notnice.txt";
//     Bitmap bm;
//     bm.WriteBmp(test);
// }
//
// void Test10(int argc, char* argv[]) {
//     const int tmp = 500;
//     Bitmap bm;
//     bm.ReadBmp("test.bmp");
//     auto a = bm.GetColsNum();
//     auto b = bm.GetRowsNum();
//     bm.Resize(a + tmp, b + tmp);
//     auto c = bm.GetColsNum();
//     auto d = bm.GetRowsNum();
// }

int main(int argc, char** argv) {
    try {
        Application app(argc, argv);
        app.Run();
        return 0;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return -1;
    } catch (...) {
        return -2;
    }
}
