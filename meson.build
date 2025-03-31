project('klib', 'c', version: '0.0.1', default_options: ['warning_level=3'])
# this library explicitly defines all files

inc = include_directories('include')

klib_sources = files(
    'src/combinations/cmb.c',
'src/exeption/error.c',
    'src/list/list.c',
    'src/math/matrix.c',
    'src/math/vector.c',
    'src/sort/sort.c',
)

inc_files = files(
    'include/klib/cmb.h',
    'include/klib/error.h',
    'include/klib/list.h',
    'include/klib/matrix.h',
    'include/klib/sort.h',
    'include/klib/vector.h',
)

lib_klib = shared_library(
    'klib',
    klib_sources,
    include_directories: inc,
    install: true,
)

install_headers(inc_files, subdir: 'klib')

klib_dep = declare_dependency(include_directories: inc, link_with: lib_klib)