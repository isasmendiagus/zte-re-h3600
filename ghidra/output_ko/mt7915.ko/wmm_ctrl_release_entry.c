// module: mt7915.ko
// function: wmm_ctrl_release_entry @ 0xad1a4
// size: 352 bytes
//

void wmm_ctrl_release_entry(byte *param_1)

{
  undefined1 uVar1;
  int iVar2;
  char cVar3;
  int iVar4;
  
  if ((param_1 == (byte *)0x0) || (param_1[6] == 0)) {
    if (DebugLevel < 0) {
      return;
    }
    printk("%s(): Can\'t find HdevObj or Edca not required\n","wmm_ctrl_release_entry");
    return;
  }
  iVar2 = *(int *)(*(undefined1 **)(param_1 + 8) + 0x18);
  iVar4 = *(int *)(iVar2 + 0x4328);
  iVar2 = *(int *)(iVar2 + 0x1a0c) + (uint)param_1[5] * 0x28;
  if ((iVar2 + 4 != 0) && (*(char *)(iVar2 + 4) != '\0')) {
    if (2 < DebugLevel) {
      printk("%s(): ObjIdx=%d,WmmIdx=%d\n","wmm_ctrl_release_entry",*param_1);
    }
    uVar1 = *(undefined1 *)(iVar2 + 3);
    cVar3 = *(char *)(iVar2 + 1) + -1;
    *(char *)(iVar2 + 1) = cVar3;
    if (cVar3 == '\0') {
      os_zero_mem(iVar2 + 4,0x24);
      *(undefined1 *)(iVar2 + 4) = 0;
      *(undefined1 *)(iVar2 + 1) = 0;
      *(undefined1 *)(iVar2 + 3) = uVar1;
      *(undefined1 *)(iVar2 + 2) = 0;
      AsicSetEdcaParm(iVar4,iVar2,*(undefined4 *)(iVar4 + (uint)*param_1 * 4 + 0xc));
    }
    iVar2 = DebugLevel;
    param_1[5] = 0;
    param_1[6] = 0;
    if (iVar2 < 3) {
      return;
    }
    printk("Release a WMM for ObjIdx: %d\n",*param_1);
    return;
  }
  if (DebugLevel < 0) {
    return;
  }
  printk("%s(): Can\'t find Edca for rdev: %d, Obj: %d\n","wmm_ctrl_release_entry",
         **(undefined1 **)(param_1 + 8),*param_1);
  return;
}

