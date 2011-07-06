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

using Posix;

/**
* Get Path of executable
*/
public static string exePath()
{
    //public static ssize_t readlink (string path, char[] buf) 
    var buf = new char[1024];
    
    var len = readlink("/proc/self/exe", buf);
    
    //TODO check len for errors
    
    var path = new StringBuilder.sized(len);
    path.append(Path.get_dirname((string)buf));
    path.append_c(Path.DIR_SEPARATOR);
    
    return path.str;
}

/**
* Search for a file in path hierachy
*/
public static File findFile(string file)
{
    
    
    File f = File.new_for_path(file);
    if(f.query_exists())
        return f;
    // 1. dir (symlink (/proc/self/exe)) + file (for testing and developing)
    // 2. ~/.conf/vaterm/file
    // 3. /etc/vaterm/ or /usr/share/apps ... ???????
        
    throw new Error(Quark.from_string("VaTerm Error"), 0, "No matching file found");
}