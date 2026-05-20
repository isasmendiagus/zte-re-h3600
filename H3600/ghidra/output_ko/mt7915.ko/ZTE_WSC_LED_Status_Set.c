// module: mt7915.ko
// function: ZTE_WSC_LED_Status_Set @ 0x15a4bc
// size: 172 bytes
//

void ZTE_WSC_LED_Status_Set(int param_1,int param_2,int param_3)

{
  char *pcVar1;
  
  if ((param_2 - 8U & 0xff) < 6) {
    *(char *)((int)&g_WPSLEDStatus + param_3) = (char)param_2;
  }
  switch(param_2 - 8U) {
  case 0:
    func_0x005f7090(0x3200,1);
    return;
  case 1:
    func_0x005f7090(0x3300,1);
    return;
  case 2:
    func_0x005f7090(0x3400,1);
    return;
  case 3:
    pcVar1 = "Set_WscBssid_Proc:: %02x:%02x:%02x:%02x:%02x:%02x\n" + param_1 + 0x28;
    pcVar1[0] = '\v';
    pcVar1[1] = '\0';
    pcVar1[2] = '\0';
    pcVar1[3] = '\0';
    RTMPSetTimer("Set_WscMode_Proc:: Set failed!!(Set_WscMode_Proc=%s)\n" + param_1,300000);
    func_0x005f7090(0x3500,1);
    return;
  case 4:
    func_0x005f7090(0x3100,1);
    return;
  default:
    return;
  }
}

