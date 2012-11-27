using Gtk;
using Poppler;

namespace pdfpres
{
	/**
	* Wrapper Class around Presentation
	*/
	public class Presentation
    {
		//poppler pdf doc
        private Poppler.Document pdfDoc;
        
        //current page of pdf
        private int pdfPageIndex = 0;
		
		
		public void Load(string filename)
        {
            if(pdfDoc != null)
            {
                pdfDoc = null;
            }

            //try
            try 
            {
				pdfDoc = new Poppler.Document.from_file(Filename.to_uri(filename), null);
			}
			catch(GLib.ConvertError exc)
			{
			}
			catch(GLib.Error exc)
			{
			}
			finally
			{
			}
        }
        
        public void SetPage(int page)
        {
			pdfPageIndex = page < 0 ? 0 : page >= pdfDoc.get_n_pages() ? pdfDoc.get_n_pages()-1 : page; 	
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

		
	}
}
