#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <iostream>
#include <malloc.h>
#include "../App.hpp"

int main()
{
    
    int sockfd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(sockfd < 0)
    {
        perror("socket");
        return -1;
    }
    struct sockaddr_in svr_addr;
    svr_addr.sin_family = AF_INET;
    svr_addr.sin_port = htons(19998);
    svr_addr.sin_addr.s_addr = inet_addr("192.168.40.131");
    int ret = connect(sockfd,(struct sockaddr*)&svr_addr,sizeof(svr_addr));
    if(ret < 0)
    {
        perror("connect");
        close(sockfd);
        return -1;
    }
    int count = 1;
    while(1)
    {
        char buf[1024] = {0};
        strcpy(buf,"i");
        ret = send(sockfd,buf,strlen(buf),0);
        if(ret < 0)
        {
            perror("send");
            close(sockfd);
            return -1;
        }
        printf("count = %d\n",count);
        count++;
        /*
        memset(buf,0,sizeof(buf));
        recv(sockfd,buf,sizeof(buf)-1,0);
        */
    }
    close(sockfd);
    return 0;
}
