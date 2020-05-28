#include "config.h"

#include <stdlib.h>

#include <curl/curl.h>
#include <glib-object.h>

#include "pigeon-application-window.h"
#include "pigeon-application.h"
#include "pigeon-resources.h"

struct _PigeonApplication
{
	GtkApplication parent_object;
};

typedef struct PigeonApplicationPrivate
{
	PigeonApplicationWindow *app_window;
} PigeonApplicationPrivate;

G_DEFINE_TYPE_WITH_PRIVATE(PigeonApplication, pigeon_application, GTK_TYPE_APPLICATION)

static void
pigeon_application_activate(GApplication *app)
{
	PigeonApplication *self		   = PIGEON_APPLICATION(app);
	PigeonApplicationPrivate *priv = pigeon_application_get_instance_private(self);

	if (priv->app_window == NULL) {
#ifndef _WIN32
		const int code = curl_global_init(CURL_GLOBAL_SSL);
#else
		const int code = curl_global_init(CURL_GLOBAL_SSL | CURL_GLOBAL_WIN32);
#endif
		if (code != CURLE_OK) {
			g_critical("Unable to initialize libcurl. Try to start the application again.");
			exit(1);
		}

		priv->app_window = pigeon_application_window_new(self);
	}

	gtk_window_present(GTK_WINDOW(priv->app_window));
}

static void
pigeon_application_startup(GApplication *app)
{
	g_resources_register(pigeon_get_resource());
	g_application_set_resource_base_path(app, "/io/partin/tristan/Pigeon");

	G_APPLICATION_CLASS(pigeon_application_parent_class)->startup(app);
}

static void
pigeon_application_about(
	G_GNUC_UNUSED GSimpleAction *action, G_GNUC_UNUSED GVariant *param, gpointer data)
{
	static const char *authors[] = {"Tristan Partin"};

	PigeonApplication *self		   = PIGEON_APPLICATION(data);
	PigeonApplicationPrivate *priv = pigeon_application_get_instance_private(self);

	gtk_show_about_dialog(GTK_WINDOW(priv->app_window), "program-name", PROJECT_NAME, "version",
		PROJECT_VERSION, "license-type", PROJECT_LICENSE, "website", PROJECT_WEBSITE,
		"website-label", PROJECT_WEBSITE_LABEL, "authors", authors, "logo-icon-name", "trophy-gold",
		NULL);
}

// clang-format off
static const GActionEntry app_entries[] = {
	{
		.name	  = "about",
		.activate = pigeon_application_about
	},
};
// clang-format on

static void
pigeon_application_class_init(PigeonApplicationClass *klass)
{
	GApplicationClass *app_class = G_APPLICATION_CLASS(klass);

	app_class->activate = pigeon_application_activate;
	app_class->startup	= pigeon_application_startup;
}

static void
pigeon_application_init(PigeonApplication *self)
{
	g_action_map_add_action_entries(
		G_ACTION_MAP(self), app_entries, G_N_ELEMENTS(app_entries), self);
}

PigeonApplication *
pigeon_application_new(const char *app_id)
{
	return g_object_new(PIGEON_TYPE_APPLICATION, "application-id", app_id, NULL);
}
