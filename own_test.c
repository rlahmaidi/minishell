#include <unistd.h>
#include <stdio.h>


int main()
{
    int fd[2];
    int id;

    pipe(fd);
    id = fork();
    if(id == 0)
    {
        int x = 4;
        close(fd[0]);
        write(fd[1],&x,sizeof(int));
        close(fd[1]);
    }
    else
    {
        int y;
        close(fd[1]);
        read(fd[0],&y,sizeof(int));
        printf("%d",y);
        close(fd[0]);
    }
    return(0);
}