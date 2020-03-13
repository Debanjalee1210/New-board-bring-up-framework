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
#define ip "10.144.172.133"
int do_ping(int loop)
{
int fail=0;
for(int time=0;time<loop;time++){
net_ping_ip = string_to_ip(ip);
net_loop(PING);
if (net_loop(PING) < 0) {
		printf("\nping failed; host %s is not alive\n Res: RunResult Fail\n", ip);
			fail=1;
	}
else{

	printf("\nhost %s is alive\n Ping Test pass\n Res: RunResult Pass", ip);
}
}
if(fail==1)
	return 0;
return 1;
}
U_BOOT_CMD(ping_test,5,1,do_ping,"ping-Test","");
