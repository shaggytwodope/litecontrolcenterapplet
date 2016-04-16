/*
* Copyright © 2016 Johnathan "Shaggytwodope" Jenkins <twodopeshaggy@gmail.com>
*
* Distributed under terms of the GPL2 license.
*/

#ifndef __XFCE_LITECONTROLCENTER_PLUGIN_H__
#define __XFCE_LITECONTROLCENTER_PLUGIN_H__

G_BEGIN_DECLS

#define DEFAULT_ICON_NAME "lite-controlcenter"
#define DEFAULT_TOOLTIP_MESSAGE "Linux Lite Control Center"
#define DEFAULT_RUN_COMMAND "lite-controlcenter"

typedef struct _LitecontrolcenterPlugin
{
  XfcePanelPlugin *plugin;

  GtkWidget       *button;
  GtkWidget       *icon;

  gchar           *icon_name;
}
LitecontrolcenterPlugin;


G_END_DECLS


#endif /* !__XFCE_LITECONTROLCENTER_PLUGIN_H__ */
