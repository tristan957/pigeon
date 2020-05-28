#include <glib-object.h>
#include <gtk/gtk.h>

#include "pigeon-application.h"

#define PIGEON_TYPE_APPLICATION_WINDOW (pigeon_application_window_get_type())
G_DECLARE_FINAL_TYPE(PigeonApplicationWindow, pigeon_application_window, PIGEON, APPLICATION_WINDOW,
	GtkApplicationWindow)

G_BEGIN_DECLS

PigeonApplicationWindow *pigeon_application_window_new(PigeonApplication *app);

G_END_DECLS
