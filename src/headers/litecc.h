/*
* Copyright © 2016 Johnathan "Shaggytwodope" Jenkins <twodopeshaggy@gmail.com>
*
* Distributed under terms of the GPL2 license.
*/

#ifndef SRC_LITECC_H_
#define SRC_LITECC_H_

G_BEGIN_DECLS

#define DEFAULT_ICON_NAME "lite-controlcenter"
#define DEFAULT_TOOLTIP_MESSAGE "Linux Lite Control Center"
#define DEFAULT_RUN_COMMAND "lite-controlcenter"

typedef struct _LccPlugin {
  XfcePanelPlugin *plugin;

  GtkWidget       *button;
  GtkWidget       *icon;

  gchar           *icon_name;
}
LccPlugin;


G_END_DECLS


#endif /* SRC_LITECC_H__ */
