package main

import (
    "io"
    "fmt"
    "json"
    "http"
    //"mime"
)

//db: https://bitbucket.org/ww/cabinet/src

/**
* Main Function
*/
func main() {
    fmt.Printf("Starting http Server ... \n")


    http.Handle("/$sys", http.HandlerFunc(handleSys));    
    http.Handle("/$db", http.HandlerFunc(handleDb))

    //internal webserver should be disabled
    http.Handle("/", http.FileServer(http.Dir("web/")))
    
    err := http.ListenAndServe("127.0.0.1:8080", nil)
    if err != nil {
       fmt.Printf("ListenAndServe Error :" + err.String())
    }
}

/**
* System Handler
*/
func handleSys(w http.ResponseWriter, req *http.Request) {
    //parse url
    // /$sys/login is a login action
    //set session cookie in w.Header()
    //func SetCookie(w ResponseWriter, cookie *Cookie)
}


/**
* DB Handler
*/
func handleDb(w http.ResponseWriter, req *http.Request) {

    //for multi user and session handling
    //req.Cookie("name")

    //Only POST Requests are allowed
    if req.Method != "POST" {
        w.WriteHeader(http.StatusBadRequest);
        io.WriteString(w, "<h1>Bad Request</h1>");
        return;
    }

    //parse command
    dec := json.NewDecoder(req.Body);
    var f interface{}
    dec.Decode(&f);
    m := f.(map[string]interface{})
    
    c := (m["cmd"]).(string)
    
    //look for db command
    switch c {
    //get a list of pages "name", "desc", "id"
    case "list": 
        
        fmt.Println("List Command :", req.Host);
        break;

    //create a new page return ("id",)
    case "new":
        break;
    
    //get the header of a page
    case "header": 
        fmt.Println("Header Command");
        break;
    
    //get content of a page
    case "content": 
        fmt.Println("Content Command");
        break;

    //update content of a page
    case "update": 
        fmt.Println("Update Command");
        break;

    //set //set a value of header of a page
    default:
        fmt.Println("Error Invalid Command");
    }
    
    //response json object
    var res = make(map[string] interface{})
    res["status"] = "ok"
    
    //Prepare Header
    w.Header().Set("Access-Control-Allow-Origin", "*");
    w.Header().Set("Content-Type", "application/json")
    w.WriteHeader(http.StatusOK);
    
    var enc = json.NewEncoder(w)
    enc.Encode(res);

}

/*
Notices:
    //write content filestream
    //os.Open(inName, os.O_RDONLY, inPerm);

*/
