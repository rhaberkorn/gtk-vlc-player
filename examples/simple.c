/*
 * Copyright (C) 2012-2013 Otto-von-Guericke-Universität Magdeburg
 * Copyright (C) 2013 Robin Haberkorn
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <glib.h>
#include <glib/gprintf.h>

#include <gdk/gdk.h>
#include <gtk/gtk.h>

/*
 * GtkVlcPlayer header file
 */
#include <gtk-vlc-player.h>

/*
 * this gets called when we close the toplevel
 * GtkWindow
 */
static gboolean
delete_event(GtkWidget *widget, GdkEvent *event, gpointer data)
{
	/* exit event loop */
	gtk_main_quit();
	/* but do not yet destroy window */
	return TRUE;
}

int
main(int argc, char *argv[])
{
	GtkWidget *window, *player;
	gchar *filename;

	/*
	 * init glib and Gdk threads
	 * GtkVlcPlayer requires this since libVLC uses threads
	 */
	g_thread_init(NULL);
	gdk_threads_init();

	gtk_init(&argc, &argv);

	if (argc != 2) {
		g_printf("Usage: simple <video-file>\n");
		return 1;
	}
	filename = argv[1];

	/*
	 * create top level window
	 */
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "GtkVlcPlayer");

	g_signal_connect(window, "delete-event",
			 G_CALLBACK(delete_event), NULL);

	/*
	 * create GtkVlcPlayer widget and add it to
	 * the window
	 */
	player = gtk_vlc_player_new();
	gtk_container_add(GTK_CONTAINER(window), player);

	/*
	 * Load and play video file
	 */
	if (!gtk_vlc_player_load_filename(GTK_VLC_PLAYER(player), filename)) {
		g_fprintf(stderr, "Could not load file \"%s\"\n", filename);
		return 1;
	}
	gtk_vlc_player_play(GTK_VLC_PLAYER(player));

	/*
	 * Show window and player widgets
	 */
	gtk_widget_show_all(window);

	/*
	 * Gtk main loop: do not forget to aquire the
	 * Gdk mutex
	 */
	gdk_threads_enter();
	gtk_main();
	gdk_threads_leave();

	/*
	 * Stop video playback & cleanup
	 */
	gtk_vlc_player_stop(GTK_VLC_PLAYER(player));
	gtk_widget_destroy(window);

	return 0;
}
