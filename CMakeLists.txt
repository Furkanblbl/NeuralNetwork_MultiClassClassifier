# Set cmake version
cmake_minimum_required(VERSION 3.16)
# Define project name as NeuralNetwork
project(NeuralNetwork LANGUAGES CXX)

# Some CMake configuration
set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set current QT directory.
# todo: make generic
set(CMAKE_PREFIX_PATH "/home/furkan/Qt/6.5.3/gcc_64/lib/cmake")

# Find nececcery package
find_package(Qt6 REQUIRED COMPONENTS Quick)

# Project custom include directories
include_directories(include)

# Declare header files relative path
set(HEADERS
    include/CoordinateSystem.h
    include/NeuralNetwork.h
)

# Declare source files relative path
set(SOURCES
    src/main.cpp
    src/CoordinateSystem.cpp
    src/NeuralNetwork.cpp
)

# Add header and source files to qt executable process
qt_add_executable(NeuralNetworkApp
    ${SOURCES}
    ${HEADERS}
)

# Set QML paths for QT
set(QML_IMPORT_PATH ${CMAKE_BINARY_DIR} CACHE STRING "" FORCE)
set(QML_IMPORT_PATH ${CMAKE_SOURCE_DIR} ${QML_IMPORT_PATH})

# Declare QML files and modules path
qt_add_qml_module(NeuralNetworkApp
    URI NeuralNetwork
    VERSION 1.0
    QML_FILES
        qml/MainWindow.qml
        qml/components/ScreenTools.qml
        qml/widgets/CustomButton.qml
        qml/widgets/CustomLabel.qml
        qml/widgets/CustomComboBox.qml
)

qt_add_qml_module(createdModule
    URI ScreenTools
    VERSION 1.0
    QML_FILES
        qml/components/ScreenTools.qml
        qml/widgets/CustomButton.qml
        qml/widgets/CustomLabel.qml
        qml/widgets/CustomComboBox.qml
    RESOURCE_PREFIX "/qmlmodules"
)

# Compile with
target_link_libraries(NeuralNetworkApp
    PRIVATE Qt6::Quick
)

# Copy QML files and modules to work directory
add_custom_command(TARGET NeuralNetworkApp POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/qml
        ${CMAKE_CURRENT_BINARY_DIR}/qml
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/qmlmodules
        ${CMAKE_CURRENT_BINARY_DIR}/qmlmodules
)
