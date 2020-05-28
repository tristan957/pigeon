pigeon_resources = gnome.compile_resources(
  'pigeon-resources',
  'pigeon-resources.gresource.xml',
  c_name: 'pigeon'
)

install_data('io.partin.tristan.Pigeon.gschema.xml',
  install_dir: join_paths(get_option('datadir'), 'glib-2.0/schemas')
)

desktop_file = i18n.merge_file(
  input: 'io.partin.tristan.Pigeon.desktop.in',
  output: 'io.partin.tristan.Pigeon.desktop',
  type: 'desktop',
  po_dir: '../po',
  install: true,
  install_dir: join_paths(get_option('datadir'), 'applications')
)

desktop_utils = find_program('desktop-file-validate', required: false)
if desktop_utils.found()
  test('Validate desktop file', desktop_utils,
    args: [desktop_file]
  )
endif

appstream_file = i18n.merge_file(
  input: 'io.partin.tristan.Pigeon.appdata.xml.in',
  output: 'io.partin.tristan.Pigeon.appdata.xml',
  po_dir: '../po',
  install: true,
  install_dir: join_paths(get_option('datadir'), 'appdata')
)

appstream_util = find_program('appstream-util', required: false)
if appstream_util.found()
  test('Validate appstream file', appstream_util,
    args: ['validate', appstream_file]
  )
endif

compile_schemas = find_program('glib-compile-schemas', required: false)
if compile_schemas.found()
  test('Validate schema file', compile_schemas,
    args: ['--strict', '--dry-run', meson.current_source_dir()]
  )
endif
