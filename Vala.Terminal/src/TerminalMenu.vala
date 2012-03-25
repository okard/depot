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

public class TerminalMenu : Menu
{
    public signal void on_new_tab();

    public TerminalMenu()
    {
        //new tab
        //new window
        //new instance
        //--------
        //set tab name
        //close tab
        //close window
        //--------
        //Copy
        //Paste
        //

        var nt = new MenuItem.with_label("new tab");
        nt.activate.connect((e) => on_new_tab());
        this.append(nt);

        var nw = new MenuItem.with_label("new window");
        this.append(nw);

        var ni = new MenuItem.with_label("new instance");
        this.append(ni);

        this.append(new SeparatorMenuItem());

        var stn = new MenuItem.with_label("set tab name");
        this.append(stn);

        this.append(new SeparatorMenuItem());

        var ct = new MenuItem.with_label("close tab");
        this.append(ct);

        var cw = new MenuItem.with_label("close window");
        this.append(cw);
        
        this.append(new SeparatorMenuItem());

        var copy = new MenuItem.with_label("Copy");
        this.append(copy);

        var paste = new MenuItem.with_label("Paste");
        this.append(paste);
        

        this.show_all();
    }
}