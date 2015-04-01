#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
 
#include <net/if.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
 
#include <linux/can.h>
#include <linux/can/raw.h>
 
int main(int argc, char **argv)
{
	int s;
	int nbytes;
	struct sockaddr_can addr;
	struct can_frame frame;
	struct ifreq ifr;
 
	char *ifname = "can0";
 
	if((s = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0) {
		perror("Error while opening socket");
		return -1;
	}
 
	strcpy(ifr.ifr_name, ifname);
	ioctl(s, SIOCGIFINDEX, &ifr);
 
	addr.can_family  = AF_CAN;
	addr.can_ifindex = ifr.ifr_ifindex; 
 
	printf("%s at index %d\n", ifname, ifr.ifr_ifindex);
 
	if(bind(s, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		perror("Error in socket bind");
		return -2;
	}
 
 	if (argc == 1)
 	{
		frame.can_id  = 0x000;
		frame.can_dlc = 2;
		frame.data[0] = 0x81;
		frame.data[1] = 0x00;
	}
	else
	{
		switch (argc)
		{
			case 10:
				frame.data[7] = atoi(argv[9]);
			case 9:
				frame.data[6] = atoi(argv[8]);
			case 8:
				frame.data[5] = atoi(argv[7]);
			case 7:
				frame.data[4] = atoi(argv[6]);
			case 6:
				frame.data[3] = atoi(argv[5]);
			case 5:
				frame.data[2] = atoi(argv[4]);
			case 4:
				frame.data[1] = atoi(argv[3]);
			case 3:
				frame.data[0] = atoi(argv[2]);
			case 2:
				frame.can_id  = atoi(argv[1]);

			frame.can_dlc = (argc - 2);
		}
	}
 
 	if (frame.can_dlc > 8)
 	{
 		frame.can_dlc = 8;
 	}

	nbytes = write(s, &frame, sizeof(struct can_frame));
 
	printf("Wrote %d bytes\n", nbytes);
 
	return 0;
}