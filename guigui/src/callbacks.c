#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"



void update_status()
{
	char temp[1000]="\tIP address:\n\tTask Id:\n\tTask Priority:\n\tStatus: Compiling/Executing/Error\n\tResult: \n\tTime of Exceution: \n\tError(if any): \n new ";
	char number[100] ;
	sprintf(number,"%d",index_of_active_client);
	strcat(temp,number);	
	gtk_text_buffer_set_text (gtk_text_view_get_buffer (GTK_TEXT_VIEW (textview1)), (temp), -1);
	gtk_widget_show(textview1);
}


gboolean
on_window1_destroy_event               (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data)
{

  gtk_widget_destroy(widget);	
  gtk_main_quit();
        exit(0);
  return FALSE;
}


void
on_filechooserwidget1_file_activated   (GtkFileChooser  *filechooser,
                                        gpointer         user_data)
{
 GFile *fp = gtk_file_chooser_get_file(filechooser); 
 g_print("%s",g_file_get_path(fp));
 //file selecing code
 close(fp);


}


void
on_check_button_clicked                (GtkButton       *button,
                                        gpointer         user_data)
{
  //checking logic
  window2 = create_window2 ();
  gtk_widget_show (window2);
}


void
on_go_button_clicked                   (GtkButton       *button,
                                        gpointer         user_data)
{
 window3 = create_window3 ();       
 gtk_widget_show (window3);
}


gboolean
on_window2_delete_event                (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data)
{
  gtk_widget_destroy(widget);	
  return FALSE;
}


void
on_back_clicked                        (GtkButton       *button,
                                        gpointer         user_data)
{
 gtk_widget_destroy(window2);	
}


gboolean
on_window3_destroy_event               (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data)
{
  gtk_widget_destroy(widget);      
  return FALSE;
}


void
on_combobox1_changed                   (GtkComboBox     *combobox,
                                        gpointer         user_data)
{
index_of_active_client = gtk_combo_box_get_active(combobox);
update_status();
}


void
on_refresh_clicked                     (GtkButton       *button,
                                        gpointer         user_data)
{
update_status();
}


gboolean
on_window1_delete_event                (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data)
{
  gtk_widget_destroy(widget);	
  gtk_main_quit();
        exit(0);
  return FALSE;
}

