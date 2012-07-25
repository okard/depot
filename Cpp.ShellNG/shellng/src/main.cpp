
#include <stdlib.h>

extern "C" {
#include <linenoise.h>
}

#include <shellng/Shell.hpp>

using namespace sng;


void RequestInput(Shell& shell)
{
    char* line = linenoise(shell.getPrompt());
    shell.parse(line);
    free(line);
}


int main()
{
    Shell shell;
    //shell.RequestInput = &RequestInput;

    char *line;
    while((line = linenoise(shell.getPrompt())) != NULL) 
    {
        if (line[0] != '\0') 
        {
            shell.parse(line);
            linenoiseHistoryAdd(line);
        }
        free(line);
    }
    
    return 0;
}