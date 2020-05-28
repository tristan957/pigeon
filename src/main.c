#include "config.h"

#include <gio/gio.h>
#include <glib/gi18n.h>

#include "pigeon-application.h"

int
main(int argc, char *argv[])
{
	bindtextdomain(GETTEXT_PACKAGE, LOCALEDIR);
	bind_textdomain_codeset(GETTEXT_PACKAGE, "UTF-8");
	textdomain(GETTEXT_PACKAGE);

	g_autoptr(PigeonApplication) app = pigeon_application_new("io.partin.tristan.Pigeon");
	g_set_prgname(PROJECT_NAME);
	g_set_application_name(_(PROJECT_NAME));

	return g_application_run(G_APPLICATION(app), argc, argv);
}
