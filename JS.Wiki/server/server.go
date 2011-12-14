package main

import (
    "fmt"
    "json"
    "http"
)

//db: https://bitbucket.org/ww/cabinet/src

func main() {
    fmt.Printf("Starting http Server ... \n")
    
    http.Handle("/$db", http.HandlerFunc(handleDb))
    http.Handle("/", http.FileServer(http.Dir("web/")))
    
    err := http.ListenAndServe("127.0.0.1:8080", nil)
    if err != nil {
       fmt.Printf("ListenAndServe Error :" + err.String())
    }
}


func handleDb(w http.ResponseWriter, req *http.Request) {

    if req.Method == "POST" {
        dec := json.NewDecoder(req.Body);
        var f interface{}
        dec.Decode(&f);
        m := f.(map[string]interface{})
        
        c := (m["cmd"]).(string)
        
        switch c {
        case "list": //get a list of pages
            fmt.Println("List Command");
            break;
        case "header": //get the header of a page
            fmt.Println("Header Command");
            break;
        case "content": //get content of a page
            fmt.Println("Content Command");
            break;
        case "update": //update content of a page
            fmt.Println("Update Command");
            break;
        //set //set a value of header of a page
        default:
            fmt.Println("Error Invalid Command");
        }
    }
    
    var res = make(map[string] interface{})
    res["status"] = "ok"
    
    //write content filestream
    //os.Open(inName, os.O_RDONLY, inPerm);
    
    var enc = json.NewEncoder(w)
    enc.Encode(res);

}
