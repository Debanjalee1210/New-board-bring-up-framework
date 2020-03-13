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





int do_i2c_probe(int loop)
{
int t;
for(int time=0;time<loop;time++){
int j;
int addr = -1;
int found = 0;
int ret,count=0;
i2c_set_bus_num(0);
puts ("I2c probe Testing\n");
for (j = 0; j < 128; j++) 
{
							
if ((0 <= addr) && (j != addr))
continue;
ret = i2c_probe(j);
					
if (ret == 0) 
{
puts ("Valid chip address:");
printf(" %02X\n", j);
if(j==0x24|| j==0x34 || j==0x50)
{
count++;
}

found++;
}
}
if(count==3)
{
printf("\n Result: I2c Probe test Passed\n");
t=1;
}
}
if(t == 1)
{
return 1;
}
return 0;
} 

 
U_BOOT_CMD(i2c_test,5,1,do_i2c_probe,"I2C Probe Test","help");
