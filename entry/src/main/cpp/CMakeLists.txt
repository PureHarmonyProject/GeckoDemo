cmake_minimum_required(VERSION 3.4.1)
project(gecko_napi)

# Set OpenHarmony NDK path
set(OHOS_NDK_HOME $ENV{OHOS_NDK_HOME})
if(NOT OHOS_NDK_HOME)
    set(OHOS_NDK_HOME ${CMAKE_CURRENT_SOURCE_DIR}/../../../prebuilts/clang/ohos/linux-x86_64/llvm)
endif()

# Include directories
include_directories(
    ${OHOS_NDK_HOME}/include
    ${CMAKE_CURRENT_SOURCE_DIR}
    # Add Gecko headers (adjust path as needed)
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../../gecko_engine/dist/include
)

# Add our NAPI library
add_library(gecko_napi SHARED
    gecko_napi.cpp
    gecko_engine.cpp
)

# Link required libraries
target_link_libraries(gecko_napi PUBLIC
    hilog_shared
    ace_napi
    # Link against pre-built Gecko libraries
    ${CMAKE_CURRENT_SOURCE_DIR}/../../libs/arm64-v8a/libxul.so
    ${CMAKE_CURRENT_SOURCE_DIR}/../../libs/arm64-v8a/libmozglue.so
)

# Install to libs directory
install(TARGETS gecko_napi LIBRARY DESTINATION libs/${OHOS_ARCH})