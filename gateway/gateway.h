ifndef GATEWAY_H
#define GATEWAY_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <unistd.h>
#include <cstring>
#include <vector>

/* stucture to hold device data*/
typedef struct dev_data{
        unsigned int device_id;
        float param_value;
}Dev_Meta_Data;

/*structure to hold record in server */
typedef struct dev_record{
        Dev_Meta_Data dev_data;
        unsigned int data_count;
}Dev_Record;

/* Class to initialize socket and store devices param value */
class Gateway
{
public:
        /* constructor */
        Gateway();

        /* Create socket */
        int Create_Socket(int port_num);

        /* Process device data */
        void Process_Request(int sock);

        /* Display device data */
        void Display_Record(void);
private:
        int m_sockfd;
        int m_newsockfd;
        int m_port;
        socklen_t m_clilen;
        struct sockaddr_in m_serv_addr, m_cli_addr;
        std::vector<Dev_Record> m_record;
};
#endif
