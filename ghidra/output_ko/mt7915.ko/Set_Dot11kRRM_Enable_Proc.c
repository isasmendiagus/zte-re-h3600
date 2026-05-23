// module: mt7915.ko
// function: Set_Dot11kRRM_Enable_Proc @ 0x21f504
// size: 212 bytes
//

undefined4
Set_Dot11kRRM_Enable_Proc(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  char cVar1;
  ushort uVar2;
  uint uVar3;
  
  uVar3 = (uint)*(byte *)(*param_1 + 0x3c);
  if (uVar3 < *(byte *)((int)param_1 + 0x2b7242)) {
    cVar1 = os_str_tol(param_2,0,10,(uint)*(byte *)((int)param_1 + 0x2b7242),param_4);
    *(bool *)((int)param_1 + (int)("%u-%02x:%02x:%02x:%02x:%02x:%02x" + uVar3 * 0x5834 + 0x11)) =
         cVar1 != '\0';
    if (cVar1 != '\0') {
      uVar2 = *(ushort *)(param_1 + uVar3 * 0x160d + 0xaecb5) | 0x1000;
    }
    else {
      uVar2 = *(ushort *)(param_1 + uVar3 * 0x160d + 0xaecb5) & 0xefff;
    }
    *(ushort *)(param_1 + uVar3 * 0x160d + 0xaecb5) = uVar2;
    UpdateBeaconHandler(param_1,param_1 + uVar3 * 0x160d + 0xadc92,2);
    return 1;
  }
  if (0 < DebugLevel) {
    printk("Unknow If index (%d)",uVar3);
    return 0xffffffff;
  }
  return 0xffffffff;
}

