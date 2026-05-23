// module: mt7915.ko
// function: BndStrg_InsertEntry @ 0x9c8b0
// size: 528 bytes
//

undefined4 BndStrg_InsertEntry(int param_1,int param_2,int *param_3)

{
  undefined4 uVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  
  if ((*(byte *)(param_2 + 2) & 0x80) == 0) {
    _raw_spin_lock_bh(param_1 + 0x1014);
    uVar3 = (uint)*(byte *)(param_2 + 2);
    iVar5 = param_1 + uVar3 * 0x18;
    iVar2 = iVar5 + 0x14;
    if (*(char *)(iVar5 + 0x14) == '\0') {
      __memzero(iVar2,0x18);
      iVar4 = param_1 + (uVar3 + 1) * 0x18;
      *(undefined4 *)(iVar4 + 4) = *(undefined4 *)(param_2 + 0xc);
      *(undefined2 *)(iVar4 + 8) = *(undefined2 *)(param_2 + 0x10);
      *(undefined4 *)(iVar5 + 0x18) = *(undefined4 *)(param_2 + 0x38);
      *(undefined1 *)(iVar4 + 10) = *(undefined1 *)(param_2 + 7);
      *(undefined1 *)(iVar5 + 0x23) = *(undefined1 *)(param_2 + 8);
      *(undefined4 *)(iVar4 + 4) = *(undefined4 *)(param_2 + 0xc);
      *(undefined2 *)(iVar4 + 8) = *(undefined2 *)(param_2 + 0x10);
      *(undefined1 *)(iVar5 + 0x14) = 1;
    }
    else {
      iVar4 = param_1 + (uVar3 + 1) * 0x18;
      BndStrg_DeleteEntry_UnLock(param_1,iVar4 + 4,uVar3);
      __memzero(iVar2,0x18);
      *(undefined4 *)(iVar4 + 4) = *(undefined4 *)(param_2 + 0xc);
      *(undefined2 *)(iVar4 + 8) = *(undefined2 *)(param_2 + 0x10);
      *(undefined4 *)(iVar5 + 0x18) = *(undefined4 *)(param_2 + 0x38);
      *(undefined1 *)(iVar4 + 10) = *(undefined1 *)(param_2 + 7);
      *(undefined1 *)(iVar5 + 0x23) = *(undefined1 *)(param_2 + 8);
      *(undefined4 *)(iVar4 + 4) = *(undefined4 *)(param_2 + 0xc);
      *(undefined2 *)(iVar4 + 8) = *(undefined2 *)(param_2 + 0x10);
      *(undefined1 *)(iVar5 + 0x14) = 1;
    }
    if (iVar2 == 0) {
      if (-1 < DebugLevel) {
        printk("%s(): add fail!\n","BndStrg_InsertEntry");
      }
    }
    else {
      iVar4 = param_1 + (uint)(byte)(*(byte *)(param_2 + 0xc) ^ *(byte *)(param_2 + 0xd) ^
                                     *(byte *)(param_2 + 0xe) ^ *(byte *)(param_2 + 0xf) ^
                                     *(byte *)(param_2 + 0x10) ^ *(byte *)(param_2 + 0x11)) * 4;
      iVar5 = *(int *)(iVar4 + 0xc14);
      if (iVar5 == 0) {
        *(int *)(iVar4 + 0xc14) = iVar2;
      }
      else {
        do {
          iVar4 = iVar5;
          iVar5 = *(int *)(iVar4 + 0x14);
        } while (iVar5 != 0);
        *(int *)(iVar4 + 0x14) = iVar2;
      }
      *param_3 = iVar2;
      *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 1;
    }
    _raw_spin_unlock_bh(param_1 + 0x1014);
    uVar1 = 0;
  }
  else if (DebugLevel < 2) {
    uVar1 = 3;
  }
  else {
    printk("%s(): Table is TalbeIndex error =%d!\n","BndStrg_InsertEntry",*(byte *)(param_2 + 2));
    uVar1 = 3;
  }
  return uVar1;
}

