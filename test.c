#include <stdio.h>
#include <stdlib.h>
#include <xcb/xcb.h>
#include <gtk/gtk.h>
#include <gdk/gdkx.h>

// Callback function for key press event
gboolean on_key_press(GtkWidget *widget, GdkEventKey *event, gpointer user_data) {
    if (event->keyval == GDK_KEY_Escape) {
        gtk_main_quit();
    }
    return FALSE;
}

int main() {
    // Initialize XCB connection
    xcb_connection_t *connection = xcb_connect(NULL, NULL);

    // Get screen dimensions
    xcb_screen_t *screen = xcb_setup_roots_iterator(xcb_get_setup(connection)).data;
    int screen_width = screen->width_in_pixels;
    int screen_height = screen->height_in_pixels;

    // Create an XCB window
    xcb_window_t window = xcb_generate_id(connection);
    xcb_create_window(connection, XCB_COPY_FROM_PARENT, window, screen->root,
                      0, 0, screen_width, screen_height, 0, XCB_WINDOW_CLASS_INPUT_OUTPUT,
                      screen->root_visual, 0, NULL);

    // Map the window
    xcb_map_window(connection, window);
    xcb_flush(connection);

    // Initialize GTK
    gtk_init(NULL, NULL);

    // Create a GTK window
    GdkWindow *gdk_window = gdk_x11_window_foreign_new_for_display(gdk_display_get_default(), window);
    GtkWidget *gtk_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_size_request(gtk_window, screen_width, screen_height);
    gtk_window_set_title(GTK_WINDOW(gtk_window), "XCB + GTK Window");
    gtk_widget_set_window(gtk_window, gdk_window);
    gtk_widget_realize(gtk_window);

    // Connect key press event to the callback function
    g_signal_connect(G_OBJECT(gtk_window), "key-press-event", G_CALLBACK(on_key_press), NULL);

    // Show the GTK window
    gtk_widget_show_all(gtk_window);

    // Main event loop
    gtk_main();

    // Cleanup
    xcb_destroy_window(connection, window);
    xcb_disconnect(connection);

    return 0;
}
