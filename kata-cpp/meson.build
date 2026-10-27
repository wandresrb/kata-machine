project(
  'kata-cpp',
  'cpp',
  version: '0.1.0',
  meson_version: '>=1.1.0',
  default_options: [
    'cpp_std=c++23',
    'warning_level=3',
    'buildtype=debug',
    'b_sanitize=address,undefined',
    'b_lundef=false',  # required by clang when using sanitizers
  ],
)

fs = import('fs')

day = get_option('day')
katas = get_option('katas')

# Make every UBSan finding fatal so a test cannot "pass" with UB in it.
add_project_arguments(
  meson.get_compiler('cpp').get_supported_arguments('-fno-sanitize-recover=all'),
  language: 'cpp',
)

if katas.length() > 0
  if day == ''
    error('-Dday=<dayN> is required when -Dkatas is not empty')
  endif
  if not fs.is_dir('src' / day)
    error('src/@0@ does not exist (run `just generate` first)'.format(day))
  endif
endif

inc = include_directories('include', 'tests', 'src' / day)

sanitizer_env = environment({
  'ASAN_OPTIONS': 'abort_on_error=0:detect_leaks=1:halt_on_error=1',
  'UBSAN_OPTIONS': 'print_stacktrace=1:halt_on_error=1',
})

foreach kata : katas
  src = 'tests' / kata + '.cpp'
  if not fs.is_file(src)
    error('Unknown kata "@0@": @1@ not found'.format(kata, src))
  endif
  if not fs.is_file('src' / day / kata + '.hpp')
    error('src/@0@/@1@.hpp not found'.format(day, kata))
  endif
  exe = executable(kata, src, include_directories: inc)
  test(kata, exe, env: sanitizer_env, timeout: 10)
endforeach
