#pragma once

#include <glib-object.h>
#include <gtk/gtk.h>

#define PIGEON_TYPE_PAGE (pigeon_page_get_type())
G_DECLARE_FINAL_TYPE(PigeonPage, pigeon_page, PIGEON, PAGE, GtkGrid)

G_BEGIN_DECLS

PigeonPage *pigeon_page_new() G_GNUC_WARN_UNUSED_RESULT;

G_END_DECLS
