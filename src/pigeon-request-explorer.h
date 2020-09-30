#include <glib-object.h>
#include <gtk/gtk.h>

#define PIGEON_TYPE_REQUEST_EXPLORER (pigeon_request_explorer_get_type())
G_DECLARE_FINAL_TYPE(
	PigeonRequestExplorer, pigeon_request_explorer, PIGEON, REQUEST_EXPLORER, GtkBox)

G_BEGIN_DECLS

PigeonRequestExplorer *pigeon_request_explorer_new() G_GNUC_WARN_UNUSED_RESULT;

G_END_DECLS
