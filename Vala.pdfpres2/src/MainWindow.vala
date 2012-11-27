using Gtk;
using Poppler;

namespace pdfpres
{

    public class MainWindow : Gtk.Window
    {
        //presentation context
        private Presentation presentation;
        
        //presenter window
        private PresenterWindow presWin;


        public MainWindow()
        {
            title = "Pdfpres";
            border_width = 10;
            window_position = WindowPosition.CENTER;
            set_default_size (350, 70);
            destroy.connect (Gtk.main_quit);

			//presentation
			presentation = new Presentation();
			//presenter window
            presWin = new PresenterWindow(presentation);
            presWin.show_all();


			//load presentation pdf
            var dia = new FileChooserDialog("test", this, FileChooserAction.OPEN,Stock.CANCEL, ResponseType.CANCEL, Stock.OPEN, ResponseType.ACCEPT);

            if (dia.run() == ResponseType.ACCEPT)   
                presentation.Load(dia.get_filename());
            dia.destroy ();            
        }

        static int main (string[] args) 
        {
            Gtk.init (ref args);
            
            var mainWin = new MainWindow();
            mainWin.show_all();

            Gtk.main ();
            return 0;
        }
    }
}




