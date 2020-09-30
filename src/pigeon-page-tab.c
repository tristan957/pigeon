#include "config.h"

#include <string.h>

#include <glib-object.h>
#include <glib/gi18n.h>
#include <gtk/gtk.h>

#include "pigeon-page-tab.h"

struct _PigeonPageTab
{
	GtkBox parent_instance;
};

typedef struct PigeonPageTabPrivate
{
	GtkStack *label_stack;
	GtkLabel *label;
	GtkText *label_entry;
	GtkButton *close_button;
} PigeonPageTabPrivate;

G_DEFINE_TYPE_WITH_PRIVATE(PigeonPageTab, pigeon_page_tab, GTK_TYPE_BOX)

enum
{
	PROP_0,
	PROP_LABEL,
	N_PROPS,
};

static GParamSpec *obj_properties[N_PROPS];

static void
click_cb(G_GNUC_UNUSED GtkGestureClick *gesture, int n_press, G_GNUC_UNUSED double x,
	G_GNUC_UNUSED double y, gpointer user_data)
{
	if (n_press != 2)
		return;

	PigeonPageTab *self		   = PIGEON_PAGE_TAB(user_data);
	PigeonPageTabPrivate *priv = pigeon_page_tab_get_instance_private(self);

	GtkEntryBuffer *buffer = gtk_text_get_buffer(priv->label_entry);
	const char *curr_label = gtk_label_get_text(priv->label);
	gtk_entry_buffer_set_text(buffer, curr_label, strlen(curr_label));
	gtk_stack_set_visible_child_name(GTK_STACK(priv->label_stack), "edit");
	gtk_widget_grab_focus(GTK_WIDGET(priv->label_entry));
}

static void
key_released_cb(G_GNUC_UNUSED GtkEventControllerKey *controller, guint keyval,
	G_GNUC_UNUSED guint keycode, G_GNUC_UNUSED GdkModifierType state, gpointer user_data)
{
	PigeonPageTab *self		   = PIGEON_PAGE_TAB(user_data);
	PigeonPageTabPrivate *priv = pigeon_page_tab_get_instance_private(self);

	GtkEntryBuffer *buffer = gtk_text_get_buffer(priv->label_entry);

	if (keyval == GDK_KEY_Escape)
		goto finish;

	if (keyval != GDK_KEY_Return)
		return;

	const char *new_label = gtk_entry_buffer_get_text(buffer);
	gtk_label_set_label(priv->label, new_label);
	gtk_widget_set_tooltip_text(GTK_WIDGET(priv->label), new_label);
finish:
	gtk_entry_buffer_delete_text(buffer, 0, -1);
	gtk_stack_set_visible_child_name(priv->label_stack, "readonly");
}

static void
pigeon_page_tab_get_property(GObject *obj, guint prop_id, GValue *val, GParamSpec *pspec)
{
	PigeonPageTab *self		   = PIGEON_PAGE_TAB(obj);
	PigeonPageTabPrivate *priv = pigeon_page_tab_get_instance_private(self);

	switch (prop_id) {
	case PROP_LABEL:
		g_value_set_string(val, gtk_label_get_label(priv->label));
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID(obj, prop_id, pspec);
	}
}

static void
pigeon_page_tab_set_property(GObject *obj, guint prop_id, const GValue *val, GParamSpec *pspec)
{
	PigeonPageTab *self		   = PIGEON_PAGE_TAB(obj);
	PigeonPageTabPrivate *priv = pigeon_page_tab_get_instance_private(self);

	switch (prop_id) {
	case PROP_LABEL:
		gtk_label_set_text(priv->label, g_value_get_string(val));
		gtk_widget_set_tooltip_text(GTK_WIDGET(priv->label), g_value_get_string(val));
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID(obj, prop_id, pspec);
	}
}

static void
pigeon_page_tab_class_init(PigeonPageTabClass *klass)
{
	GObjectClass *obj_class	  = G_OBJECT_CLASS(klass);
	GtkWidgetClass *wid_class = GTK_WIDGET_CLASS(klass);

	obj_class->get_property = pigeon_page_tab_get_property;
	obj_class->set_property = pigeon_page_tab_set_property;

	obj_properties[PROP_LABEL]
		= g_param_spec_string("label", _("Label"), _("Label of the tab"), NULL, G_PARAM_READWRITE);

	g_object_class_install_properties(obj_class, N_PROPS, obj_properties);

	gtk_widget_class_set_template_from_resource(
		wid_class, "/io/partin/tristan/Pigeon/ui/pigeon-page-tab.ui");
	gtk_widget_class_bind_template_child_private(wid_class, PigeonPageTab, label_stack);
	gtk_widget_class_bind_template_child_private(wid_class, PigeonPageTab, label);
	gtk_widget_class_bind_template_child_private(wid_class, PigeonPageTab, label_entry);
	gtk_widget_class_bind_template_child_private(wid_class, PigeonPageTab, close_button);

	// gtk_widget_class_set_layout_manager_type(wid_class, GTK_TYPE_BOX_LAYOUT);
}

static void
pigeon_page_tab_init(PigeonPageTab *self)
{
	PigeonPageTabPrivate *priv = pigeon_page_tab_get_instance_private(self);

	gtk_widget_init_template(GTK_WIDGET(self));

	GtkGesture *click_gesture = gtk_gesture_click_new();
	g_signal_connect(click_gesture, "pressed", G_CALLBACK(click_cb), self);
	gtk_widget_add_controller(GTK_WIDGET(priv->label), GTK_EVENT_CONTROLLER(click_gesture));

	GtkEventController *key_controller = gtk_event_controller_key_new();
	g_signal_connect(key_controller, "key-released", G_CALLBACK(key_released_cb), self);
	gtk_widget_add_controller(GTK_WIDGET(priv->label_entry), key_controller);
}

PigeonPageTab *
pigeon_page_tab_new(const char *label)
{
	return g_object_new(PIGEON_TYPE_PAGE_TAB, "label", label, NULL);
}
