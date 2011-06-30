/*
Copyright (c) 2011 okard

Permission is hereby granted, free of charge, to any person obtaining a copy 
of this software and associated documentation files (the "Software"), to deal 
in the Software without restriction, including without limitation the rights 
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell 
copies of the Software, and to permit persons to whom the Software is 
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN 
THE SOFTWARE.
*/

using Gtk;


/**
* Terminal Application
*/
public class TerminalApplication : Gtk.Application
{
    /// Application DBUS Id
    public static const string AppId = "org.gtk.vala.vaterm"; 

    /// CSS Provider
    private CssProvider cssProvider;
    
    /**
    * Ctor
    */
    public TerminalApplication(string appid, ApplicationFlags flag)
    {
        Object( application_id: appid, flags: flag);
        
        //Load CSS Style
        cssProvider = new CssProvider();
        try 
        {
            var file = File.new_for_path ("vaterm.css");
            cssProvider.load_from_file(file);
        }
        catch(Error e){  stderr.printf ("Error: %s\n", e.message);}
        
        //map events
        activate.connect(onActivate);
        
    }
    
    /**
    * On Application Activate
    */
    public void onActivate()
    {
        //required to handle here???
        Gdk.Display display = Gdk.Display.get_default();
        Gdk.Screen screen = display.get_default_screen();
        StyleContext.add_provider_for_screen (screen, cssProvider, STYLE_PROVIDER_PRIORITY_APPLICATION);
    
        //set up Terminal Window
        var window = new TerminalWindow(); 
        window.set_application(this);
        this.add_window(window);
        window.show_all();
    }
}


/**
* Main Function
*/
public static int main (string[] args) 
{
    //have to detect multiple instance here to set right app id
    var IsMultipleInstance = false;
    string appid = !IsMultipleInstance ? TerminalApplication.AppId : "%s.instance%x".printf(TerminalApplication.AppId ,new DateTime.now_utc().hash());
    var app = new TerminalApplication(appid, ApplicationFlags.FLAGS_NONE);
    
    return app.run(args);
}
