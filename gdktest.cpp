#include <stdlib.h>
#include <gdk/gdk.h>

void delete_window(GdkEvent *event);
void repaint_rect(GdkEventExpose *event);
void paint_window(GdkEventKey *event);
void main_event_loop();
GdkWindow* init_window();

int main(int argc, char **argv)
{
	gdk_init(&argc,&argv);
	gdk_window_show(init_window());
	main_event_loop();
	_exit(0);
}

void main_event_loop()
{
	GdkEvent *event; 
	while(1)
	{
		event = gdk_event_get();
		if(event == NULL)
			continue;
		switch(event->type)
		{
			case GDK_DELETE:
				{
					delete_window(event);
					break; 
				}
			case GDK_EXPOSE:
				{
					repaint_rect((GdkEventExpose *)event);
					break;
				}
			case GDK_KEY_PRESS:
				{
					paint_window((GdkEventKey *)event);
					break;
				}
			case GDK_MOTION_NOTIFY:
				break;
			case GDK_BUTTON_PRESS:
				break; 
			default:
				break;
		}
	}
}
GdkWindow* init_window()
{
	GdkWindowAttr *gwa = (GdkWindowAttr*)malloc(sizeof(GdkWindowAttr));
	gchar title[]="Gdk Test";
	gwa->title=title;
	gwa->event_mask=GDK_ALL_EVENTS_MASK;
	gwa->x=0;
	gwa->y=0;
	gwa->width=200;
	gwa->height=200;
	gwa->wclass=GDK_INPUT_OUTPUT;
	gwa->visual=gdk_visual_get_best();
	gwa->window_type=GDK_WINDOW_TOPLEVEL;
	gwa->cursor=gdk_cursor_new(GDK_ARROW);
	gwa->wmclass_name=NULL;
	gwa->wmclass_class=NULL;
	gwa->override_redirect=0;
	gwa->type_hint=GDK_WINDOW_TYPE_HINT_NORMAL;
	GdkWindow *window;	
	GdkRGBA *pcolor = (GdkRGBA*)malloc(sizeof(GdkRGBA));
	pcolor->red=0.4;
	pcolor->green=0.4;
	pcolor->blue=0.7;
	pcolor->alpha=1;
	window=gdk_window_new(NULL,gwa,GDK_WA_TITLE|GDK_WA_X|GDK_WA_Y );
	gdk_window_set_background_rgba(window,pcolor);
	return window;
}
void delete_window(GdkEvent *event)
{
	gdk_window_destroy(((GdkEventAny *)event)->window);
	_exit(0);
}

void repaint_rect(GdkEventExpose *event)
{
	printf("event->type: %d\n",event->type);
	gdk_window_begin_paint_region(event->window,event->region);
	gdk_window_end_paint(event->window);
}

void paint_window(GdkEventKey *event)
{
	gchar keyname[32]; 
	cairo_t *p; 
	g_strlcpy(keyname,gdk_keyval_name(event->keyval),sizeof(keyname));
	printf("key pressed: %s\n",keyname);
	if(!g_strcmp0(keyname,"p"))
	{

		p = gdk_cairo_create(event->window);
		cairo_set_source_rgb(p,0.7,0.9,0.5);
		cairo_set_line_width(p,10);
		cairo_move_to(p,100,100);
		cairo_line_to(p,200,200);
		cairo_stroke(p);
		cairo_destroy(p);
	}

}
