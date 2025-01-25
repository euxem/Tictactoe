#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <gtk/gtk.h>

void initWindow(GtkWidget*& window);

void on_destroy(GtkWidget* widget, gpointer data);

#endif
