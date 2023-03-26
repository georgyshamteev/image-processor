#ifndef CPP_HSE_APPLICATION_H
#define CPP_HSE_APPLICATION_H

#include <iostream>
#include "command_parser.h"
#include "bmp.h"
#include "filters.h"
#include "filter_producing.h"
#include "pipeline.h"

class Application {
public:
    Application(int argc, char* argv[]);
    void Run();

private:
    int argc_;
    char** argv_;
    void ApplyFilters(Bitmap& bm, Pipeline& pipeline);
};

#endif  // CPP_HSE_APPLICATION_H
