/*
* Copyright © 2016 Johnathan "Shaggytwodope" Jenkins <twodopeshaggy@gmail.com>
*
* Distributed under terms of the GPL2 license.
*/

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#ifdef HAVE_STRING_H
#include <string.h>
#endif


#include <gtk/gtk.h>
#include <libxfce4util/libxfce4util.h>
#include <libxfce4panel/xfce-panel-plugin.h>
#include "headers/litecc.h"


#ifdef LIBXFCE4PANEL_CHECK_VERSION
#if LIBXFCE4PANEL_CHECK_VERSION(4, 9, 0)
#define HAS_PANEL_49
#endif
#endif


static void button_clicked(GtkWidget *button, LccPlugin *litecc)
{
    GError *error = NULL;
    g_spawn_command_line_async(DEFAULT_RUN_COMMAND, &error);
    if (error != NULL) {
        g_warning("unable to launch: %s", error->message);
    }
}


static LccPlugin *
litecc_init(XfcePanelPlugin *plugin)
{
    LccPlugin *litecc = g_slice_new0(LccPlugin);
    litecc->plugin = plugin;
    litecc->icon_name = g_strdup(DEFAULT_ICON_NAME);
    litecc->button = xfce_panel_create_button();
    gtk_widget_show(litecc->button);
    g_signal_connect(G_OBJECT(litecc->button),
                     "clicked", G_CALLBACK(button_clicked), plugin);
    gtk_widget_set_tooltip_text(GTK_WIDGET(litecc->button),
                                DEFAULT_TOOLTIP_MESSAGE);
    litecc->icon = xfce_panel_image_new_from_source(litecc->icon_name);
    gtk_widget_show(litecc->icon);
    gtk_container_add(GTK_CONTAINER(litecc->button), litecc->icon);
    return litecc;
}



static void litecc_free(XfcePanelPlugin *plugin, LccPlugin *litecc)
{
    gtk_widget_destroy(litecc->button);
    gtk_widget_destroy(litecc->icon);
    g_slice_free(LccPlugin, litecc);
}



static gboolean litecc_size_changed(XfcePanelPlugin *plugin,
                                    gint size, LccPlugin *litecc)
{
#ifdef HAS_PANEL_49
    size /= xfce_panel_plugin_get_nrows(plugin);
#endif
    gtk_widget_set_size_request(GTK_WIDGET(litecc->button), size, size);
    return TRUE;
}



static void litecc_construct(XfcePanelPlugin *plugin)
{
    LccPlugin *litecc;
    litecc = litecc_init(plugin);
    gtk_container_add(GTK_CONTAINER(plugin), litecc->button);
    xfce_panel_plugin_add_action_widget(plugin, litecc->button);
    g_signal_connect(G_OBJECT(plugin),
                     "free-data", G_CALLBACK(litecc_free), litecc);
    g_signal_connect(G_OBJECT(plugin),
                     "size-changed", G_CALLBACK(litecc_size_changed), litecc);
}

XFCE_PANEL_PLUGIN_REGISTER(litecc_construct);
