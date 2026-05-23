// module: mt7915.ko
// function: RcUpdateRepeaterEntry @ 0xabcb0
// size: 196 bytes
//

int RcUpdateRepeaterEntry(int param_1,undefined1 param_2)

{
  int iVar1;
  undefined1 local_e0 [4];
  int local_dc;
  undefined1 local_d8;
  undefined1 local_d7;
  undefined1 local_d6;
  
  iVar1 = *(int *)(*(int *)(param_1 + 0x18) + 0x4328);
  if (((*(uint *)(*(int *)(param_1 + 0x18) + 0xb58) & 0x20) != 0) &&
     (*(char *)(iVar1 + 0x79504d) != '\0')) {
    os_zero_mem(local_e0,200);
    local_e0[0] = *(undefined1 *)(iVar1 + 0x79504d);
    local_d6 = **(undefined1 **)(param_1 + 4);
    local_dc = local_dc + 1;
    local_d8 = 4;
    local_d7 = param_2;
    iVar1 = AsicSetDbdcCtrl(iVar1,local_e0);
    if (iVar1 != 0) {
      if (DebugLevel < 0) {
        return iVar1;
      }
      printk("%s(): Error for conifgure dbdc, ret = %d !\n","RcUpdateRepeaterEntry",iVar1);
      return iVar1;
    }
  }
  return 0;
}

