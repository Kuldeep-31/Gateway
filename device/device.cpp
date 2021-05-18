#include "device.h"
#include <iostream>

using namespace std;

#define RETURN_SUCCESS 1
#define RETURN_FAIL 0


Device::Device():m_device_sockfd(0),m_dev_addr()
{
}

int  Device::Connect_Server(void)
{
	int ret_status = RETURN_SUCCESS;
	m_device_sockfd = socket(AF_INET,SOCK_STREAM,0);
	if( m_device_sockfd < 0 )
	{
		cout<<"Client socket failed"<<endl;
		ret_status = RETURN_FAIL;
	}
	
	if( ret_status == RETURN_SUCCESS )
	{
		m_dev_addr.sin_family = AF_INET;
		m_dev_addr.sin_port = htons(PORT);
		
		if(inet_pton(AF_INET,"127.0.0.1",&m_dev_addr.sin_addr) < 0 )
		{	
			ret_status = RETURN_FAIL;
			cout<<"inet_pton failed"<<endl;
		}
		else
		{
			if(connect(m_device_sockfd,reinterpret_cast<struct sockaddr *>(&m_dev_addr),sizeof(m_dev_addr)) < 0 )
			{
				ret_status = RETURN_FAIL;
				cout<<"connect failed"<<endl;	
			}
			
		} 
	}
	
	return (ret_status);
}

int Device::Send_Data(int sock, std::string dev_id, float val)
{
	int ret_status = RETURN_SUCCESS;
	int len = dev_id.length();
	dev_data.device_id = dev_id;
	dev_data.param_value = val;
//	cout<<"val="<<dev_data.value;	
	if( (ret_status = send(sock,reinterpret_cast<int *>(&len),sizeof(int),0)) < 0)
	{
		ret_status =  RETURN_FAIL;
	}
	if( (ret_status == RETURN_SUCCESS)&&((ret_status = send(sock,dev_data.device_id.c_str(),len,0)) < 0))
	{
		ret_status =  RETURN_FAIL;
	}
	if( (ret_status == RETURN_SUCCESS)&&((ret_status = send(sock,reinterpret_cast<float *>(&dev_data.param_value),sizeof(float),0)) < 0))
	{
		ret_status =  RETURN_FAIL;
	}
	return(ret_status);
}

int Device:: Get_Sockfd(void)
{
	return(m_device_sockfd);
}

