#include "serverfuncs.h"

/**
 * @brief Prints the name of server and the ip addresses of server
 * 
 */
void printNameAndIP()
{
    char name[256];
    gethostname(name, 256);
    printf("I am %s\n", name);
    
    struct ifaddrs *addrs, *tmp;
    getifaddrs(&addrs);
    tmp = addrs;

    while (tmp) 
    {
        if (tmp->ifa_addr && tmp->ifa_addr->sa_family == AF_INET)
        {
            struct sockaddr_in *pAddr = (struct sockaddr_in *)tmp->ifa_addr;
            printf("%s: %s\n", tmp->ifa_name, inet_ntoa(pAddr->sin_addr));
        }

        tmp = tmp->ifa_next;
    }

    freeifaddrs(addrs);
}
