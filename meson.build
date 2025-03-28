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
    'include/cmb.h',
    'include/error.h',
    'include/list.h',
    'include/matrix.h',
    'include/sort.h',
    'include/vector.h',
)

lib_klib = library(
    'klib',
    klib_sources,
    include_directories: inc,
    install: true,
    install_dir: get_option('includedir'),
)

install_headers(inc_files, subdir: get_option('includedir') / 'klib')

lib_klib