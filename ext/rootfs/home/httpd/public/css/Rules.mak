
CFLAGS  += -Wall $(DIR_INCLUDE) $(OSS_DIR_INCLUDE) $(DB_DIR_INCLUDE) $(EXPATLIB_DIR_INCLUDE) $(LUA_DIR_INCLUDE)
CFLAGS  += -I$(CSP_DIR_INCLUDE)
CFLAGS  += $(CSP_INTERFACE_DIR_INCLUDE)
CFLAGS  += -I$(ROOT_PATH)/lib/cmapi/include
CFLAGS  += -I$(ROOT_PATH)/lib/cfapi/include
CFLAGS  += -I$(ROOT_PATH)/lib/libcommon/include
CFLAGS  += -I$(ROOT_PATH)/include/common
CFLAGS  += -I$(ROOT_PATH)/include/csp/cmapi
CFLAGS  += -I$(ROOT_PATH)/include/csp/app
CFLAGS  += -I$(ROOT_PATH)/include/csp/oss
CFLAGS  += -I$(ROOT_PATH)/include
CFLAGS  += -I$(COMP_PATH)/include
CFLAGS += -I $(COMP_PATH)/ipv6/cfapi
CFLAGS += -I $(COMP_PATH)/ipv6/cmapi
