// module: mt7915.ko
// function: ZTE_Get_ChannelUtilization @ 0x156a90
// size: 196 bytes
//

int ZTE_Get_ChannelUtilization(undefined4 param_1,uint param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  byte local_1c [4];
  
  uVar4 = param_2 & 0xff;
  local_1c[0] = 0;
  local_1c[1] = 0;
  local_1c[2] = 0;
  local_1c[3] = 0;
  iVar1 = Get_OBSS_AirTime(param_1,uVar4);
  iVar2 = Get_My_Tx_AirTime(param_1,uVar4);
  iVar3 = Get_My_Rx_AirTime(param_1,uVar4);
  if (iVar1 == 0) {
    uVar4 = (uint)local_1c[param_2];
  }
  else {
    uVar4 = (uint)((int)((ulonglong)(uint)(iVar1 * 100) * 0x431bde83 >> 0x20) << 6) >> 0x18;
  }
  if (iVar3 == 0 && iVar2 == 0) {
    return local_1c[param_2 + 2] + uVar4;
  }
  return ((uint)((int)((ulonglong)(uint)((iVar3 + iVar2) * 100) * 0x431bde83 >> 0x20) << 6) >> 0x18)
         + uVar4;
}

