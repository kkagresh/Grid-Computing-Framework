/*
 * DO NOT EDIT THIS FILE - it is generated by Glade.
 */

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <vector>
#include <string>

#include <gdk/gdkkeysyms.h>
#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"

using namespace std;

#define GLADE_HOOKUP_OBJECT(component,widget,name) \
  g_object_set_data_full (G_OBJECT (component), name, \
    gtk_widget_ref (widget), (GDestroyNotify) gtk_widget_unref)

#define GLADE_HOOKUP_OBJECT_NO_REF(component,widget,name) \
  g_object_set_data (G_OBJECT (component), name, widget)

GtkWidget * window1;
GtkWidget * window2;
GtkWidget * window3;
GtkWidget *textview5;
GtkWidget *textview6;
GtkWidget *textview7;
GtkWidget *combobox1;

gboolean list_updated;
string task_info;
string overview;
vector<string> task_vector;
vector<string> overview_vector;
vector<string> worker_vector;
string current_worker;

int combo_size;

GtkWidget*
create_window1 (void)
{
  GtkWidget *vbox10;
  GtkWidget *label11;
  GtkWidget *hbox4;
  GtkWidget *hbuttonbox1;
  GtkWidget *recover_old;
  GtkWidget *start_new;

  window1 = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_widget_set_size_request (window1, 600, 200);
  gtk_window_set_title (GTK_WINDOW (window1), _("Grid Computing Framework"));

  vbox10 = gtk_vbox_new (FALSE, 0);
  gtk_widget_show (vbox10);
  gtk_container_add (GTK_CONTAINER (window1), vbox10);

  label11 = gtk_label_new (_("<b>Click the appropriate button to continue</b>"));
  gtk_widget_show (label11);
  gtk_box_pack_start (GTK_BOX (vbox10), label11, FALSE, FALSE, 0);
  gtk_widget_set_size_request (label11, -1, 100);
  gtk_label_set_use_markup (GTK_LABEL (label11), TRUE);

  hbox4 = gtk_hbox_new (FALSE, 0);
  gtk_widget_show (hbox4);
  gtk_box_pack_start (GTK_BOX (vbox10), hbox4, TRUE, TRUE, 0);

  hbuttonbox1 = gtk_hbutton_box_new ();
  gtk_widget_show (hbuttonbox1);
  gtk_box_pack_start (GTK_BOX (hbox4), hbuttonbox1, TRUE, TRUE, 0);
  gtk_button_box_set_layout (GTK_BUTTON_BOX (hbuttonbox1), GTK_BUTTONBOX_SPREAD);

  recover_old = gtk_button_new_with_mnemonic (_("Recover Old Tasks"));
  gtk_widget_show (recover_old);
  gtk_container_add (GTK_CONTAINER (hbuttonbox1), recover_old);
  GTK_WIDGET_SET_FLAGS (recover_old, GTK_CAN_DEFAULT);

  start_new = gtk_button_new_with_mnemonic (_("Start New Tasks"));
  gtk_widget_show (start_new);
  gtk_container_add (GTK_CONTAINER (hbuttonbox1), start_new);
  GTK_WIDGET_SET_FLAGS (start_new, GTK_CAN_DEFAULT);

  g_signal_connect ((gpointer) window1, "delete_event",
                    G_CALLBACK (on_window1_delete_event),
                    NULL);
  g_signal_connect ((gpointer) recover_old, "clicked",
                    G_CALLBACK (on_recover_old_clicked),
                    NULL);
  g_signal_connect ((gpointer) start_new, "clicked",
                    G_CALLBACK (on_start_new_clicked),
                    NULL);

  /* Store pointers to all widgets, for use by lookup_widget(). */
  GLADE_HOOKUP_OBJECT_NO_REF (window1, window1, "window1");
  GLADE_HOOKUP_OBJECT (window1, vbox10, "vbox10");
  GLADE_HOOKUP_OBJECT (window1, label11, "label11");
  GLADE_HOOKUP_OBJECT (window1, hbox4, "hbox4");
  GLADE_HOOKUP_OBJECT (window1, hbuttonbox1, "hbuttonbox1");
  GLADE_HOOKUP_OBJECT (window1, recover_old, "recover_old");
  GLADE_HOOKUP_OBJECT (window1, start_new, "start_new");

  return window1;
}

GtkWidget*
create_window2 (void)
{
  GtkWidget *vbox3;
  GtkWidget *filechooserwidget1;
  GtkWidget *upload_file;

  window2 = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_widget_set_size_request (window2, 600, 400);
  gtk_window_set_title (GTK_WINDOW (window2), _("File Selector Window"));
  gtk_window_set_destroy_with_parent (GTK_WINDOW (window2), TRUE);

  vbox3 = gtk_vbox_new (FALSE, 0);
  gtk_widget_show (vbox3);
  gtk_container_add (GTK_CONTAINER (window2), vbox3);

  filechooserwidget1 = gtk_file_chooser_widget_new (GTK_FILE_CHOOSER_ACTION_OPEN);
  gtk_widget_show (filechooserwidget1);
  gtk_box_pack_start (GTK_BOX (vbox3), filechooserwidget1, TRUE, TRUE, 0);

  upload_file = gtk_button_new_with_mnemonic (_("Select FIle and Proceed"));
  gtk_widget_show (upload_file);
  gtk_box_pack_start (GTK_BOX (vbox3), upload_file, FALSE, FALSE, 0);
  gtk_widget_set_size_request (upload_file, -1, 50);
  gtk_container_set_border_width (GTK_CONTAINER (upload_file), 3);

  g_signal_connect ((gpointer) window2, "delete_event",
                    G_CALLBACK (on_window2_delete_event),
                    NULL);
  g_signal_connect ((gpointer) filechooserwidget1, "file_activated",
                    G_CALLBACK (on_filechooserwidget1_file_activated),
                    NULL);
  g_signal_connect ((gpointer) upload_file, "clicked",
                    G_CALLBACK (on_upload_file_clicked),
                    NULL);

  /* Store pointers to all widgets, for use by lookup_widget(). */
  GLADE_HOOKUP_OBJECT_NO_REF (window2, window2, "window2");
  GLADE_HOOKUP_OBJECT (window2, vbox3, "vbox3");
  GLADE_HOOKUP_OBJECT (window2, filechooserwidget1, "filechooserwidget1");
  GLADE_HOOKUP_OBJECT (window2, upload_file, "upload_file");

  return window2;
}

GtkWidget*
create_window3 (void)
{

  GtkWidget *notebook1;
  GtkWidget *vbox7;
  GtkWidget *label7;
  GtkWidget *scrolledwindow5;
  GtkWidget *stop_execution;
  GtkWidget *label2;
  GtkWidget *vbox8;
  GtkWidget *label8;
  GtkWidget *scrolledwindow6;
  GtkWidget *label3;
  GtkWidget *vbox11;
  GtkWidget *label12;
  GtkWidget *scrolledwindow7;
  GtkWidget *display_client;
  GtkWidget *label4;
  GtkWidget *label10;
  GtkWidget *label5;

  window3 = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_widget_set_size_request (window3, 600, 400);
  gtk_window_set_title (GTK_WINDOW (window3), _("Supervisor Execution"));
  gtk_window_set_destroy_with_parent (GTK_WINDOW (window3), TRUE);

  notebook1 = gtk_notebook_new ();
  gtk_widget_show (notebook1);
  gtk_container_add (GTK_CONTAINER (window3), notebook1);

  vbox7 = gtk_vbox_new (FALSE, 0);
  gtk_widget_show (vbox7);
  gtk_container_add (GTK_CONTAINER (notebook1), vbox7);

  label7 = gtk_label_new (_("<b>Complete Overview of Tasks</b>"));
  gtk_widget_show (label7);
  gtk_box_pack_start (GTK_BOX (vbox7), label7, FALSE, FALSE, 0);
  gtk_label_set_use_markup (GTK_LABEL (label7), TRUE);

  scrolledwindow5 = gtk_scrolled_window_new (NULL, NULL);
  gtk_widget_show (scrolledwindow5);
  gtk_box_pack_start (GTK_BOX (vbox7), scrolledwindow5, TRUE, TRUE, 0);
  gtk_scrolled_window_set_shadow_type (GTK_SCROLLED_WINDOW (scrolledwindow5), GTK_SHADOW_IN);

  textview5 = gtk_text_view_new ();
  gtk_widget_show (textview5);
  gtk_container_add (GTK_CONTAINER (scrolledwindow5), textview5);
  gtk_text_view_set_editable (GTK_TEXT_VIEW (textview5), FALSE);

  stop_execution = gtk_button_new_with_mnemonic (_("Stop Execution"));
  //gtk_widget_show (stop_execution);
  //gtk_box_pack_start (GTK_BOX (vbox7), stop_execution, FALSE, FALSE, 0);

  label2 = gtk_label_new (_("<b>Overview</b>"));
  gtk_widget_show (label2);
  gtk_notebook_set_tab_label (GTK_NOTEBOOK (notebook1), gtk_notebook_get_nth_page (GTK_NOTEBOOK (notebook1), 0), label2);
  gtk_label_set_use_markup (GTK_LABEL (label2), TRUE);
  gtk_label_set_justify (GTK_LABEL (label2), GTK_JUSTIFY_CENTER);
  gtk_misc_set_padding (GTK_MISC (label2), 5, 0);

  vbox8 = gtk_vbox_new (FALSE, 0);
  gtk_widget_show (vbox8);
  gtk_container_add (GTK_CONTAINER (notebook1), vbox8);

  label8 = gtk_label_new (_("<b>Information of Tasks</b>"));
  gtk_widget_show (label8);
  gtk_box_pack_start (GTK_BOX (vbox8), label8, FALSE, FALSE, 0);
  gtk_label_set_use_markup (GTK_LABEL (label8), TRUE);
  gtk_label_set_justify (GTK_LABEL (label8), GTK_JUSTIFY_CENTER);

  scrolledwindow6 = gtk_scrolled_window_new (NULL, NULL);
  gtk_widget_show (scrolledwindow6);
  gtk_box_pack_start (GTK_BOX (vbox8), scrolledwindow6, TRUE, TRUE, 0);
  gtk_scrolled_window_set_shadow_type (GTK_SCROLLED_WINDOW (scrolledwindow6), GTK_SHADOW_IN);

  textview6 = gtk_text_view_new ();
  gtk_widget_show (textview6);
  gtk_container_add (GTK_CONTAINER (scrolledwindow6), textview6);
  gtk_text_view_set_cursor_visible (GTK_TEXT_VIEW (textview6), FALSE);

  label3 = gtk_label_new (_("<b>Task Information</b>"));
  gtk_widget_show (label3);
  gtk_notebook_set_tab_label (GTK_NOTEBOOK (notebook1), gtk_notebook_get_nth_page (GTK_NOTEBOOK (notebook1), 1), label3);
  gtk_label_set_use_markup (GTK_LABEL (label3), TRUE);
  gtk_label_set_justify (GTK_LABEL (label3), GTK_JUSTIFY_CENTER);
  gtk_misc_set_padding (GTK_MISC (label3), 5, 0);

  vbox11 = gtk_vbox_new (FALSE, 0);
  gtk_widget_show (vbox11);
  gtk_container_add (GTK_CONTAINER (notebook1), vbox11);

  label12 = gtk_label_new (_("<b>Click on a worker to view its status</b>"));
  gtk_widget_show (label12);
  gtk_box_pack_start (GTK_BOX (vbox11), label12, FALSE, FALSE, 0);
  gtk_label_set_use_markup (GTK_LABEL (label12), TRUE);
  gtk_label_set_justify (GTK_LABEL (label12), GTK_JUSTIFY_CENTER);
  gtk_misc_set_padding (GTK_MISC (label12), 5, 0);

  combobox1 = gtk_combo_box_new_text ();
  gtk_combo_box_set_title(GTK_COMBO_BOX (combobox1),_("Select Worker"));
  gtk_widget_show (combobox1);
  gtk_box_pack_start (GTK_BOX (vbox11), combobox1, FALSE, TRUE, 0);
  combo_size = 0;

  scrolledwindow7 = gtk_scrolled_window_new (NULL, NULL);
  gtk_widget_show (scrolledwindow7);
  gtk_box_pack_start (GTK_BOX (vbox11), scrolledwindow7, TRUE, TRUE, 0);
  gtk_scrolled_window_set_shadow_type (GTK_SCROLLED_WINDOW (scrolledwindow7), GTK_SHADOW_IN);

  textview7 = gtk_text_view_new ();
  gtk_widget_show (textview7);
  gtk_container_add (GTK_CONTAINER (scrolledwindow7), textview7);
  gtk_text_view_set_editable (GTK_TEXT_VIEW (textview7), FALSE);

  display_client = gtk_button_new_with_mnemonic (_("Display Worker Information"));
  gtk_widget_show (display_client);
  gtk_box_pack_start (GTK_BOX (vbox11), display_client, FALSE, FALSE, 0);

  label4 = gtk_label_new (_("<b>Worker Information</b>"));
  gtk_widget_show (label4);
  gtk_notebook_set_tab_label (GTK_NOTEBOOK (notebook1), gtk_notebook_get_nth_page (GTK_NOTEBOOK (notebook1), 2), label4);
  gtk_label_set_use_markup (GTK_LABEL (label4), TRUE);
  gtk_label_set_justify (GTK_LABEL (label4), GTK_JUSTIFY_CENTER);
  gtk_misc_set_padding (GTK_MISC (label4), 6, 0);

  label10 = gtk_label_new (_("			<b>Grid Computing Framework</b>\n\n					Authors\n_________________________________________________________\n\n			<b>Gaurav Menghani (Red.Dragon) </b>\n			<b>Anil Harwani (Gohan)</b>\n			<b>Yash Londhe</b>\n			<b>Kalpesh Kagresha</b>\n_________________________________________________________\n\n	For any queries please please contact us\n	Released Under GPL (GNU PLublic License)\n	For any queries please contact us at:\n	<b>gridcomputingframework@gmail.com</b>\n"));
  gtk_widget_show (label10);
  gtk_container_add (GTK_CONTAINER (notebook1), label10);
  gtk_label_set_use_markup (GTK_LABEL (label10), TRUE);
  //gtk_label_set_justify (GTK_LABEL (label10), GTK_JUSTIFY_CENTER);

  label5 = gtk_label_new (_("<b>About Us</b>"));
  gtk_widget_show (label5);
  gtk_notebook_set_tab_label (GTK_NOTEBOOK (notebook1), gtk_notebook_get_nth_page (GTK_NOTEBOOK (notebook1), 3), label5);
  gtk_label_set_use_markup (GTK_LABEL (label5), TRUE);
  gtk_label_set_justify (GTK_LABEL (label5), GTK_JUSTIFY_CENTER);
  gtk_misc_set_padding (GTK_MISC (label5), 6, 0);

  g_signal_connect ((gpointer) window3, "delete_event",
                    G_CALLBACK (on_window3_delete_event),
                    NULL);
  g_signal_connect ((gpointer) stop_execution, "clicked",
                    G_CALLBACK (on_stop_execution_clicked),
                    NULL);
  g_signal_connect ((gpointer) combobox1, "changed",
                    G_CALLBACK (on_combobox1_changed),
                    NULL);
  g_signal_connect ((gpointer) display_client, "clicked",
                    G_CALLBACK (on_display_client_clicked),
                    NULL);

  /* Store pointers to all widgets, for use by lookup_widget(). */
  GLADE_HOOKUP_OBJECT_NO_REF (window3, window3, "window3");
  GLADE_HOOKUP_OBJECT (window3, notebook1, "notebook1");
  GLADE_HOOKUP_OBJECT (window3, vbox7, "vbox7");
  GLADE_HOOKUP_OBJECT (window3, label7, "label7");
  GLADE_HOOKUP_OBJECT (window3, scrolledwindow5, "scrolledwindow5");
  GLADE_HOOKUP_OBJECT (window3, textview5, "textview5");
  GLADE_HOOKUP_OBJECT (window3, stop_execution, "stop_execution");
  GLADE_HOOKUP_OBJECT (window3, label2, "label2");
  GLADE_HOOKUP_OBJECT (window3, vbox8, "vbox8");
  GLADE_HOOKUP_OBJECT (window3, label8, "label8");
  GLADE_HOOKUP_OBJECT (window3, scrolledwindow6, "scrolledwindow6");
  GLADE_HOOKUP_OBJECT (window3, textview6, "textview6");
  GLADE_HOOKUP_OBJECT (window3, label3, "label3");
  GLADE_HOOKUP_OBJECT (window3, vbox11, "vbox11");
  GLADE_HOOKUP_OBJECT (window3, label12, "label12");
  GLADE_HOOKUP_OBJECT (window3, combobox1, "combobox1");
  GLADE_HOOKUP_OBJECT (window3, scrolledwindow7, "scrolledwindow7");
  GLADE_HOOKUP_OBJECT (window3, textview7, "textview7");
  GLADE_HOOKUP_OBJECT (window3, display_client, "display_client");
  GLADE_HOOKUP_OBJECT (window3, label4, "label4");
  GLADE_HOOKUP_OBJECT (window3, label10, "label10");
  GLADE_HOOKUP_OBJECT (window3, label5, "label5");
  list_updated = TRUE;
  return window3;
}

void delete_window2_show3()
{
	gtk_widget_destroy(window2);
	window3 = create_window3 ();
	gtk_widget_show (window3);
}

void delete_window1_show2()
{	
	gtk_widget_destroy(window1);
	window2 = create_window2 ();
	gtk_widget_show (window2);
}

void delete_window1_show3()
{
	gtk_widget_destroy(window1);
	window3 = create_window3 ();
	gtk_widget_show (window3);	
}

void * updater(void *args)
{
	while(1)
	{
		sleep(3);
	}
}

gpointer
thread_func( gpointer data )
{
    while( TRUE )
    {
        g_usleep( 10000 );
    }
 
    return( NULL );
}

gboolean overview_timeout( gpointer data )
{
	gtk_text_buffer_set_text(gtk_text_view_get_buffer (GTK_TEXT_VIEW(textview5)),overview.c_str(),-1);
    return( TRUE );	
}

gboolean task_info_timeout( gpointer data )
{
    gtk_text_buffer_set_text(gtk_text_view_get_buffer (GTK_TEXT_VIEW(textview6)),task_info.c_str(),-1);
    return( TRUE );
}


gboolean current_worker_info_timeout( gpointer data )
{
    gtk_text_buffer_set_text(gtk_text_view_get_buffer (GTK_TEXT_VIEW(textview7)),current_worker.c_str(),-1);
    return( TRUE );
}

gboolean worker_timeout( gpointer data )
{
	
	if(!list_updated )
		return ( TRUE );
	for(int i = 0 ;i<combo_size ; i++)
	{
		gtk_combo_box_remove_text(GTK_COMBO_BOX(combobox1),0);
		
	}
	for(int i = 0 ; i < worker_vector.size() ; i++ )
	{
			gtk_combo_box_append_text (GTK_COMBO_BOX (combobox1), worker_vector[i].c_str());
	}
	combo_size = worker_vector.size();
	list_updated = FALSE;
    return( TRUE );	
}


void send_to_task_info(string message)
{
  task_vector.push_back(message);

  task_info = "";
  for(int i=0;i<task_vector.size();i++)
   { task_info += task_vector[i];;
     task_info +="\n"; 
   }	
}

void send_to_overview(string message)
{
  overview_vector.push_back(message);

  overview = "";
  for(int i=0;i<overview_vector.size();i++)
   { overview += overview_vector[i];;
     overview +="\n"; 
   }	
}


void update_worker_box(vector<string> workers)
{
	
	list_updated = TRUE;
	worker_vector.clear();
	
	for(int i = 0 ;i < workers.size() ;i++)
	{
				worker_vector.push_back(workers[i]);
	}
}


void update_status(gchar *text)
{
        char result[200];
		strcpy(result,text);
		current_worker = get_information((string)result);
}
