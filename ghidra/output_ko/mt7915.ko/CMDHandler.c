// module: mt7915.ko
// function: CMDHandler @ 0xc4b9c
// size: 444 bytes
//

void CMDHandler(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  undefined4 *puVar6;
  
  if (param_1 == 0) {
    return;
  }
  if (*(int *)(param_1 + 0x285c54) == 0) {
    return;
  }
  iVar5 = (int)&DAT_00285c64 + param_1;
  uVar4 = 1;
  do {
    _raw_spin_lock_bh(iVar5);
    puVar6 = *(undefined4 **)(param_1 + 0x285c58);
    if (puVar6 == (undefined4 *)0x0) {
      _raw_spin_unlock_bh(iVar5);
      return;
    }
    iVar3 = *(int *)(param_1 + 0x285c54) + -1;
    *(undefined4 *)(param_1 + 0x285c58) = puVar6[4];
    *(int *)(param_1 + 0x285c54) = iVar3;
    if (iVar3 == 0) {
      *(undefined4 *)(param_1 + 0x285c5c) = 0;
    }
    _raw_spin_unlock_bh(iVar5);
    if ((*(uint *)(param_1 + 0xa39f84) & 0x140) == 0) {
      iVar3 = 0;
      if ((short)*puVar6 < 0x21) {
        do {
          iVar2 = iVar3 * 8;
          iVar1 = iVar3 * 8;
          iVar3 = iVar3 + 1;
          if (*(int *)(&DAT_00294cb8 + iVar2) == (int)(short)*puVar6) {
            if (*(code **)(&DAT_00294cbc + iVar1) != (code *)0x0) {
              (**(code **)(&DAT_00294cbc + iVar1))(param_1,puVar6);
              goto LAB_000c4c48;
            }
            break;
          }
        } while (iVar3 != 0x15);
        if (-1 < DebugLevel) {
          printk("No corresponding CMDHdlr for this CMD(%x)\n");
        }
      }
      else if (-1 < DebugLevel) {
        printk("CMD(%x) is out of boundary\n");
      }
    }
LAB_000c4c48:
    iVar3 = puVar6[1];
    if (*(char *)(puVar6 + 3) == '\x01') {
joined_r0x000c4d0c:
      if (iVar3 != 0) {
        os_free_mem();
      }
    }
    else if (iVar3 != 0) {
      iVar3 = puVar6[2];
      goto joined_r0x000c4d0c;
    }
    os_free_mem(puVar6);
    if (*(int *)(param_1 + 0x285c54) == 0) {
      return;
    }
    uVar4 = uVar4 + 1;
    if ((*(uint *)(((uint)&stack0xffffffe0 & 0xffffe000) + 4) & 0x1fff00) == 0 && 0xf < uVar4) {
      schedule();
      uVar4 = 0;
    }
  } while( true );
}

