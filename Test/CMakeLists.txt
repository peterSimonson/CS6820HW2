project(${TARGET_NAME})

add_subdirectory(googletest)
add_subdirectory(LL1LibTest)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)