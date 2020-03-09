#include <gtk/gtk.h>
#include <unistd.h> 
#include <fcntl.h> 
#include <stdio.h> 
#include <sys/types.h> 
#include <sys/stat.h> 
#include <errno.h> 
#include <string.h> 
#define BUFFER_SIZE 1024   //缓冲区大小
int a = 0;
//gcc lab1-2.c -o lab1-2 `pkg-config --cflags --libs gtk+-2.0`
void callback(GtkWidget *widget,gpointer data)
{
    g_print ("Hello again - %s was pressed\n", (gchar *) data);
}

gint delete_event(GtkWidget *widget,GdkEvent *event,gpointer data )
{
    gtk_main_quit ();
    return FALSE;
}

gint progress_timeout(gpointer data)
{
    GtkWidget *pbar = (GtkWidget *)data;
    gdouble new_val = 0;
    new_val = gtk_progress_bar_get_fraction (GTK_PROGRESS_BAR (pbar)) + 0.01;
    if(new_val > 0.9 && a == 1){
        gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR (pbar), 1);
        g_print ("Copy finished\n");
        return FALSE;
    }else if(new_val > 0.9){
        return TRUE;
    }else
        gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR (pbar), new_val);
    return TRUE;
}

int main(int argc,char *argv[])
{
    GtkWidget *window;
    GtkWidget *button;
    GtkWidget *box1;
    GtkWidget *pbar;

    gtk_init (&argc, &argv);

    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);

    gtk_window_set_title (GTK_WINDOW (window), "Hello Buttons!");

    g_signal_connect (G_OBJECT (window), "delete_event",
		      G_CALLBACK (delete_event), NULL);

    gtk_container_set_border_width (GTK_CONTAINER (window), 10);

    box1 = gtk_vbox_new (FALSE, 0);
    gtk_container_add (GTK_CONTAINER (window), box1);

    pbar = gtk_progress_bar_new ();
    gtk_progress_bar_set_orientation (GTK_PROGRESS_BAR (pbar), GTK_PROGRESS_LEFT_TO_RIGHT);
    gtk_progress_bar_set_text (GTK_PROGRESS_BAR (pbar), argv[3]);
    gtk_box_pack_start (GTK_BOX(box1), pbar, TRUE, TRUE, 0);

    button = gtk_button_new_with_label ("Button 1");
    g_signal_connect (G_OBJECT (button), "clicked",G_CALLBACK (callback), "button 1");
    gtk_box_pack_start (GTK_BOX(box1), button, TRUE, TRUE, 0);


   
    /* 显示的顺序并不重要，但我建议最后显示窗口。这样它们会同时显示出来。*/
    gtk_widget_show (button);

    gtk_widget_show (box1);
    gtk_widget_show (pbar);
    gtk_widget_show (window);

    int timer = gtk_timeout_add(100, progress_timeout, pbar);

//--------------------------------------------------------------------------
    
    int from_fd,to_fd; 
	int bytes_read,bytes_write; 
	char buffer[BUFFER_SIZE];   //设定一个缓冲区
	char *ptr; 
	if(argc!=4)    //五个参数
	{ 
		fprintf(stderr,"Usage:%s fromfile tofile\n\a",argv[0]); 
		return(-1); 
	} 
	/* 打开源文件 */ 
	if((from_fd=open(argv[1],O_RDONLY))==-1) 
	{ 
		fprintf(stderr,"Open %s Error:%s\n",argv[1],strerror(errno)); 
		return(-1); 
	} 
	/* 创建目的文件 */ 
	if((to_fd=open(argv[2],O_WRONLY|O_CREAT,S_IRUSR|S_IWUSR))==-1) 
	{ 
		fprintf(stderr,"Open %s Error:%s\n",argv[2],strerror(errno)); 
		return(-1); 
	} 

	/* 以下代码是一个经典的拷贝文件的代码 */ 
	while(bytes_read=read(from_fd,buffer,BUFFER_SIZE)) 
	{ 
		/* 一个致命的错误发生了 */ 
		if((bytes_read==-1)&&(errno!=EINTR)) break; 
		else if(bytes_read>0) 
		{ 
			ptr=buffer; 
			while(bytes_write=write(to_fd,ptr,bytes_read)) 
			{ 
				/* 一个致命错误发生了 */ 
				if((bytes_write==-1)&&(errno!=EINTR))break; 
				/* 写完了所有读的字节 */ 
				else if(bytes_write==bytes_read) break; 
				/* 只写了一部分,继续写 */ 
				else if(bytes_write>0) 
				{ 
					ptr+=bytes_write; 
					bytes_read-=bytes_write; 
				} 
			} 
			/* 写的时候发生的致命错误 ????*/ 
			if(bytes_write==-1)break; 
		} 
	} 
	close(from_fd); 
	close(to_fd); 
    a = 1;
    
//--------------------------------------------------------------------------


    gtk_main ();

    return 0;
}