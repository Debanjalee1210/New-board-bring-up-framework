#include <common.h>
#include <bootretry.h>
#include <cli.h>
#include <command.h>
#include <console.h>
#include <dm.h>
#include <edid.h>
#include <environment.h>
#include <errno.h>
#include <i2c.h>
#include <malloc.h>
#include <asm/byteorder.h>
#include <linux/compiler.h>
#include <net.h>
#include <dm.h>
#include <mmc.h>
#include <sparse_format.h>
#include <image-sparse.h>
#include <dm/device-internal.h>
#include <dm/uclass-internal.h>
volatile unsigned int *address =(volatile unsigned int*)0x80000000;
#define PATTERN_1 0x55555555
#define number_of_bytes (1024)
void write_pattern();
void read_pattern();
int fail=0;


int do_memory_test(int loop)
{
for(int time=0;time<loop;time++){
write_pattern();
read_pattern();
}
if(fail==1)
	return 0;

return 1;
}



void write_pattern()
{
	volatile unsigned int *r=(volatile unsigned int*)address;
	int i=0;
	while(i< (number_of_bytes)/4)
	{
		*r=PATTERN_1;
		r++;
		i++;
	}
}
void read_pattern()
{
	int i=0;
	volatile unsigned int *r=(volatile unsigned int*)address;
	while(i<(number_of_bytes)/4)
	{
		if(*r!=PATTERN_1){
			printf("Res: RAM TEST Run Result Fail\n");
			fail=1;
			break;
		}
		r++;
		i++;
	}
	if(i==(number_of_bytes)/4)
	{
		printf(" Res: RAM TEST  Run Result Pass\n");
		
	}
}
U_BOOT_CMD(Memory_test,5,1,do_memory_test,"Memory pattern Test","help");
