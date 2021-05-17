#include <iostream>
#include "gateway.h"
#include <pthread.h>

#define PORT 49153

using namespace std;

void *Display_Val_Count(void *arg)
{
	char ch;
	Gateway *tmp = reinterpret_cast<Gateway *>(arg);
	cout<<"Enter D or d to display device connected to server"<<endl;
	while(1)
	{
		cin>>ch;
		if(ch == 'd' || ch == 'D')
		{
			tmp->Display_Record();
		}		
		sleep(1);
	}
	pthread_exit(NULL);

}

int main(int argc, char* argv[])
{
	Gateway inst;
	pthread_t ptid;
	int rc;
	rc = pthread_create( &ptid, NULL, &Display_Val_Count,reinterpret_cast<Gateway *>(&inst));
	if(rc)
	{
		cout<<"error thread creation"<<endl;
	}
	inst.Create_Socket(PORT);
	pthread_exit(NULL);
	return 0;
}

