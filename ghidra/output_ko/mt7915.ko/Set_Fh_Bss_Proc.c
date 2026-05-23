// module: mt7915.ko
// function: Set_Fh_Bss_Proc @ 0x2b6d4
// size: 184 bytes
//

undefined4 Set_Fh_Bss_Proc(int *param_1,undefined4 param_2)

{
  char cVar1;
  byte bVar2;
  uint uVar3;
  
  cVar1 = os_str_tol(param_2,0,10);
  if ((*(int *)(*param_1 + 0x38) - 0x100U & 0xfffffeff) != 0) {
    return 0;
  }
  uVar3 = (uint)*(byte *)(*param_1 + 0x3c);
  bVar2 = *(byte *)((int)param_1 + uVar3 * 0x5834 + 0x2bb1a5);
  if (cVar1 == '\0') {
    bVar2 = bVar2 & 0xdf;
  }
  else {
    bVar2 = bVar2 | 0x20;
  }
  *(byte *)((int)param_1 + uVar3 * 0x5834 + 0x2bb1a5) = bVar2;
  if (0 < DebugLevel) {
    printk("%s %s wdev->MAPCfg.DevOwnRole 0x%x\n","Set_Fh_Bss_Proc",
           param_1[uVar3 * 0x160d + 0xadc92],
           *(undefined1 *)((int)param_1 + uVar3 * 0x5834 + 0x2bb1a5));
    return 1;
  }
  return 1;
}

