// module: mt7915.ko
// function: AutoChSelUpdateChannel @ 0x22e64
// size: 144 bytes
//

void AutoChSelUpdateChannel(undefined4 param_1,undefined4 param_2,int param_3,int param_4)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  
  if (param_3 == 0) {
    *(char *)(param_4 + 0x1a) = (char)param_2;
    iVar1 = wlan_config_get_ext_cha(param_4);
    iVar2 = ExtChCheck(param_1,param_2,iVar1,param_4);
    if (iVar2 == 0) {
      if (iVar1 == 3) {
        uVar3 = 1;
      }
      else {
        uVar3 = 3;
      }
      wlan_config_set_ext_cha(param_4,uVar3);
    }
  }
  else {
    *(char *)(param_4 + 0x1a) = (char)param_2;
  }
  if (2 < DebugLevel) {
    printk("%s(): Update channel for wdev for this band PhyMode = %d, Channel = %d\n",
           "AutoChSelUpdateChannel",*(undefined2 *)(param_4 + 0x18),*(undefined1 *)(param_4 + 0x1a))
    ;
    return;
  }
  return;
}

