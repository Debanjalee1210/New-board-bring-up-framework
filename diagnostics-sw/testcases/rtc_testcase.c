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

int do_rtctest(int loop)
{
for(int time=0;time<loop;time++){
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
	
	
	chip   = 0x68;
	addr   = 0x00;
	alen   = 1;
	length = 8;

	nbytes = length;
	do {
		unsigned char	linebuf[DISP_LINE_LEN];//copying remember
		unsigned char	*cp;

		linebytes = (nbytes > DISP_LINE_LEN) ? DISP_LINE_LEN : nbytes;
		i2c_set_bus_num(1);
		
		ptr = map_sysmem(addr1, size1);

		*((u8 *)ptr) =0x00000062;
		ptr1 = map_sysmem(addr2, size1);
		*((u8 *)ptr1) =0x00000062;
		ret = i2c_read(chip, addr, alen, linebuf, linebytes);
		if(ret){
		printf("\nRTC TEST RESULT : FAIL\n");
		return 0;	
		}
			cp = linebuf;
			printf("RTC TEST RESULT : PASS\n");
			for (j=0; j<linebytes; j++) {
      				printf("%02x ",*cp);
				cp++;
				
			}

		nbytes -= linebytes;
	} while (nbytes > 0);
}
return 1;

}


U_BOOT_CMD(rtc_test,5,1,do_rtctest,"Board Bring Up Test","");
