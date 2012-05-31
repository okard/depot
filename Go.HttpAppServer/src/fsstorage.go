package main

import "io"


type fsstorage struct {
    dir string
}



func FSStorage(dir string) *fsstorage {
 
    return &fsstorage{dir}
}


func (fsstore fsstorage) Get(key string, writer io.Writer) (error) {
    //read from file
    return nil;
}

func (fsstore fsstorage) Set(key string, reader io.Reader) (error) {
    //write to file
    return nil;
}
