#include "config.h"

#include <glib-object.h>
#include <gtk/gtk.h>
#include <math.h>

#include "pigeon-application-window.h"
#include "pigeon-application.h"
#include "pigeon-page-tab.h"
#include "pigeon-page.h"

struct _PigeonApplicationWindow
{
	GtkApplicationWindow parent_object;

	unsigned int num_untitled_pages;
};

typedef struct PigeonApplicationWindowPrivate
{
	GtkNotebook *tab_notebook;
} PigeonApplicationWindowPrivate;

G_DEFINE_TYPE_WITH_PRIVATE(
	PigeonApplicationWindow, pigeon_application_window, GTK_TYPE_APPLICATION_WINDOW)

static void
win_shortcuts(
	GtkWidget *widget, G_GNUC_UNUSED const char *action_name, G_GNUC_UNUSED GVariant *parameter)
{
	PigeonApplicationWindow *self = PIGEON_APPLICATION_WINDOW(widget);

	g_autoptr(GtkBuilder) builder
		= gtk_builder_new_from_resource("/io/partin/tristan/Pigeon/ui/pigeon-shortcuts-window.ui");
	GtkShortcutsWindow *shortcuts_window
		= GTK_SHORTCUTS_WINDOW(gtk_builder_get_object(builder, "shortcuts_window"));
	gtk_window_set_transient_for(GTK_WINDOW(shortcuts_window), GTK_WINDOW(self));

	gtk_window_present(GTK_WINDOW(shortcuts_window));
}

static void
win_save_tab(G_GNUC_UNUSED GtkWidget *widget, G_GNUC_UNUSED const char *action_name,
	G_GNUC_UNUSED GVariant *parameter)
{
	g_print("save\n");
}

static void
win_save_tab_as(G_GNUC_UNUSED GtkWidget *widget, G_GNUC_UNUSED const char *action_name,
	G_GNUC_UNUSED GVariant *parameter)
{
	g_print("save as\n");
}

static void
win_close_tab(G_GNUC_UNUSED GtkWidget *widget, G_GNUC_UNUSED const char *action_name,
	G_GNUC_UNUSED GVariant *parameter)
{
	PigeonApplicationWindow *self		 = PIGEON_APPLICATION_WINDOW(widget);
	PigeonApplicationWindowPrivate *priv = pigeon_application_window_get_instance_private(self);

	const int page_num = gtk_notebook_get_current_page(priv->tab_notebook);
	gtk_notebook_remove_page(priv->tab_notebook, page_num);
}

static void
win_shift_left(G_GNUC_UNUSED GtkWidget *widget, G_GNUC_UNUSED const char *action_name,
	G_GNUC_UNUSED GVariant *parameter)
{
	PigeonApplicationWindow *self		 = PIGEON_APPLICATION_WINDOW(widget);
	PigeonApplicationWindowPrivate *priv = pigeon_application_window_get_instance_private(self);

	const int page_num	  = gtk_notebook_get_current_page(priv->tab_notebook);
	const int total_pages = gtk_notebook_get_n_pages(priv->tab_notebook);
	if (total_pages > 0 && page_num > 0)
		gtk_notebook_set_current_page(priv->tab_notebook, page_num - 1);
}

static void
win_shift_right(G_GNUC_UNUSED GtkWidget *widget, G_GNUC_UNUSED const char *action_name,
	G_GNUC_UNUSED GVariant *parameter)
{
	PigeonApplicationWindow *self		 = PIGEON_APPLICATION_WINDOW(widget);
	PigeonApplicationWindowPrivate *priv = pigeon_application_window_get_instance_private(self);

	const int page_num	  = gtk_notebook_get_current_page(priv->tab_notebook);
	const int total_pages = gtk_notebook_get_n_pages(priv->tab_notebook);
	if (total_pages > 0 && page_num < total_pages - 1)
		gtk_notebook_set_current_page(priv->tab_notebook, page_num + 1);
}

static void
new_request_cb(G_GNUC_UNUSED GtkButton *button, gpointer user_data)
{
	PigeonApplicationWindow *self		 = PIGEON_APPLICATION_WINDOW(user_data);
	PigeonApplicationWindowPrivate *priv = pigeon_application_window_get_instance_private(self);

	GString *label = g_string_new("Untitled ");
	g_string_append_printf(label, "%u", self->num_untitled_pages);
	PigeonPage *page		= pigeon_page_new();
	PigeonPageTab *page_tab = pigeon_page_tab_new(label->str);
	gtk_notebook_append_page(priv->tab_notebook, GTK_WIDGET(page), GTK_WIDGET(page_tab));
	self->num_untitled_pages++;
}

static void
pigeon_application_window_class_init(PigeonApplicationWindowClass *klass)
{
	GtkWidgetClass *wid_class = GTK_WIDGET_CLASS(klass);

	gtk_widget_class_set_template_from_resource(
		wid_class, "/io/partin/tristan/Pigeon/ui/pigeon-application-window.ui");
	gtk_widget_class_bind_template_child_private(wid_class, PigeonApplicationWindow, tab_notebook);
	gtk_widget_class_bind_template_callback(wid_class, new_request_cb);

	gtk_widget_class_install_action(wid_class, "win.shift-left", NULL, win_shift_left);
	gtk_widget_class_install_action(wid_class, "win.shift-right", NULL, win_shift_right);
	gtk_widget_class_install_action(wid_class, "win.shortcuts", NULL, win_shortcuts);
	gtk_widget_class_install_action(wid_class, "win.save-tab", NULL, win_save_tab);
	gtk_widget_class_install_action(wid_class, "win.save-tab-as", NULL, win_save_tab_as);
	gtk_widget_class_install_action(wid_class, "win.close-tab", NULL, win_close_tab);
}

static void
pigeon_application_window_init(PigeonApplicationWindow *self)
{
	PigeonApplicationWindowPrivate *priv = pigeon_application_window_get_instance_private(self);

	gtk_widget_init_template(GTK_WIDGET(self));

	self->num_untitled_pages = 0;

	GString *label = g_string_new("Untitled ");
	g_string_append_printf(label, "%u", self->num_untitled_pages);
	PigeonPage *page		= pigeon_page_new();
	PigeonPageTab *page_tab = pigeon_page_tab_new(label->str);
	gtk_notebook_append_page(priv->tab_notebook, GTK_WIDGET(page), GTK_WIDGET(page_tab));
	self->num_untitled_pages++;
}

PigeonApplicationWindow *
pigeon_application_window_new(PigeonApplication *app)
{
	return g_object_new(PIGEON_TYPE_APPLICATION_WINDOW, "application", app, NULL);
}
