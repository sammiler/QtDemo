add_executable(CustomSelectionHighlightDemo
        WIN32
        main.cpp
        mainwindow.cpp
        mainwindow.h
        custom_item.cpp
        custom_item.h # Use WIN32 for a standard Windows GUI application
)

# Link Qt libraries to the executable
target_link_libraries(CustomSelectionHighlightDemo
        PRIVATE
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
)

# Optional: Add compiler flags for UTF-8 source files if needed
# target_compile_options(${PROJECT_NAME} PRIVATE
#     $<$<CXX_COMPILER_ID:MSVC>:/utf-8>
#     $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-finput-charset=UTF-8>
# )