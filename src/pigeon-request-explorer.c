#include "config.h"

#include <glib-object.h>
#include <glib.h>
#include <gtk/gtk.h>

#include "pigeon-request-explorer.h"

struct _PigeonRequestExplorer
{
	GtkBox parent_instance;
};

typedef struct PigeonRequestExplorerPrivate
{
	GtkListView *request_tree;
} PigeonRequestExplorerPrivate;

G_DEFINE_TYPE_WITH_PRIVATE(PigeonRequestExplorer, pigeon_request_explorer, GTK_TYPE_BOX)

static void
pigeon_request_explorer_class_init(PigeonRequestExplorerClass *klass)
{
	GtkWidgetClass *wid_class = GTK_WIDGET_CLASS(klass);

	gtk_widget_class_set_template_from_resource(
		wid_class, "/io/partin/tristan/Pigeon/ui/pigeon-request-explorer.ui");
	gtk_widget_class_bind_template_child_private(wid_class, PigeonRequestExplorer, request_tree);
}

static void
pigeon_request_explorer_init(PigeonRequestExplorer *self)
{
	gtk_widget_init_template(GTK_WIDGET(self));
}

PigeonRequestExplorer *
pigeon_request_explorer_new()
{
	return g_object_new(PIGEON_TYPE_REQUEST_EXPLORER, NULL);
}
