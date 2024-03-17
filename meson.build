project('quickerSDLPoP','c','cpp',
  version: '1.0.0',
  license: 'GPL-3.0-only',
  default_options : ['cpp_std=c++20', 'default_library=shared', 'buildtype=release'],
  subproject_dir : 'extern'
)

# Loading dependencies
subdir('source')

# Do not build any targets if this is a subproject
if meson.is_subproject() == false

# Common application flags
commonCompileArgs = [ '-Wfatal-errors', '-Wall', '-Werror' ]

# Grabbing jaffarCommon dependency

jaffarCommonSubproject = subproject('jaffarCommon')
jaffarCommonDependency = jaffarCommonSubproject.get_variable('jaffarCommonDependency')

# Building playback tool
  if get_option('buildPlayer') == true

    # First, building sdlpop as library only for display
    
    SDLPoPLib = library('SDLPoPLib',
      cpp_args            : [ commonCompileArgs, '-DNCURSES' ],
      dependencies        : [ jaffarCommonDependency, SDLPoPDependency, toolDependency],
     )
  
    quickerSDLPoPPlayer = executable('quickerSDLPoPPlayer',
      'source/player.cpp',
      cpp_args            : [ commonCompileArgs, '-DNCURSES' ],
      dependencies        : [ jaffarCommonDependency, quickerSDLPoPDependency, toolDependency],
      link_with           : [ SDLPoPLib ],
      link_args           : [ '-lncurses' ]
    )

    SDLPoPPlayer = executable('SDLPoPPlayer',
    'source/player.cpp',
      cpp_args            : [ commonCompileArgs, '-DNCURSES' ],
      dependencies        : [ jaffarCommonDependency, SDLPoPDependency, toolDependency],
      link_args           : [ '-lncurses' ]
    )
    
  endif

  # Building tester tool for QuickerSDLPoP

  quickerSDLPoPTester = executable('quickerSDLPoPTester',
    'source/tester.cpp',
    cpp_args            : [ commonCompileArgs, '-Werror' ],
    dependencies        : [ jaffarCommonDependency, quickerSDLPoPDependency, toolDependency ]
  )

  # Building tester tool for the original SDLPoP

  if get_option('buildSDLPoP') == true
  SDLPoPTester = executable('SDLPoPTester',
    'source/tester.cpp',
    cpp_args            : [ commonCompileArgs ],
    dependencies        : [ jaffarCommonDependency, SDLPoPDependency, toolDependency ]
  )
  endif

  # Building tests
  if get_option('buildSDLPoP') == true
    subdir('tests')
  endif
  
endif # If not subproject
