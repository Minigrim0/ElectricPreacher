project(
  'ElectricPreacher',
  'cpp',
  default_options: 'default_library=static')

dependencies = []

sdl2_dep = dependency('sdl2')
sdl2_ttf_dep = dependency('sdl2_ttf')
sdl2_image_dep = dependency('sdl2_image')
nlohmann_json_dep = dependency('nlohmann_json')
tinyxml2_dep = dependency('tinyxml2')

dependencies += sdl2_dep
dependencies += sdl2_ttf_dep
dependencies += sdl2_image_dep
dependencies += nlohmann_json_dep
dependencies += tinyxml2_dep

# subdirs
subdir('src/game')
subdir('src/map')
subdir('src/player')
subdir('src/screen')
subdir('src/UI')
subdir('src/utils')

# Actual code
source_files = files('main.cpp') + game_sources + map_sources + player_sources + screen_sources + ui_sources + utils_sources


executable(
  'ElectricPreacher', source_files,
  include_directories: ['includes'],
  win_subsystem: 'windows',
  dependencies: dependencies)