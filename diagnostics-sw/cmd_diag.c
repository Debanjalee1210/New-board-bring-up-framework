#include "DiagTypes.h"

#include <common.h>

#include <command.h>

static int runall(cmd_tbl_t * cmdtp, int flag, int argc, char * const argv[]){
int time=1,time1=1,current_loop,pass=0,fail=0,temp[6],f=0;
if(argc > 0){
time1=Atoi(argv[1]);
}
for(int i=0;i<time1;i++){
temp[0]=do_Diagtest(time);
temp[1]=do_memory_test(time);
temp[2]=do_pmic_test(time);
temp[3]=do_ping(time);
temp[4]=do_rtctest(time);
temp[5]=do_i2c_probe(time);
for(int j=0;j<6;j++)
{
if(temp[j]!=1){
f=1;
break;
}
}
if(f==1){
fail++;
}
else{
pass++;
}
f=0;

printf("\n# test iteration : %d \n",time1);
printf("# TEST PASSED  : %d \n",pass);
printf("# TEST FAILED  : %d \n",fail);
}
}

static int runtest(cmd_tbl_t * cmdtp, int flag, int argc, char * const argv[]){
if(argc<2)
{
printf("\n diagtest runtest 1 [TO RUN I2C INTERFACE TEST]\n diagtest runtest 2 [TO RUN MEMORY TEST]\n diagtest runtest 3 [TO PING_smsc95xx_eth TEST ]\n diagtest runtest 4 [TO RUN RTC TEST]\n diagtest runtest 5 [TO RUN PMIC TEST]\n diagtest runtest 6 [TO RUN eeprom test]\n");
return 0;
}
int s,time=1;
s=Atoi(argv[1]);
if(argc>2){
time=Atoi(argv[2]);
}
if(time<1)
{
time=1;
}
switch(s)
{
case 1:
	do_i2c_probe(time);
	break;
case 2:
	do_memory_test(time);
	break;
case 3:
	do_ping(time);
	break;
case 4:
	do_rtctest(time);
	break;
case 5:
	do_pmic_test(time);
	break;
case 6:
	do_Diagtest(time);
	break;
	
default:
	printf("Enter test ID is not present");
	break;
}
return 0;
}
static int listall(cmd_tbl_t * cmdtp, int flag, int argc, char * const argv[])
{
printf("\n  1 TO RUN I2C INTERFACE TEST\n  2 TO RUN MEMORY TEST\n  3 TO PING_smsc95xx_eth TEST \n  4 TO RUN RTC TEST\n  5 TO RUN PMIC TEST\n  runtest 6 TO RUN eeprom test\n");
}
static cmd_tbl_t cmd_Diagtest_sub[] ={
U_BOOT_CMD_MKENT(listall,0,1,listall,"",""),
U_BOOT_CMD_MKENT(runtest,1,1,runtest,"",""),
U_BOOT_CMD_MKENT(runall,0,1,runall,"",""),
};

static int do_boarddiag (cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[]) {
    int retval = 0;

	cmd_tbl_t *c;
	printf ("\n   ==== Board Diagnostics ====\n\n");


	if (argc < 2)
		return CMD_RET_USAGE;

	argc--;
	argv++;

	c = find_cmd_tbl(argv[0], &cmd_Diagtest_sub[0], ARRAY_SIZE(cmd_Diagtest_sub));

	if (c)
		return c->cmd(cmdtp, flag, argc, argv);
	else
		return CMD_RET_USAGE;

}
int Atoi(char *str)
{
    if (*str == '\0')
       return 0;
 
    int res = 0;		// Initialize result
    int sign = 1;		// Initialize sign as positive
    int i = 0;			// Initialize index of first digit
 
    
 
    for (; str[i] != '\0'; ++i)
    {
        if ( str[i] <= '0' || str[i] >= '9')	// If string contain character it will terminate
            return 0; 
            
        res = res*10 + str[i] - '0';
    }
 
    return res;
}






U_BOOT_CMD(boarddiag, CONFIG_SYS_MAXARGS, 0, do_boarddiag, "Board diagnostics",
        "   [args...]\n"
        "   list           -- List available tests\n"
	"   run <test_num> -- Run test by test number specified in the list\n"
        "   runAll         -- Run all tests\n"
        "                loop <times> -- Sets the loop to execute the test number of times. \n"
		);

