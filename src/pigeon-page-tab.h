#include <glib-object.h>
#include <gtk/gtk.h>

#define PIGEON_TYPE_PAGE_TAB (pigeon_page_tab_get_type())
G_DECLARE_FINAL_TYPE(PigeonPageTab, pigeon_page_tab, PIGEON, PAGE_TAB, GtkBox)

G_BEGIN_DECLS

PigeonPageTab *pigeon_page_tab_new(const char *label) G_GNUC_WARN_UNUSED_RESULT;

G_END_DECLS
