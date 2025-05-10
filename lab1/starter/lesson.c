// Indicated png or not
// Indicates dimensions
// Indicates any crc errors

// gcc _filename_ -o _outputFileName_

#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>


int main(int argc, char *arg[])
{
    printf("printing args\n ");
    for(int i=1;i<argc;i++)
    {
        printf("%s\n", arg[i]);
    }

    // Getting the file desitnation
    DIR *directoryPointer;

    // We will now tell it to check the directory:

    if(argc <=1 )
    {
        printf("Not enough arg");
    }
    else
    {
        directoryPointer = opendir(arg[1]);
        if(directoryPointer == NULL)
        {
            printf("no such directory");
            return 0;
        }
        
    }

    // Making a struct for each of those files:
    /*
    struct dirent {
        ino_t          d_ino;       // inode number
        off_t          d_off;       // offset to the next dirent
        unsigned short d_reclen;    // length of this record
        unsigned char  d_type;      // type of file (file, dir, etc.)
        char           d_name[256]; // filename (null-terminated string)
    };
    */

    printf("\n\n\nPart 2\n");
    struct dirent *p_dirent;


    // we are get each element in the directory
    while((p_dirent = readdir(directoryPointer)) != NULL)
    {
        //from struct we will now grab the dname
        char *fileName = p_dirent->d_name;
        
        if(fileName != NULL)
        {
            printf("%s\n", fileName);
        }
        else
        {
            printf("Empty \n");
            return 0;
        }
        
    }



    return 0;
}