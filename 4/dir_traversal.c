#define _XOPEN_SOURCE 500
#define _GNU_SOURCE

#include <ftw.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

static int display_info(const char *fpath, const struct stat *sb, int tflag, struct FTW *ftwbuf) // display info for evry level
{
    // check the type of the object
    char *type;
    if (tflag == FTW_D) //fpath is a directory
        type = "D";
    if (tflag == FTW_DP)
        type = "DP";
    if (tflag == FTW_DNR) //fpath is a directory which can't be read.
        type = "DNR";
    if (tflag == FTW_F) //fpath is a regular file
        type = "F";
    if (tflag == FTW_SL) //fpath is a symbolic link
        type = "SL";
    if (tflag == FTW_SLN) //fpath is a symbolic link pointing to a nonexistent file.
        type = "SLN";
    if (tflag == FTW_NS) 
        type = "NS";

    long inode = sb->st_ino; // take the inode number

    lstat(fpath, sb);         // give information on the soft link
    if (S_ISLNK(sb->st_mode)) // check if this if a soft link file
    {
        return 0; //continue
    }

    printf("%s  %ld  %s\n", type, inode, basename(fpath));

    return 0;
}

int main(int argc, char *argv[])
{
    int flags = 0;

    if (argc < 2)
    {
        printf("Invalid input\n");
        return 0;
    }
    char *name_dir = argv[1];

    if (nftw(name_dir, display_info, 20, flags) == -1) // return -1 if faild
    {
        printf("Not success\n");
        exit(EXIT_FAILURE);
    }
}
