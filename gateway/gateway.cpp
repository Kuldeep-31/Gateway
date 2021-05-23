#include <iostream>
#include "gateway.h"
using namespace std;

#define RETURN_SUCCESS 1
#define RETURN_FAIL 0

Gateway::Gateway():m_sockfd(0),m_newsockfd(0),m_port(0),m_serv_addr(),m_cli_addr(),m_clilen(0),m_record()
{
	
}


int  Gateway::Create_Socket(int port_num)
{
	int ret_status = RETURN_SUCCESS;
	m_sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if( m_sockfd < 0 )
	{	
		ret_status = RETURN_FAIL;
		cout<<"Error socket failed"<<endl;
	}
	
	if (ret_status == RETURN_SUCCESS )
	{
		m_port = port_num;
		m_serv_addr.sin_family = AF_INET;
     		m_serv_addr.sin_addr.s_addr = INADDR_ANY;
     		m_serv_addr.sin_port = htons(m_port);
		if (bind(m_sockfd,reinterpret_cast< struct sockaddr *>(&m_serv_addr),sizeof(m_serv_addr)) < 0)
		{
			ret_status = RETURN_FAIL;
			cout<<"Bind failed"<<endl;
		}
		else
		{
			listen(m_sockfd,5);
     			m_clilen = sizeof(m_cli_addr);
			while(1)
			{
				m_newsockfd = accept(m_sockfd,reinterpret_cast<struct sockaddr *>( &m_cli_addr), &m_clilen);
				if(m_newsockfd < 0 )
				{
					ret_status = RETURN_FAIL;
					cout<<"accept failed"<<endl;
				}
				else
				{
					Process_Request(m_newsockfd);
					close(m_newsockfd);
				}
				
			}
		}
	
	}
	return(ret_status);
}

void  Gateway::Process_Request(int sock)
{
	int n;
	Dev_Meta_Data tmp = {};
	Dev_Record rec = {};
	std::vector<Dev_Record>::iterator ptr;
	bool found = false;
	int len = 0;
	std::string str1;
	std::vector<char> name;
	float val;
	
	n = read(sock,reinterpret_cast<int*>(&len),sizeof(int));
	if(n>0)
	{
		name.resize(len,0);
		n = read(sock,&name[0],len);
	}
	if(n>0)
	{
		n = read(sock,reinterpret_cast<float*>(&val),sizeof(float));
		str1.assign(&name[0],len);
		tmp.device_id.assign(str1);
		tmp.param_value = val;
	}
	if (n < 0)
	{
		cout<< "ERROR reading from socket"<<endl;
	}
	else
	{
		if(m_record.empty())
		{
			rec.dev_data.device_id = tmp.device_id;
			rec.dev_data.param_value = tmp.param_value;
			rec.data_count = 1;
			m_record.insert(m_record.begin(),rec);

			if(m_record.empty())
			{
				cout<<"record empty"<<endl;
			}
		}
		else
		{
			for(ptr = m_record.begin();ptr < m_record.end();ptr++)
			{
				if(ptr->dev_data.device_id == tmp.device_id)
				{
					found = true;
					ptr->dev_data.param_value = tmp.param_value;
					ptr->data_count = ptr->data_count + 1;
					break;
				}
			}
			
			if( found != true )
			{
	                        rec.dev_data.device_id = tmp.device_id;
        	                rec.dev_data.param_value = tmp.param_value;
                	        rec.data_count = 1;
				m_record.push_back(rec);
				unsigned int size = m_record.size();

			}
							
		}	
	}		
}

void Gateway::Display_Record(void)
{
	unsigned int size = m_record.size();
	for(uint n = 0;n < size;n++)
	{
		cout<<"Device Id   = "<<m_record[n].dev_data.device_id<<endl;
		cout<<"Param Value = "<<m_record[n].dev_data.param_value<<endl;
		cout<<"Param Count = "<<m_record[n].data_count<<endl;
		cout<<endl;
	}
	cout<<"Total Device connected = "<<m_record.size()<<endl;
	cout<<"Enter D or d to display device connected to server"<<endl;
		
}
