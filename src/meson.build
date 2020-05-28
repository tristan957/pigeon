config_h = configuration_data({
  'project_name': 'Pigeon',
  'project_version': meson.project_version(),
  'project_license': 'GTK_LICENSE_GPL_3_0',
  'project_website': 'https://git.sr.ht/~tristan957/pigeon',
  'project_website_label': 'Repository',
  'gettext_package': meson.project_name(),
  'localedir': join_paths(get_option('prefix'), get_option('localedir')),
  'libdir': join_paths(get_option('prefix'), get_option('libdir')),
})

configure_file(
    input: 'config.h.in',
    output: 'config.h',
    configuration: config_h,
)

pigeon_sources = [
  'main.c',
  'pigeon-application.c',
  'pigeon-application-window.c',
]

pigeon_deps = [
  libgio_dep,
  libgtk_dep,
  libcurl_dep,
]

pigeon_c_args = [
  '-DG_LOG_DOMAIN="Pigeon"',
]

if get_option('buildtype') == 'release'
  pigeon_c_args += [
    '-DG_DISABLE_ASSERT',
    '-DG_DISABLE_CHECKS',
    '-DG_DISABLE_CAST_CHECKS',
  ]
elif get_option('buildtype').startswith('debug')
  pigeon_c_args += [
    '-DG_ENABLE_DEBUG',
  ]
endif

executable(
  'pigeon',
  pigeon_sources + pigeon_resources,
  dependencies: pigeon_deps,
  c_args: pigeon_c_args,
  gui_app: true,
  install: true,
)
