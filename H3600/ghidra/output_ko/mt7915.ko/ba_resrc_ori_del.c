// module: mt7915.ko
// function: ba_resrc_ori_del @ 0xa618c
// size: 572 bytes
//

undefined4 ba_resrc_ori_del(int param_1,int param_2,int param_3)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  ushort *puVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  undefined1 auStack_29 [5];
  
  uVar5 = (uint)*(ushort *)(param_1 + (param_2 * 0xa60 + param_3 + 0x51500) * 2 + 4);
  if (uVar5 - 1 < 0x47f) {
    if (2 < DebugLevel) {
      printk("%s():Idx=%d, Wcid=%d, TID=%d, ORI_BA_Status=%d\n","ba_resrc_ori_del",uVar5,param_2,
             param_3,*(undefined4 *)(uVar5 * 0x48 + param_1 + 0x1b1cc));
    }
    iVar6 = uVar5 * 0x48;
    HW_SET_BA_REC(param_1,param_2,param_3,0,0,0,1,0);
    RTMPReleaseTimer(param_1 + 0x1c0 + iVar6 + 0x1b010,auStack_29);
    iVar7 = DebugLevel;
    if (*(int *)(param_1 + iVar6 + 0x1b1cc) == 0) {
      uVar2 = 1;
    }
    else {
      uVar3 = (uint)*(ushort *)(param_1 + 0x1c0 + iVar6 + 0x1b000);
      *(undefined2 *)
       (param_1 + (uVar3 * 0xa60 + (uint)*(byte *)(param_1 + iVar6 + 0x1b1c2) + 0x51500) * 2 + 4) =
           0;
      if (2 < iVar7) {
        printk("%s: Wcid = %d, TID = %d\n","ba_free_ori_entry",uVar3);
      }
      iVar7 = param_1 + 0x2f5c0;
      iVar6 = param_1 + uVar5 * 0x48;
      if (*(int *)(iVar6 + 0x1b1cc) == 3) {
        _raw_spin_lock_bh(iVar7);
        iVar1 = DebugLevel;
        *(int *)(param_1 + 0x2f688) = *(int *)(param_1 + 0x2f688) + -1;
        puVar4 = (ushort *)(uVar3 * 0x14c0 + param_1 + 0xa29e0);
        *puVar4 = *puVar4 & ~(ushort)(1 << *(sbyte *)(iVar6 + 0x1b1c2));
        if (2 < iVar1) {
          printk("ba_free_ori_entry numAsOriginator= %ld\n");
        }
        _raw_spin_unlock_bh(iVar7);
      }
      _raw_spin_lock_bh(iVar7);
      if (*(int *)(param_1 + 0x2f684) == 0) {
        if (-1 < DebugLevel) {
          printk("%s(): !!! Something wrong !!! numAsOriginator = 0, ORI_BA_Status = %d\n",
                 "ba_free_ori_entry",*(undefined4 *)(uVar5 * 0x48 + param_1 + 0x1b1cc));
        }
      }
      else {
        *(int *)(param_1 + 0x2f684) = *(int *)(param_1 + 0x2f684) + -1;
      }
      _raw_spin_unlock_bh(iVar7);
      uVar2 = 1;
      param_1 = param_1 + uVar5 * 0x48;
      *(undefined4 *)(param_1 + 0x1b1cc) = 0;
      *(undefined1 *)(param_1 + 0x1b1c6) = 0;
    }
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}

