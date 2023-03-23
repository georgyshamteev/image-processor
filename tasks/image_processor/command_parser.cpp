#include "command_parser.h"

std::string_view Parser::GetOutputFileName() const {
    return output_file_name_;
}
std::string_view Parser::GetInputFileName() const {
    return input_file_name_;
}
const std::vector<FilterDescriptors>& Parser::GetFilterDescriptors() const {
    return filter_descriptors_;
}

bool Parser::Parse(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0]
                  << " input_file output_file [-filter1 param1_1 param1_2 ...] [-filter2 param2_1 param2_2 ...] ..."
                  << std::endl;
        return false;
    }
    input_file_name_ = argv[1];
    output_file_name_ = argv[2];

    for (int i = 3; i < argc; ++i) {
        std::string_view arg = argv[i];
        if (arg.empty()) {
            continue;
        }

        if (arg[0] == '-') {
            std::string_view filter_name = arg.substr(1);
            if (filter_name.empty()) {
                std::cerr << "Error: empty filter name" << std::endl;
                return false;
            }

            FilterDescriptors filter_desc = {filter_name, {}};

            int j = i + 1;
            while (j < argc && argv[j][0] != '-') {
                filter_desc.parameters.emplace_back(argv[j]);
                j++;
            }
            filter_descriptors_.push_back(filter_desc);
            //            i = j - 1;
        }
    }

    return true;
}
