#include "application.h"

Application::Application(int argc, char** argv) : argc_(argc), argv_(argv) {
}

void Application::ApplyFilters(Bitmap& bm, Pipeline& pipeline) {
    for (const auto& i : pipeline) {
        i->ApplyFilter(bm);
    }
}

void Application::Run() {
    Parser parser;
    parser.Parse(argc_, argv_);

    Bitmap bm;
    bm.ReadBmp(parser.GetInputFileName());

    PipelineGenerator pipeline_generator(parser.GetFilterDescriptors());
    Pipeline pipeline = pipeline_generator.CreatePipeline();

    ApplyFilters(bm, pipeline);

    bm.WriteBmp(parser.GetOutputFileName());
}
