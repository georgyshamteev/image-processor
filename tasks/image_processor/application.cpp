#include "application.h"

Application::Application(int argc, char** argv) : argc_(argc), argv_(argv) {
}

void Application::Run() {
    Parser parser;
    parser.Parse(argc_, argv_);

    Bitmap bm;

    std::string s(parser.GetInputFileName());

    bm.ReadBmp(static_cast<std::string>(parser.GetInputFileName()));

    Pipeline pipeline(parser.GetFilterDescriptors());

    std::vector<std::unique_ptr<BasicFilter>> pipe = pipeline.CreatePipeline();

    for (const auto& i : pipe) {
        i->ApplyFilter(bm);
        std::cout << "FILTER APPLIED" << std::endl;
    }

    bm.WriteBmp(static_cast<std::string>(parser.GetOutputFileName()));
}
