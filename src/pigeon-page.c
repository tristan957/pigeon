#include "config.h"

#include <curl/curl.h>
#include <glib-object.h>
#include <gtk/gtk.h>

#include "pigeon-page.h"

struct _PigeonPage
{
	GtkGrid parent_instance;

	CURL *handle;
};

typedef struct PigeonPagePrivate
{
} PigeonPagePrivate;

G_DEFINE_TYPE(PigeonPage, pigeon_page, GTK_TYPE_GRID)

static void
pigeon_page_finalize(GObject *obj)
{
	PigeonPage *self = PIGEON_PAGE(obj);

	curl_easy_cleanup(self->handle);

	G_OBJECT_CLASS(pigeon_page_parent_class)->finalize(obj);
}

static void
pigeon_page_class_init(PigeonPageClass *klass)
{
	GObjectClass *obj_class	  = G_OBJECT_CLASS(klass);
	GtkWidgetClass *wid_class = GTK_WIDGET_CLASS(klass);

	obj_class->finalize = pigeon_page_finalize;

	gtk_widget_class_set_template_from_resource(
		wid_class, "/io/partin/tristan/Pigeon/ui/pigeon-page.ui");
}

static void
pigeon_page_init(PigeonPage *self)
{
	gtk_widget_init_template(GTK_WIDGET(self));

	self->handle = curl_easy_init();
}

PigeonPage *
pigeon_page_new()
{
	return g_object_new(PIGEON_TYPE_PAGE, NULL);
}
