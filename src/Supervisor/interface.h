/*
 * DO NOT EDIT THIS FILE - it is generated by Glade.
 */
#include <string>
#include <vector>
using namespace std;

GtkWidget* create_window1 (void);
GtkWidget* create_window2 (void);
GtkWidget* create_window3 (void);

void delete_window1_show2();
void delete_window2_show3();

void * updater(void *args);
gpointer thread_func( gpointer data );

gboolean task_info_timeout( gpointer data );
gboolean overview_timeout( gpointer data );
gboolean worker_timeout( gpointer data );
gboolean current_worker_info_timeout( gpointer data );


void send_to_task_info(string message);
void send_to_overview(string message);


void xml_signal();

void update_worker_box(vector<string>);

void update_status(gchar *);

string get_information(string);
