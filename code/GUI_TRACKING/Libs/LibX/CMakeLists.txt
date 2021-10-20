cmake_minimum_required(VERSION 3.15)
project(LibX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(QT_VERSION 5)
set(REQUIRED_LIBS Core Gui Widgets PrintSupport Positioning Qml Quick)
set(REQUIRED_LIBS_QUALIFIED Qt5::Core Qt5::Gui Qt5::Widgets Qt5::PrintSupport Qt5::Positioning Qt5::Qml Qt5::Quick)
set(CMAKE_PREFIX_PATH "C:/Qt/5.15.2/mingw81_64/lib/cmake")
#qt5_add_resources(qml_QRC src/qml.qrc)
# lots of warnings and all warnings as errors
# add_compile_options(-Wall -Wextra -pedantic-errors -Werror -Wconversion -Wsign-conversion)

file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.qrc" "src/*.qml" "includes/*.h" "includes/*.ui")

add_library(${PROJECT_NAME} STATIC ${SOURCES})
add_library(Libs::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
                           PUBLIC
                           $<INSTALL_INTERFACE:includes>
                           $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/includes>
                           ${CMAKE_CURRENT_SOURCE_DIR})

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)




find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)

target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})