add_executable(PathBanner
        WIN32
        main.cpp
        BannerWidget.cpp
        BannerWidget.h # 包含 Q_OBJECT 宏，需要 moc 处理
)

target_link_libraries(PathBanner
        PRIVATE
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
)
