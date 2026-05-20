// module: mt7915.ko
// function: mtf_dump_rmac_info_for_ICVERR @ 0x19c3b0
// size: 408 bytes
//

void mtf_dump_rmac_info_for_ICVERR(int param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = hc_get_hif_type(*(undefined4 *)(param_1 + 0xa797a0));
  if (iVar1 != 2) {
    return;
  }
  if (DebugLevel < 0) {
    return;
  }
  uVar2 = (uint)(*(int *)(param_2 + 0xc) << 0xe) >> 0x1e;
  printk("\tHTC/UC2ME/MC/BC = %d/%d/%d/%d\n",(uint)(*(int *)(param_2 + 0xc) << 0xd) >> 0x1f,
         uVar2 == 1,uVar2 == 2,uVar2 == 3);
  if (-1 < DebugLevel) {
    printk(", WlanIndex=%d",*(uint *)(param_2 + 4) & 0x3ff);
    if (DebugLevel < 0) {
      return;
    }
    printk(", SEC Mode=%d\n",(uint)(*(int *)(param_2 + 4) << 0xb) >> 0x1b);
    if (DebugLevel < 0) goto LAB_0019c4f8;
    printk("\tFCE Error(FC)=%d",(uint)(*(int *)(param_2 + 4) << 4) >> 0x1f);
    if (DebugLevel < 0) {
      return;
    }
    printk(", CM=%d",(uint)(*(int *)(param_2 + 4) << 8) >> 0x1f);
  }
  if (DebugLevel < 0) {
    return;
  }
  printk(", CLM=%d",(uint)(*(int *)(param_2 + 4) << 7) >> 0x1f);
  if (DebugLevel < 0) {
    return;
  }
  printk(", I=%d",(uint)(*(int *)(param_2 + 4) << 6) >> 0x1f);
LAB_0019c4f8:
  if ((-1 < DebugLevel) &&
     (printk(", T=%d",(uint)(*(int *)(param_2 + 4) << 5) >> 0x1f), -1 < DebugLevel)) {
    printk("\tFragment Frame(FRAG)=%d\n",(uint)(*(int *)(param_2 + 8) << 4) >> 0x1f);
    return;
  }
  return;
}

