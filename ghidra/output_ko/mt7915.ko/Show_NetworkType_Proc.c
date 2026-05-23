// module: mt7915.ko
// function: Show_NetworkType_Proc @ 0xd60f0
// size: 164 bytes
//

undefined4 Show_NetworkType_Proc(int *param_1,char *param_2,size_t param_3)

{
  switch((char)param_1[*(int *)(*param_1 + 0x3c) * 0x84dec + 0xdc6ee]) {
  case '\0':
    snprintf(param_2,param_3,"\tAdhoc");
    return 0;
  case '\x01':
    snprintf(param_2,param_3,"\tInfra");
    return 0;
  case '\x02':
    snprintf(param_2,param_3,"\tAny");
    return 0;
  case '\x03':
    snprintf(param_2,param_3,"\tMonitor");
    return 0;
  default:
    sprintf(param_2,"\tUnknow Value(%d)");
    return 0;
  }
}

