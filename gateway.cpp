#include <iostream>
#include "gateway.h"
using namespace std;

#define RETURN_SUCCESS 1
#define RETURN_FAIL 0
/* constructor */
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
//					int pid = fork();
//					if(pid < 0 )
//					{
//						cout<<"error in fork"<<endl;
//					}
//					else if (pid == 0)
					{
//						cout<<"in Process"<<endl;
//						close(m_sockfd);
						Process_Request(m_newsockfd);
						close(m_newsockfd);
//						sleep(1);
//						exit(0);	
					}
//					else
					{
						//close(m_newsockfd);
						//cout<<"close socket"<<endl;
					}	
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
	n = read(sock,reinterpret_cast<Dev_Meta_Data*>(&tmp),sizeof(tmp));
	if (n < 0)
	{
		cout<< "ERROR reading from socket"<<endl;
	}
	else
	{
//		cout<<"in process="<<tmp.value<<endl;
		if(m_record.empty())
		{
			rec.dev_data.device_id = tmp.device_id;
			rec.dev_data.value = tmp.value;
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
//					cout<<"found device id"<<endl;
					found = true;
					ptr->dev_data.value = tmp.value;
					ptr->data_count = ptr->data_count + 1;
					break;
				}
			}
			
			if( found != true )
			{
	                        rec.dev_data.device_id = tmp.device_id;
        	                rec.dev_data.value = tmp.value;
                	        rec.data_count = 1;
				m_record.push_back(rec);
//				cout<<"new device added"<<endl;
				unsigned int size = m_record.size();
//                        	cout<<"device id = "<<m_record[size -1].dev_data.device_id<<endl;
//                        	cout<<"Val="<<m_record[size -1].dev_data.value<<endl;
//                        	cout<<"count="<<m_record[size -1].data_count<<endl;

			}
							
		}	
	}		
}

void Gateway::Display_Record(void)
{
//	std::vector<Dev_Record>::iterator ptr;
	unsigned int size = m_record.size();
	for(uint n  = 0;n < size;n++)
	{
		cout<<"Device Id   = "<<m_record[n].dev_data.device_id<<endl;
		cout<<"Param Value = "<<m_record[n].dev_data.value<<endl;
		cout<<"Param Count = "<<m_record[n].data_count<<endl;
		cout<<endl;
	}
	cout<<"Total Device connected = "<<m_record.size()<<endl;
	cout<<"Enter D or d to display device connected to server"<<endl;
		
}
