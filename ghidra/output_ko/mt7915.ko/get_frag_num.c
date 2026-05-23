// module: mt7915.ko
// function: get_frag_num @ 0xcd890
// size: 124 bytes
//

char get_frag_num(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  char cVar1;
  int iVar2;
  int extraout_r1;
  byte *local_28;
  undefined1 auStack_24 [4];
  undefined1 auStack_20 [8];
  int local_18;
  
  RTMP_QueryPacketInfo(param_3,auStack_20,&local_28,auStack_24);
  iVar2 = wlan_operate_get_frag_thld(param_2);
  if ((*local_28 & 1) == 0) {
    cVar1 = __aeabi_uidiv(local_18 + -6,iVar2 + -0x1c);
    __aeabi_uidivmod(local_18 + -6,iVar2 + -0x1c);
    if (extraout_r1 != 0) {
      cVar1 = cVar1 + '\x01';
    }
  }
  else {
    cVar1 = '\x01';
  }
  return cVar1;
}

