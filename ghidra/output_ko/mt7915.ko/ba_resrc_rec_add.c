// module: mt7915.ko
// function: ba_resrc_rec_add @ 0xa65f0
// size: 952 bytes
//

undefined4
ba_resrc_rec_add(int param_1,int param_2,uint param_3,undefined2 param_4,undefined2 param_5)

{
  undefined2 uVar1;
  undefined1 uVar2;
  int iVar3;
  undefined1 *puVar4;
  uint uVar5;
  int iVar6;
  undefined4 uVar7;
  undefined2 uVar8;
  uint uVar9;
  undefined1 *puVar10;
  
  if (param_2 * 0x14c0 + param_1 == -0xa1d20) {
    printk(&_LC45,0x557);
    dump_stack();
  }
  iVar6 = param_1 + (param_2 * 0xa60 + param_3) * 2;
  uVar9 = (uint)*(ushort *)(iVar6 + 0xa29f4);
  if (uVar9 == 0) {
    iVar3 = param_1 + 0x2f5c0;
    _raw_spin_lock_bh(iVar3);
    if (*(uint *)(param_1 + 0x2f680) < 0x47f) {
      _raw_spin_unlock_bh(iVar3);
      uVar5 = 1;
      puVar10 = (undefined1 *)(param_1 + 0x220);
      do {
        puVar4 = puVar10;
        puVar10 = puVar4 + 0x10;
        _raw_spin_lock_bh(puVar10);
        if (*(int *)(puVar4 + 8) == 0) {
          uVar9 = uVar5 & 0xffff;
          *(int *)(param_1 + 0x2f680) = *(int *)(param_1 + 0x2f680) + 1;
          *(undefined4 *)(param_1 + uVar5 * 0x60 + 0x1c8) = 1;
          _raw_spin_unlock_bh(puVar10);
          break;
        }
        uVar5 = uVar5 + 1;
        _raw_spin_unlock_bh(puVar10);
        puVar10 = puVar4 + 0x60;
      } while (uVar5 != 0x480);
      goto LAB_000a6704;
    }
    if (0 < DebugLevel) {
      printk("BA Recipeint Session (%ld) > %d\n",*(uint *)(param_1 + 0x2f680),0x47f);
    }
    _raw_spin_unlock_bh(iVar3);
    if (DebugLevel < 3) {
      return 0;
    }
    puVar4 = (undefined1 *)0x0;
  }
  else {
    puVar4 = (undefined1 *)(param_1 + 0x1c0 + uVar9 * 0x60);
    FUN_000a4598(param_1,param_1 + 0x1c0,puVar4);
LAB_000a6704:
    uVar8 = (undefined2)uVar9;
    if (DebugLevel < 3) goto LAB_000a6720;
  }
  uVar8 = (undefined2)uVar9;
  printk("%s(%ld): Idx = %d, BAWinSize = %d\n","ba_resrc_rec_add",*(undefined4 *)(param_1 + 0x2f680)
         ,uVar9,param_5);
LAB_000a6720:
  if (puVar4 == (undefined1 *)0x0) {
    if (DebugLevel < 3) {
      return 0;
    }
    param_1 = param_2 * 0x14c0 + param_1;
    printk("Can\'t Accept ADDBA for %02x:%02x:%02x:%02x:%02x:%02x TID = %d\n",
           *(undefined1 *)(param_1 + 0xa1e0c),*(undefined1 *)(param_1 + 0xa1e0d),
           *(undefined1 *)(param_1 + 0xa1e0e),*(undefined1 *)(param_1 + 0xa1e0f),
           *(undefined1 *)(param_1 + 0xa1e10),*(undefined1 *)(param_1 + 0xa1e11),param_3);
    uVar7 = 0;
  }
  else {
    _raw_spin_lock_bh(puVar4 + 0x10);
    iVar3 = param_2 * 0x14c0 + param_1;
    *(undefined2 *)(puVar4 + 0x14) = param_5;
    *(undefined4 *)(puVar4 + 8) = 2;
    uVar1 = *(undefined2 *)(iVar3 + 0xa1e00);
    puVar4[0x3e] = (char)param_3;
    *(undefined2 *)(puVar4 + 0x40) = param_4;
    *(undefined2 *)(puVar4 + 0x3c) = uVar1;
    *(undefined4 *)(puVar4 + 8) = 3;
    *puVar4 = 1;
    uVar2 = HcGetBandByWdev(*(undefined4 *)(iVar3 + 0xa1d28));
    puVar4[0x3f] = uVar2;
    if (((*(uint *)(param_1 + 0x2f68c) & 1) != 0) && (*(uint *)(param_1 + 0x2f680) < 5)) {
      os_alloc_mem(0,puVar4 + 0x48,0x1400);
      if (*(int *)(puVar4 + 0x48) != 0) {
        os_zero_mem(*(int *)(puVar4 + 0x48),0x1400);
      }
    }
    iVar3 = param_2 * 0x14c0 + param_1;
    uVar7 = 1;
    *(ushort *)(iVar3 + 0xa29de) = *(ushort *)(iVar3 + 0xa29de) | (ushort)(1 << (param_3 & 0xff));
    *(undefined2 *)(iVar6 + 0xa29f4) = uVar8;
    HW_SET_BA_REC(param_1,*(undefined2 *)(puVar4 + 0x3c),puVar4[0x3e],*(undefined2 *)(puVar4 + 0xc),
                  *(undefined2 *)(puVar4 + 0x14),1,2,0);
    _raw_spin_unlock_bh(puVar4 + 0x10);
    if (DebugLevel < 3) {
      uVar7 = 1;
    }
    else {
      printk("MACEntry[%d]RXBAbitmap = 0x%x. BARecWcidArray=%d\n",*(undefined2 *)(iVar3 + 0xa1e00),
             *(undefined2 *)(iVar3 + 0xa29de),*(undefined2 *)(iVar6 + 0xa29f4));
    }
  }
  return uVar7;
}

