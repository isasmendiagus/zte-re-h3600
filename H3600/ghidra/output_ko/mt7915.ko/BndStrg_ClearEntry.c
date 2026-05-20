// module: mt7915.ko
// function: BndStrg_ClearEntry @ 0x9ade0
// size: 336 bytes
//

void BndStrg_ClearEntry(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  if (0 < DebugLevel) {
    printk("BndStrg_ClearEntry(5G): Table Size = %u\n",*(undefined4 *)(param_1 + 8));
  }
  iVar3 = param_1 + 0x14;
  iVar4 = param_1 + 0x1c;
  _raw_spin_lock_bh(param_1 + 0x1014);
  do {
    if ((iVar3 != 0) && (*(char *)(iVar4 + -8) != '\0')) {
      iVar5 = param_1 + (uint)(byte)(*(byte *)(iVar3 + 9) ^ *(byte *)(iVar3 + 8) ^
                                     *(byte *)(iVar3 + 10) ^ *(byte *)(iVar3 + 0xb) ^
                                     *(byte *)(iVar3 + 0xc) ^ *(byte *)(iVar3 + 0xd)) * 4;
      iVar2 = *(int *)(iVar5 + 0xc14);
      if (iVar2 != 0) {
        if (iVar3 == iVar2) {
LAB_0009aefc:
          *(undefined4 *)(iVar5 + 0xc14) = *(undefined4 *)(iVar3 + 0x14);
        }
        else {
          for (iVar1 = *(int *)(iVar2 + 0x14); iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x14)) {
            if (iVar3 == iVar1) {
              if (iVar2 == 0) goto LAB_0009aefc;
              *(undefined4 *)(iVar2 + 0x14) = *(undefined4 *)(iVar3 + 0x14);
              break;
            }
            iVar2 = iVar1;
          }
        }
      }
      __memzero(iVar4,6);
      *(undefined4 *)(iVar3 + 0x14) = 0;
      *(undefined1 *)(iVar4 + -8) = 0;
      *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + -1;
    }
    iVar3 = iVar3 + 0x18;
    iVar4 = iVar4 + 0x18;
    if (iVar3 == param_1 + 0xc14) {
      if (0 < DebugLevel) {
        printk("Table Size = %u",*(undefined4 *)(param_1 + 8));
      }
      _raw_spin_unlock_bh(param_1 + 0x1014);
      return;
    }
  } while( true );
}

