add_executable(
        image_processor
        image_processor.cpp
        tmatrix.h
        command_parser.cpp
        command_parser.h
        bmp.cpp
        bmp.h
        test.cpp filters.cpp filters.h filter_producing.cpp filter_producing.h pipeline.cpp pipeline.h)

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
