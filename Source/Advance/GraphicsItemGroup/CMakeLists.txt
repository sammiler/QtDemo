

# Find Qt5 components


# Add the executable
add_executable(GraphicsItemGroup
        WIN32
        main.cpp
        mainwindow.cpp
        mainwindow.h # Use WIN32 for a standard Windows GUI application
)

# Link Qt libraries to the executable
target_link_libraries(GraphicsItemGroup
        PRIVATE
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
)

# Optional: Add compiler flags for UTF-8 source files if needed
# target_compile_options(GraphicsItemGroup PRIVATE
#     $<$<CXX_COMPILER_ID:MSVC>:/utf-8>
#     $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-finput-charset=UTF-8>
# )