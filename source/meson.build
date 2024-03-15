# Getting core configurations
if get_option('buildSDLPoP') == true
subdir('SDLPoP')
endif

subdir('quickerSDLPoP')

# Tool Configuration

 toolDependency = declare_dependency(
  include_directories : include_directories(['.']),
  dependencies:  [ dependency('sdl2'), dependency('SDL2_image') ]
 )
