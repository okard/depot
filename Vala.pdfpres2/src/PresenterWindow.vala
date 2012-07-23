
using Gtk;
using Cairo;


namespace pdfpres
{
    /**
    * Presenter Window
    */
    public class PresenterWindow : Gtk.Window
    {
        private MainWindow mainWin;


        public PresenterWindow(MainWindow mainWin)
        {
            this.mainWin = mainWin;
            
            this.draw.connect(drawPdf);

        }

        //TODO Support drawing with pencil

        protected bool drawPdf(Cairo.Context cr)
        {
            var page =  mainWin.CurrentPage;
            if(page != null)
                return true;

            double pageWidth, pageHeight;
            page.get_size(out pageWidth, out pageHeight);

           
            page.render(cr);
            return true;
        }
    }


}