
using Gtk;
using Cairo;


namespace pdfpres
{
    /**
    * Presenter Window
    */
    public class PresenterWindow : Gtk.Window
    {
        private Presentation presentation;
        
        
        //draw context for overlays
        private Cairo.Surface surface;


        public PresenterWindow(Presentation presentation)
        {
            this.presentation = presentation;
            
            this.draw.connect(drawPdf);
            
            //events for drawing
            
            
			//this.get_screen();
			//this.set_screen();
			//Screen.get_height () 
            
        }
        
        //motion_notify_event
        //gdk_window_get_pointer()  GDK_POINTER_MOTION_HINT_MASK to gtk_widget_set_events().
        // gtk_widget_queue_draw_area (widget, x - 3, y - 3, 6, 6);
        //button_press_event_cb 
        
        
        private void NewPage()
        {
			//read from memory?
			//save in list
			surface = new Cairo.ImageSurface(Cairo.Format.ARGB32, 800,600);
		}
        

        //TODO Support drawing with pencil

        protected bool drawPdf(Cairo.Context cr)
        {
            var page =  presentation.CurrentPage;
            if(page != null)
                return true;


			//create right scaling
            double pageWidth, pageHeight;
            page.get_size(out pageWidth, out pageHeight);
            
            //this.get_size (out int width, out int height) 

           
            page.render(cr);
            
            //draw image overlay
            //scale to image overlay
            cr.set_source_surface(surface, 0, 0);
            cr.paint();
            
            
            return true;
        }
    }


}
