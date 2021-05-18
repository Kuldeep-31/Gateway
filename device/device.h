#ifndef DEVICE_H
#define DEVICE_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>

#define PORT 49153 

/*  structure to send device data */
typedef struct dev_data{
        std::string device_id;
        float param_value;
}Dev_Meta_Data;

/* Class to send device data to gateway*/
class Device
{
public:
        /* Constructor */
        Device();

        /* Connect Gateway*/
        int Connect_Server(void);

        /* Send periodic data to gateway */
        int Send_Data(int sock,std::string dev_id,float val);

        /* Return socket descriptor */
        int Get_Sockfd(void);
private:
        int m_device_sockfd;
        struct sockaddr_in  m_dev_addr;
        Dev_Meta_Data dev_data;
};
#endif
