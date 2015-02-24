---
title: Guidelines on markdown, pandoc and how to build pdf files
author: Niklas Blomqvist, Robin Gustafsson
geometry: margin=2.5cm
header-includes:
   - \DeclareUnicodeCharacter{00A0}{~}
---


#How to build the project (a md-file)
Just run 
    
    md2pdf <file name> [-spell] 
    # the -spell flag is optional, but enforces spell check


#Useful snippets

Create several newlines (blank):

    \vspace*{12\baselineskip} # creates 12 blank lines

Insert image:

    !["Image text"](path/to/img.png, "Alternative text")


Write a snippet of code with color coding:

*This:*

    ```c
    #include <stdio.h>
    
    int main(int argc, char** argv)
    {
        char world[5] = "world";
        printf("Hello %s", world);
        
        return 0;
    }
    ```


*Becomes:*


```c
#include <stdio.h>

int main(int argc, char** argv)
{
    char world[5] = "world";
    printf("Hello %s", world);
    
    return 0;
}
```

# Documentation on markdown and pandoc
http://johnmacfarlane.net/pandoc/demo/example9/pandocs-markdown.html
