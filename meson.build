project(
  'pigeon',
  'c',
  version: '0.1.0',
  meson_version: '>= 0.50.0',
  default_options: [
    'warning_level=2',
    'c_std=gnu18',
    'buildtype=debugoptimized',
  ],
)

cc = meson.get_compiler('c')
i18n = import('i18n')
gnome = import('gnome')

libgio_dep = dependency('gio-2.0', version: '>= 2.64.3', required: true, fallback: ['gio', 'libgio_dep'])
libgtk_dep = dependency('gtk4', version: '>= 3.99.0', required: true, fallback: ['gtk', 'libgtk_dep'])
gtksource_dep = dependency('gtksourceview-4', version: '>= 4.6.2', fallback: ['gtksourceview', 'gtksource_dep'])
libcurl_dep = dependency('libcurl', version: '>= 7.69.1', required: true)

subdir('data')
subdir('src')
subdir('po')

meson.add_install_script('meson_post_install.sh')
