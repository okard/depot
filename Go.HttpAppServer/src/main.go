package main

import (
    "fmt"
    "net/http"
    "os"
    "io"
)

const Port = 8080;
const Host = "localhost";
const StoragePath = "store/";

var rootDir string = ".";

/**
* Storage Interface
*/
type Storage interface {
    Set(key string, reader io.Reader) (error)
    Get(key string, writer io.Writer) (error)
}

//type Reader interface 
//type Writer interface

/**
* Handler Function
*/
func storageHandler(w http.ResponseWriter, r *http.Request) {
    
    var s Storage = FSStorage(".");
    s.Get("test", nil);
    s.Set("test", nil);
    //Method post/get
    //assert r.URL.Path length = 2 , listing, (1==$storage)
    //join rootdir StoragePath
    //seperate file?
    fmt.Fprintf(w, "Method: %s Url: %s", r.Method, r.URL.Path[1:])
}


/**
* Main Function
*/ 
func main() {
    fmt.Println("HttpAppServer");
    
    //get arg0 for dir
    //app.conf
    
    //get current working directory
    pwd, err := os.Getwd();
    if err != nil {
        fmt.Println(err);
    }
    
    dir := http.Dir(pwd);
    
    fmt.Println(dir);

    http.Handle("/", http.FileServer(dir))
    http.HandleFunc("/$storage/", storageHandler);
    http.ListenAndServe("127.0.0.1:8080", nil);
}