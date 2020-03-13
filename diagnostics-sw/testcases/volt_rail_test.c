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
  
#define DISP_LINE_LEN	16





struct Record{
unsigned char data1[8];
};

struct Record data={0x3f,0x00,0x01,0xb1,0x80,0xb2,0x01,0x00}; 


int do_pmic_test(int loop)
{
i2c_set_bus_num(0);
for(int time=0;time<loop;time++){
	uint	chip;
	uint	addr, length;
	int alen;
	int	j, nbytes, linebytes;
	int ret;
	int count=0;
	
	chip   =0x24;
	addr   = 0x0000;
	alen   = 2;
	length = 16;

	nbytes = length;
	do {
		unsigned char	linebuf[DISP_LINE_LEN];//copying remember
		unsigned char	*cp;

		linebytes = (nbytes > DISP_LINE_LEN) ? DISP_LINE_LEN : nbytes;
		ret = i2c_read(chip, addr, alen, linebuf, linebytes);
			cp = linebuf;
			for (j=0; j<linebytes; j++) 
			{
				if(count<8)
				{
					if(!(*cp==data.data1[count])){
						printf("Res: voltage rail test Fail\n");
						
						return 0;
							}
				}
				
		

				cp++;
				count++;
				if(count==8)
					break;
			}
			if(count==8){
					printf("\nRes: voltage rail Pass\n");
					
					break;
			}
		nbytes -= linebytes;
	} while (nbytes > 0);
}
return 1;

}
U_BOOT_CMD(pmic_test,1,1,do_pmic_test,"voltage rail Test","help");

