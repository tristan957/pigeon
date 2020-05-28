#include <glib-object.h>
#include <gtk/gtk.h>

#include "pigeon-application-window.h"
#include "pigeon-application.h"

struct _PigeonApplicationWindow
{
	GtkApplicationWindow parent_object;
};

typedef struct PigeonApplicationWindowPrivate
{
} PigeonApplicationWindowPrivate;

G_DEFINE_TYPE_WITH_PRIVATE(
	PigeonApplicationWindow, pigeon_application_window, GTK_TYPE_APPLICATION_WINDOW)

static void
pigeon_application_window_class_init(PigeonApplicationWindowClass *klass)
{
	GtkWidgetClass *wid_class = GTK_WIDGET_CLASS(klass);

	gtk_widget_class_set_template_from_resource(
		wid_class, "/io/partin/tristan/Pigeon/ui/pigeon-application-window.ui");
}

static void
pigeon_application_window_init(PigeonApplicationWindow *self)
{
	gtk_widget_init_template(GTK_WIDGET(self));
}

PigeonApplicationWindow *
pigeon_application_window_new(PigeonApplication *app)
{
	return g_object_new(PIGEON_TYPE_APPLICATION_WINDOW, "application", app, NULL);
}
