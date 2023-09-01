# CMake version.
cmake_minimum_required(VERSION "3.26.3")

# Modules.
include("FetchContent")

# Project.
project("test_sqlitecpp")

# Find libs.
find_package("fmt" REQUIRED)
find_package("SQLite3" REQUIRED)

# [sqlitecpp] - download.
FetchContent_Populate("package_sqlitecpp" URL "https://github.com/SRombauts/SQLiteCpp/archive/master.zip")

# [sqlitecpp] - make library.
add_library(sqlitecpp STATIC
	"${package_sqlitecpp_SOURCE_DIR}/src/Backup.cpp"
	"${package_sqlitecpp_SOURCE_DIR}/src/Column.cpp"
	"${package_sqlitecpp_SOURCE_DIR}/src/Database.cpp"
	"${package_sqlitecpp_SOURCE_DIR}/src/Exception.cpp"
	"${package_sqlitecpp_SOURCE_DIR}/src/Savepoint.cpp"
	"${package_sqlitecpp_SOURCE_DIR}/src/Statement.cpp"
	"${package_sqlitecpp_SOURCE_DIR}/src/Transaction.cpp"
)

# [sqlitecpp] - add includes.
target_include_directories(sqlitecpp PUBLIC
	"${package_sqlitecpp_SOURCE_DIR}/include"
)

# [sqlitecpp] - linkage.
target_link_libraries(sqlitecpp PRIVATE SQLite3)

# Find sources.
file(GLOB_RECURSE src "src/*")

# [Target] - Make.
add_executable(${PROJECT_NAME} ${src})

# [Target] - Properties.
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 23)
set_property(TARGET ${PROJECT_NAME} PROPERTY CMAKE_CXX_STANDARD_REQUIRED ON)
set_property(TARGET ${PROJECT_NAME} PROPERTY CMAKE_CXX_EXTENSIONS OFF)

# [Target] - Linking.
target_link_libraries(${PROJECT_NAME} PRIVATE
	fmt::fmt
	sqlitecpp
)

# [Clang] - Enable LTO optimization.
if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
	set(LLVM_ENABLE_LTO "Thin")
endif()

# [MSVC] - Enable big objects support.
if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	target_compile_options(${PROJECT_NAME} PRIVATE "/bigobj")
endif()

# [Windows] - Set minimal api version.
if(WIN32)
	target_compile_definitions(${PROJECT_NAME} PRIVATE _WIN32_WINNT=0x0601)
endif()

# Set msvc runtime library.
set_property(TARGET ${PROJECT_NAME} PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
