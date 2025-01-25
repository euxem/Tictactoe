#ifndef __BUTTON_H__
#define __BUTTON_H__

#include <gtk/gtk.h>
#include <string>

class Bouton
{
private:
    GtkWidget *button;
public:
    Bouton(const std::string& label, void (*callback) (GtkWidget*, gpointer));
    Bouton(const std::string& label, void (*callback) (GtkWidget*, gpointer), unsigned int width, unsigned int height, void* userData);
    ~Bouton();
    GtkWidget* getButton();
};

#endif