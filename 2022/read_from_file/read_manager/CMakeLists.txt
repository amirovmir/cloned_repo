project (read_manager)

# Toolkit for working with NK parser.
include (platform/nk)

# Setting compilation flags.
project_header_default ("STANDARD_GNU_11:YES" "STRICT_WARNINGS:NO")
add_compile_options(-fexceptions)

add_executable (
        ReadManager
        "src/read_manager.cpp"
        "src/main.cpp"
        ${EDL_FILES})

add_dependencies (ReadManager read_from_file_read_manager)
target_link_libraries (ReadManager ${${PROJECT_NAME}_LIBS} ${vfs_CLIENT_LIB})

# We do not need default VFS entity here, which comes from ${vfs_CLIENT_LIB}.
set_target_properties (ReadManager PROPERTIES ${vfs_ENTITY}_REPLACEMENT "")