#pragma once

#include <glib-object.h>
#include <gtk/gtk.h>

#define PIGEON_TYPE_APPLICATION (pigeon_application_get_type())
G_DECLARE_FINAL_TYPE(PigeonApplication, pigeon_application, PIGEON, APPLICATION, GtkApplication)

G_BEGIN_DECLS

PigeonApplication *pigeon_application_new(const char *app_id) G_GNUC_WARN_UNUSED_RESULT;

G_END_DECLS
