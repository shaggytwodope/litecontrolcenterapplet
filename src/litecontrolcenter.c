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
#include "litecontrolcenter.h"


#ifdef LIBXFCE4PANEL_CHECK_VERSION
  #if LIBXFCE4PANEL_CHECK_VERSION(4,9,0)
    #define HAS_PANEL_49
  #endif
#endif


static void button_clicked(GtkWidget *button, LitecontrolcenterPlugin *litecontrolcenter)
{
    GError *error = NULL;
    g_spawn_command_line_async(DEFAULT_RUN_COMMAND, &error);
    if (error != NULL)
     {
       g_warning("unable to launch: %s", error->message);
     }
}


static LitecontrolcenterPlugin *
litecontrolcenter_init(XfcePanelPlugin *plugin)
{
  LitecontrolcenterPlugin *litecontrolcenter = g_slice_new0(LitecontrolcenterPlugin);
  litecontrolcenter->plugin = plugin;
  litecontrolcenter->icon_name = g_strdup(DEFAULT_ICON_NAME);
  litecontrolcenter->button = xfce_panel_create_button();
  gtk_widget_show(litecontrolcenter->button);
  g_signal_connect(G_OBJECT(litecontrolcenter->button), "clicked", G_CALLBACK(button_clicked), plugin);
  gtk_widget_set_tooltip_text(GTK_WIDGET (litecontrolcenter->button), DEFAULT_TOOLTIP_MESSAGE);
  litecontrolcenter->icon = xfce_panel_image_new_from_source( litecontrolcenter->icon_name);
  gtk_widget_show(litecontrolcenter->icon);
  gtk_container_add(GTK_CONTAINER(litecontrolcenter->button), litecontrolcenter->icon);
  return litecontrolcenter;
}



static void litecontrolcenter_free(XfcePanelPlugin *plugin, LitecontrolcenterPlugin *litecontrolcenter)
{
  gtk_widget_destroy(litecontrolcenter->button);
  gtk_widget_destroy(litecontrolcenter->icon);
  g_slice_free(LitecontrolcenterPlugin, litecontrolcenter);
}



static gboolean litecontrolcenter_size_changed(XfcePanelPlugin *plugin, gint size, LitecontrolcenterPlugin *litecontrolcenter)
{
#ifdef HAS_PANEL_49
   size /= xfce_panel_plugin_get_nrows(plugin);
#endif
   gtk_widget_set_size_request(GTK_WIDGET(litecontrolcenter->button), size, size);
   return TRUE;
}



static void litecontrolcenter_construct(XfcePanelPlugin *plugin)
{
  LitecontrolcenterPlugin *litecontrolcenter;
  litecontrolcenter = litecontrolcenter_init(plugin);
  gtk_container_add(GTK_CONTAINER(plugin), litecontrolcenter->button);
  xfce_panel_plugin_add_action_widget(plugin, litecontrolcenter->button);
  g_signal_connect(G_OBJECT(plugin), "free-data", G_CALLBACK(litecontrolcenter_free), litecontrolcenter);
  g_signal_connect(G_OBJECT(plugin), "size-changed", G_CALLBACK(litecontrolcenter_size_changed), litecontrolcenter);

}

XFCE_PANEL_PLUGIN_REGISTER(litecontrolcenter_construct);
