// module: mt7915.ko
// function: WLAN_Set_BeaconLostResetSw @ 0x15a2cc
// size: 120 bytes
//

undefined4 WLAN_Set_BeaconLostResetSw(int param_1,int param_2)

{
  int iVar1;
  undefined1 uVar2;
  
  if (param_1 == 0 || param_2 == 0) {
    return 0;
  }
  uVar2 = simple_strtol(param_2,0,10);
  iVar1 = DebugLevel;
  *(undefined1 *)(param_1 + 0xa7d167) = uVar2;
  if (2 < iVar1) {
    printk("Beacon Check Flag=%d\n",uVar2);
    return 1;
  }
  return 1;
}

