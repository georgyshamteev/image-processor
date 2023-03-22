#ifndef CPP_HSE_COMMAND_PARSER_H
#define CPP_HSE_COMMAND_PARSER_H

#include <iostream>
#include <vector>

struct FilterDescriptors {
    std::string_view name;
    std::vector<std::string_view> parameters;
};

class Parser {
public:
    bool Parse(int argc, char* argv[]);
    std::string_view GetOutputFileName() const;
    std::string_view GetInputFileName() const;
    const std::vector<FilterDescriptors> GetFilterDescriptors() const;

private:
    std::string_view input_file_name_;
    std::string_view output_file_name_;
    size_t number_of_parameters_;
    std::vector<FilterDescriptors> filter_descriptors_;
};

#endif
