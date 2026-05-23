// module: mt7915.ko
// function: tm_init @ 0x150918
// size: 84 bytes
//

void tm_init(int param_1)

{
  int iVar1;
  undefined1 *puVar2;
  
  iVar1 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(char *)(iVar1 + 0x15c) == '\0') {
    puVar2 = tm_tasklet_qm_ops;
    *(undefined1 **)("Get_RBIST_IQ_Data" + param_1 + 0x10) = tm_tasklet_qm_ops;
  }
  else {
    puVar2 = *(undefined1 **)("Get_RBIST_IQ_Data" + param_1 + 0x10);
  }
                    /* WARNING: Could not recover jumptable at 0x00150968. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)puVar2)(param_1);
  return;
}

