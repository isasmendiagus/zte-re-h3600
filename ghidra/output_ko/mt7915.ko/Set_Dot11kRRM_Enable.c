// module: mt7915.ko
// function: Set_Dot11kRRM_Enable @ 0x2205b8
// size: 208 bytes
//

undefined4 Set_Dot11kRRM_Enable(int *param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  ushort uVar1;
  uint uVar2;
  int *piVar3;
  
  uVar2 = (uint)*(byte *)(*param_1 + 0x3c);
  if (uVar2 < *(byte *)((int)param_1 + 0x2b7242)) {
    *(bool *)((int)param_1 + (int)("%u-%02x:%02x:%02x:%02x:%02x:%02x" + uVar2 * 0x5834 + 0x11)) =
         param_2 != 0;
    if (param_2 != 0) {
      uVar1 = *(ushort *)(param_1 + uVar2 * 0x160d + 0xaecb5) | 0x1000;
    }
    else {
      uVar1 = *(ushort *)(param_1 + uVar2 * 0x160d + 0xaecb5) & 0xefff;
    }
    *(ushort *)(param_1 + uVar2 * 0x160d + 0xaecb5) = uVar1;
    piVar3 = param_1 + uVar2 * 0x160d;
    ApUpdateCapabilityAndErpIe(param_1,piVar3 + 0xadc92,uVar1,piVar3,param_4);
    UpdateBeaconHandler(param_1,piVar3 + 0xadc92,2);
    return 0;
  }
  if (0 < DebugLevel) {
    printk("Unknow If index (%d)",uVar2);
    return 1;
  }
  return 1;
}

