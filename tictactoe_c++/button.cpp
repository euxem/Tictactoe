#include "button.h"

Bouton::Bouton(const std::string& label, void (*callback) (GtkWidget*, gpointer)) {
    this->button = gtk_button_new_with_label(label.c_str());
    g_signal_connect(this->button, "clicked", G_CALLBACK(callback), this);
}

Bouton::Bouton(const std::string& label, void (*callback) (GtkWidget*, gpointer), unsigned int width, unsigned int height, void* userData) {
    this->button = gtk_button_new_with_label(label.c_str());
    g_signal_connect(this->button, "clicked", G_CALLBACK(callback), userData);
    gtk_widget_set_size_request(this->button, width, height);
}

Bouton::~Bouton() {
}

GtkWidget* Bouton::getButton() {
    return this->button;
}
