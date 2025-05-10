
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>



int main(int argc, char *argv[])
{
    if (argc==2)
    {
        FILE *imagePointer = fopen(argv[1],"rb");

        if(imagePointer == NULL)
        {
            printf("Problem opening image");
            return 1;
        }

    }
    else
    {
        printf("wrong inputs");
        return 1;    
    }
    return 0;
}