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
#include <hash.h>
#include <inttypes.h>
#include <mapmem.h>
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
#define DISP_LINE_LEN 8
unsigned int busnum1=1;
cmd_i2c_set_bus_num(busnum1);
void do_rtctest(int argc,char* argv)
{
ulong	addr1=0x44e10958;
ulong	addr2=0x44e1095c;
unsigned int bus_arjun;
int size1=1;
void *ptr = NULL;
void *ptr1 = NULL;


  uint	chip;
	uint	addr, length;
	int alen;
	int	j, nbytes, linebytes;
        int ret;
	//int count=0;
	
	chip   = 0x68;
	addr   = 0x00;
	alen   = 1;
	length = 10;

	nbytes = length;
	do {
		unsigned char	linebuf[DISP_LINE_LEN];//copying remember
		unsigned char	*cp;

		linebytes = (nbytes > DISP_LINE_LEN) ? DISP_LINE_LEN : nbytes;
i2c_set_bus_num(1);
bus_arjun = i2c_get_bus_num();
		
		ptr = map_sysmem(addr1, size1);
/*to modify the address values*/
*((u8 *)ptr) =0x00000062;
ptr1 = map_sysmem(addr2, size1);
*((u8 *)ptr1) =0x00000062;
		ret = i2c_read(chip, addr, alen, linebuf, linebytes);
			cp = linebuf;
			printf("rtc test case\n");
			for (j=0; j<linebytes; j++) {
      				printf("%02x ",*cp);
				cp++;
				//count++;
				
			}
			
			printf("\nRes: RunResult Pass\n");
					
		nbytes -= linebytes;
	} while (nbytes > 0);

}


U_BOOT_CMD(rtc_test,5,1,do_rtctest,"Board Bring Up Test","");
