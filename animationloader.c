#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
static gint back_width, back_height;
static GdkPixbuf *bgimage;
static GdkPixbufAnimation *bganimation;
static gboolean is_image;

gboolean load_pixbuf(const char *filename){
    GError *error = NULL;
    GdkPixbufAnimation *pixbuf = gdk_pixbuf_animation_new_from_file(filename, &error); 
    	if (pixbuf == NULL){
        	g_print ("Error loading file: %d : %s\n", error->code, error->message);
       	 	g_error_free (error);
        	exit(1);
    	}
   	back_width = gdk_pixbuf_animation_get_width (pixbuf);
	back_height = gdk_pixbuf_animation_get_height (pixbuf);
	if(gdk_pixbuf_animation_is_static_image(pixbuf)){
		bgimage = gdk_pixbuf_animation_get_static_image(pixbuf);
		return TRUE;
	}
	else{
		bganimation  = pixbuf;
	}
	return FALSE;
}

int main (int argc, char **argv){
    
	GtkWidget *window = NULL;
    	GtkWidget *label;
    	GtkWidget *entry;
    	GtkWidget *overlay;
    	GtkWidget *vbox;
	GtkWidget *image;
    	
	gtk_init (&argc, &argv);
    	/* Load a non animated gif */
   	is_image  = load_pixbuf("./coderain.png");
	
    	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    	overlay = gtk_overlay_new ();
	gtk_window_set_title (GTK_WINDOW(window), "Load Image");
    	gtk_window_set_default_size (GTK_WINDOW (window), 600, 500);
    	gtk_window_set_resizable (GTK_WINDOW (window), FALSE);

		
	if(is_image){
		image = gtk_image_new_from_pixbuf(bgimage);
		gtk_overlay_add_overlay(GTK_OVERLAY (overlay),image);
	}else{
		image = gtk_image_new_from_animation(bganimation);
		gtk_overlay_add_overlay (GTK_OVERLAY (overlay),image);
	}
	
 
	/* Vertical Box */
 	vbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 10);
       	gtk_widget_set_halign (vbox, GTK_ALIGN_CENTER);
       	gtk_widget_set_valign (vbox, GTK_ALIGN_CENTER);

 	/* Add Component in Vertical Box */
       	label = gtk_label_new ("<span foreground='blue' weight='ultrabold' font='40'>Numbers</span>");
       	gtk_label_set_use_markup (GTK_LABEL (label), TRUE);
       	entry = gtk_entry_new ();
       	gtk_entry_set_placeholder_text (GTK_ENTRY (entry), "MAYAJAL");
 
	/* Pack components in V box*/
	gtk_box_pack_start (GTK_BOX (vbox), label, FALSE, FALSE, 8);
	gtk_box_pack_start (GTK_BOX (vbox), entry, FALSE, FALSE, 8);


 	/* Add Widgets in Overlay*/
 	gtk_overlay_add_overlay (GTK_OVERLAY (overlay), vbox);
	
	//gtk_overlay_set_overlay_pass_through (GTK_OVERLAY (overlay), vbox, TRUE);
        gtk_container_add (GTK_CONTAINER (window), overlay);
	g_signal_connect(G_OBJECT(window), "destroy",G_CALLBACK(gtk_main_quit), NULL);
	gtk_widget_show_all (window);
    	gtk_main ();     
    	return 0;
}	    
