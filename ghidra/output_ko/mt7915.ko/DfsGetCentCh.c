// module: mt7915.ko
// function: DfsGetCentCh @ 0x23613c
// size: 400 bytes
//

uint DfsGetCentCh(undefined4 param_1,uint param_2,int param_3,undefined4 param_4)

{
  int iVar1;
  uint uVar2;
  
  uVar2 = param_2;
  if (param_3 != 0) {
    if (param_3 == 1) {
      iVar1 = N_ChannelGroupCheck(param_1,param_2,param_4);
      if (iVar1 != 0) {
        if ((((param_2 & 0xe7) == 0x24) || ((param_2 & 0xe7) == 100)) ||
           ((param_2 & 0xf7) == 0x95 || param_2 == 0x84)) {
          uVar2 = param_2 + 2 & 0xff;
        }
        else if ((((param_2 & 0xbf) == 0x30 || (param_2 & 0xaf) == 0x28) || (param_2 == 0x40)) ||
                (((param_2 & 0xf7) == 0x80 || ((param_2 + 0x67 & 0xf7) == 0)))) {
          uVar2 = param_2 - 2 & 0xff;
        }
        else {
          uVar2 = 0;
        }
        goto LAB_00236160;
      }
    }
    else if (param_3 == 2) {
      iVar1 = vht80_channel_group(param_1,param_2,param_4);
      if (iVar1 == 0) {
        uVar2 = 0;
      }
      else {
        uVar2 = vht_cent_ch_freq(param_2,1,1);
      }
      goto LAB_00236160;
    }
    if (DebugLevel < 0) {
      return 0;
    }
    printk("[%s]Error!Unexpected Bw=%d!!\n","DfsGetCentCh",param_3);
    uVar2 = 0;
  }
LAB_00236160:
  if (2 < DebugLevel) {
    printk("[%s]Control/Central Ch=%d/%d;Bw=%d\n","DfsGetCentCh",param_2,uVar2,param_3);
  }
  return uVar2;
}

