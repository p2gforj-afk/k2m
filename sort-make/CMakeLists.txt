cmake_minimum_required(VERSION 3.10)

project(sort_project C)

# FLAG
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")

# Dossiers de sortie
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Includes
include_directories(${CMAKE_SOURCE_DIR}/include)


# Bibliothèque statique

add_library(system_utils STATIC
    src/system_utils/system_utils.c
)

# Bibliothèque dynamique

add_library(sort SHARED
    src/sort/sort.c
    src/sort/demo.c
)

# Position Independent Code (équivalent à -fPIC)
set_target_properties(sort PROPERTIES POSITION_INDEPENDENT_CODE ON)


# bin/sort

add_executable(sort_exec
    apps/Sort.c
)

# Link avec les bibliothèques
target_link_libraries(sort_exec
    sort
    system_utils
)

# Nom de sortie "sort" au lieu de "sort_exec"
set_target_properties(sort_exec PROPERTIES OUTPUT_NAME sort)

# Doxygen
find_package(Doxygen)
if (DOXYGEN_FOUND)
    add_custom_target(doc
        COMMAND ${DOXYGEN_EXECUTABLE} Doxyfile
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    )
endif()
