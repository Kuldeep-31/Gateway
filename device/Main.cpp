#include <iostream>
#include "device.h"

using namespace std;

int main(int argc, char *argv[])
{
	Device inst;
	std::string dev_id;
	float val = 0;
	float range = 50.0;
	if(argc != 2)
	{
		cout<<"Enter correct arguments"<<endl;
		cout<<"device device_id "<<endl;
		return -1;
	}
	else
	{
		while(1)
		{
			if( inst.Connect_Server() == 1 )
			{
				dev_id = argv[1];
				{
					srand(time(0));
					val = static_cast<float>(rand())/static_cast<float>(RAND_MAX)*range;
					cout<<"Connection successful="<<dev_id<<" ,val="<<val<<endl;
					int sock = inst.Get_Sockfd();
					if(inst.Send_Data(sock,dev_id,val)>1)
					{
						cout<<"Send data to server"<<endl;
						close(sock);
					}
					usleep(4000000);
				}
			}
			else
			{
				break;
			}
		}
	}
	return 0;
}
