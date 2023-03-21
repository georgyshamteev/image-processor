add_executable(
        image_processor
        image_processor.cpp
        tmatrix.h
        command_parser.cpp
        command_parser.h
        bmp.cpp
        bmp.h
        test.cpp filters.cpp filters.h filter_pipeline.cpp filter_pipeline.h)

add_catch(
        unit_test
        image_processor.cpp
        tmatrix.h
        command_parser.cpp
        command_parser.h
        bmp.cpp
        bmp.h
        test.cpp
)
