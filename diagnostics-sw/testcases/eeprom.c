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

#define DISP_LINE_LEN	16


struct eeprom{
unsigned char header[4];
unsigned char revision[2];
unsigned char boardname[10];
};
struct eeprom e={{0xaa,0x55,0x33,0xee},{0x41,0x33},{0x33,0x35,0x42,0x4e,0x4c,0x54,0x30,0x30,0x43,0x30}};







int do_Diagtest(int loop)
{
	for(int time=0;time<loop;time++){
	ulong	addr1=0x44e10958;
int size1=1;
void *ptr = NULL;


	
	uint	chip;
	uint	addr, length;
	int alen;
	int	j, nbytes, linebytes;
	int ret;
	int count=0;
	unsigned int bus_arjun;
	
	chip   =0x50;
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
			for (j=0; j<linebytes; j++) {
				if(count<4)
				{
					if(!(*cp==e.header[count])){
						printf("Res: RunResult Fail");
						return 0;
}
					}
				if(count>=4 && count<6)
				{
					if(!(*cp==e.revision[count-4])){
						printf("Res: EEPROM RunResult Fail");
						return 0;
						}
					}
				if(count>=6 && count<16)
				{
					if(!(*cp==e.boardname[count-6])){
						printf("Res: EEPROM RunResult Fail");
						return 0;
						}
					}

				cp++;
				count++;
				if(count==16)
					break;
			}
			if(count==16){
					printf("\nRes: EEPROM RunResult Pass\n");
					return 1;
			}
		nbytes -= linebytes;
	} while (nbytes > 0);
}

}



		



U_BOOT_CMD(diagtest,5,1,do_Diagtest,"Board Bring Up Test"," ");

