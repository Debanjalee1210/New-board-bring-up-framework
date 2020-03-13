ifeq ($(CONFIG_ARCH_OMAP2PLUS),y)
obj-$(CONFIG_DIAGSW) += RAM_test.o
obj-$(CONFIG_DIAGSW) += i2c-test.o
obj-$(CONFIG_DIAGSW) += ping_test.o
obj-$(CONFIG_DIAGSW) += volt_rail_test.o
obj-$(CONFIG_DIAGSW) += eeprom.o
obj-$(CONFIG_DIAGSW) += rtc_testcase.o
else ifeq ($(CONFIG_TARGET_RPI_2),y)
obj-$(CONFIG_DIAGSW) += RAM_test.o
obj-$(CONFIG_DIAGSW) += ping_test.o

else

endif

