// module: mt7915.ko
// function: WrapDfsSelectChannel @ 0x23595c
// size: 108 bytes
//

void WrapDfsSelectChannel(int param_1,int param_2)

{
  undefined1 uVar1;
  undefined4 uVar2;
  
  DfsSelectChannel(param_1,param_1 + 0x795130,param_2);
  if (*(char *)(param_1 + param_2 + 0x795134) == '\x06') {
    if (*(char *)(param_1 + 0x795133) == '\0') {
      uVar1 = *(undefined1 *)(param_1 + 0x795131);
    }
    else {
      uVar1 = *(undefined1 *)(param_1 + 0x795130);
    }
    uVar2 = vht_cent_ch_freq(uVar1,3,1);
    wlan_config_set_cen_ch_2_all(param_1 + 0xa7c558,uVar2);
    return;
  }
  return;
}

