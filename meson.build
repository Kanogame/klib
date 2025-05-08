project('klib', 'c', version: '0.0.1', default_options: ['warning_level=3'])
# this library explicitly defines all files

inc = include_directories('include')

klib_sources = files(
    'src/combinations/cmb.c',
    'src/exeption/error.c',
    'src/heap/binary_heap.c',
    'src/list/list.c',
    'src/math/approx.c',
    'src/math/matrix.c',
    'src/math/vector.c',
    'src/randutils/randstring.c',
    'src/sort/radix.c',
    'src/sort/sort.c',

)

inc_files = files(
    'include/klib/approx.h',
    'include/klib/binary_heap.h',
    'include/klib/cmb.h',
    'include/klib/error.h',
    'include/klib/list.h',
    'include/klib/matrix.h',
    'include/klib/randutils.h',
    'include/klib/sort.h',
    'include/klib/vector.h',
)

# written in RV64 asm
if false
    klib_sources += files(
        'src/asm/crypt/xorshift.s',
        'src/asm/string/size.s',
    )

    inc_files += files(
        'include/klib/asm/crypt.h',
        'include/klib/asm/string.h',
    )
endif

lib_klib = static_library(
    'klib',
    klib_sources,
    include_directories: inc,
    install: true,
)

install_headers(inc_files, subdir: 'klib')

klib_dep = declare_dependency(include_directories: inc, link_with: lib_klib)