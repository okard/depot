using Gtk;
using Poppler;

namespace pdfpres
{

    public class MainWindow : Gtk.Window
    {
        //poppler pdf doc
        private Poppler.Document pdfDoc;
        
        //current page of pdf
        private int pdfPageIndex = 0;

        //presenter window
        private PresenterWindow presWin;


        public MainWindow()
        {
            title = "Pdfpres";
            border_width = 10;
            window_position = WindowPosition.CENTER;
            set_default_size (350, 70);
            destroy.connect (Gtk.main_quit);

            presWin = new PresenterWindow(this);
            presWin.show_all();


            var dia = new FileChooserDialog("test", this, FileChooserAction.OPEN,Stock.CANCEL, ResponseType.CANCEL, Stock.OPEN, ResponseType.ACCEPT);

            if (dia.run() == ResponseType.ACCEPT)   
                Load(dia.get_filename());
            dia.destroy ();

            
        }


        private void Load(string filename)
        {
            if(pdfDoc != null)
            {
                pdfDoc = null;
            }

            //try
            
            pdfDoc = new Poppler.Document.from_file(Filename.to_uri(filename), null);
        }


        /**
        * Return current page if a document is loaded
        */
        public Poppler.Page CurrentPage
        {
            owned get {
                if(pdfDoc != null)
                    return pdfDoc.get_page(pdfPageIndex);
                else
                    return null;
            }
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




