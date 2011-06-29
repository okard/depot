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
using Vte;


/**
* Terminal Window
*/
public class TerminalWindow : Window
{
    //Tab Container
    private Notebook tabs;
    
    /**
    * Ctor
    */
    public TerminalWindow() 
    {
        this.title = "Terminal";
        this.set_has_resize_grip(false);
        
        this.key_press_event.connect(onKeyPress);
        
        this.tabs = new Notebook();
        tabs.page_added.connect((child, index) => { tabs.set_show_tabs(tabs.get_n_pages() > 1 ? true : false); });
        
        tabs.page_removed.connect((child, index) => {
            tabs.set_show_tabs(tabs.get_n_pages() > 1 ? true : false);
            
            if(tabs.get_n_pages() == 0)
                    this.hide();
            //close program? when not windows are open
        });
       
        
        //one shell
        addTerminalTab();
       
        var vbox = new VBox (true, 0);
        vbox.add(tabs);
        add(vbox);
    }
    
    /**
    * Key Event Handling
    */
    public bool onKeyPress(Gdk.EventKey event)
    {
        if (event.type != Gdk.EventType.KEY_PRESS)
            return false;
        
        if(event.is_modifier > 0)
            return false;
        
        //TODO shortcuts
        
        if((event.state & Gdk.ModifierType.CONTROL_MASK) == Gdk.ModifierType.CONTROL_MASK)
        {
            string key = Gdk.keyval_name(event.keyval);
            if(key == "t")
            {
                addTerminalTab();
                return true;
            }
            //Left, Right
            //
        }
        
        return false;
    }
    
    /**
    * Add a Terminal Tab
    */
    private void addTerminalTab()
    {        
        Terminal term = new Terminal();
        startShell(term);
        tabs.append_page(term, new Label("Terminal"));
        
        term.child_exited.connect(() => {
            tabs.remove(term);
        });
            
            
        tabs.show_all();
    }
    
    /**
    * Start a Shell at terminal
    */
    private void startShell(Terminal term)
    {
        //public bool fork_command_full (Vte.PtyFlags pty_flags, string? working_directory, [CCode (array_length = false)] string[] argv, [CCode (array_length = false)] string[]? envv, GLib.SpawnFlags spawn_flags, [CCode (delegate_target_pos = 6.5)] GLib.SpawnChildSetupFunc? child_setup, out GLib.Pid? child_pid) 
        
        string shell = Vte.get_user_shell();
        //argv rest?
        //enviroment
        //working directory
        //"/usr/bin/lua" python ruby?
        //GLib.Environment.get_home_dir() 
        //GLib.Environment.get_current_dir() 
        
        try
        {
        term.fork_command_full(PtyFlags.DEFAULT, //Vte.PtyFlags
                               null,             // working_directory,
                               {shell},          //argv
                               null,             //envv
                               GLib.SpawnFlags.DO_NOT_REAP_CHILD, //GLib.SpawnFlags
                               null, //GLib.SpawnChildSetupFunc
                               null  //out GLib.Pid? child_pid
                               );
        }
        catch(Error e)
        {
            stderr.printf ("Error: %s\n", e.message);
        }
    }
    
}

/**
* Main Function
*/
public static int main (string[] args) 
{
    Gtk.Application app = new Gtk.Application("org.gtk.vala.vaterm", ApplicationFlags.FLAGS_NONE);
   
    //look for existing process?
    //send message to open a new window?
    
    //read config
    
    CssProvider cssProvider = new CssProvider();
    
    //TODO fix vterm.css location
    try {cssProvider.load_from_file(File.new_for_path ("vterm.css"));}
    catch(Error e){  stderr.printf ("Error: %s\n", e.message);}
    
    //on app activate
    app.activate.connect(() =>
    {
        //required to handle here???
        Gdk.Display display = Gdk.Display.get_default();
        Gdk.Screen screen = display.get_default_screen();
        StyleContext.add_provider_for_screen (screen, cssProvider, STYLE_PROVIDER_PRIORITY_APPLICATION);
    
        //set up Terminal Window
        var window = new TerminalWindow(); 
        window.set_application(app);
        window.show_all();
        
    });
    
    return app.run(args);
}