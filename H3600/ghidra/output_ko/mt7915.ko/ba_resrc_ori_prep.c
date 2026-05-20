// module: mt7915.ko
// function: ba_resrc_ori_prep @ 0xa5ab4
// size: 568 bytes
//

undefined4
ba_resrc_ori_prep(int param_1,int param_2,uint param_3,undefined2 param_4,undefined1 param_5,
                 undefined2 param_6)

{
  ushort uVar1;
  undefined2 uVar2;
  undefined2 *puVar3;
  int iVar4;
  int iVar5;
  undefined2 *puVar6;
  int iVar7;
  undefined1 auStack_29 [5];
  
  iVar7 = param_1 + (param_2 * 0xa60 + param_3) * 2;
  uVar1 = *(ushort *)(MlmeDELBAAction + iVar7);
  if (uVar1 == 0) {
    iVar5 = param_1 + 0x2f5c0;
    _raw_spin_lock_bh(iVar5);
    if (0x47e < *(uint *)(param_1 + 0x2f684)) {
      _raw_spin_unlock_bh(iVar5);
      goto LAB_000a5be0;
    }
    _raw_spin_unlock_bh(iVar5);
    iVar5 = 1;
    puVar3 = (undefined2 *)(param_1 + 0x1b208);
    do {
      puVar6 = puVar3;
      if (*(int *)(puVar6 + 6) == 0) {
        iVar4 = param_1 + iVar5 * 0x48;
        *(int *)(param_1 + 0x2f684) = *(int *)(param_1 + 0x2f684) + 1;
        uVar1 = (ushort)iVar5;
        *(int *)(iVar4 + 0x1b204) = param_1;
        *(undefined4 *)(iVar4 + 0x1b1cc) = 1;
        break;
      }
      iVar5 = iVar5 + 1;
      puVar3 = puVar6 + 0x24;
    } while (iVar5 != 0x480);
  }
  else {
    puVar6 = (undefined2 *)(param_1 + (uint)uVar1 * 0x48 + 0x1b1c0);
  }
  if (puVar6 != (undefined2 *)0x0) {
    if (*(uint *)(puVar6 + 6) < 2) {
      iVar5 = param_2 * 0x14c0 + param_1;
      *(ushort *)(MlmeDELBAAction + iVar7) = uVar1;
      puVar6[2] = param_4;
      *puVar6 = (short)param_2;
      *(undefined4 *)(puVar6 + 6) = 2;
      uVar2 = *(undefined2 *)
               (param_1 + param_3 * 2 + (uint)*(ushort *)(iVar5 + 0xa1e00) * 0x620 + 0x2f6b4);
      *(char *)(puVar6 + 1) = (char)param_3;
      puVar6[5] = param_6;
      puVar6[4] = uVar2;
      *(undefined1 *)((int)puVar6 + 7) = param_5;
      *(int *)(puVar6 + 0x22) = param_1;
      *(undefined1 *)(puVar6 + 3) = 1;
      if (((int)(uint)*(ushort *)(iVar5 + 0xa29e0) >> (param_3 & 0xff) & 1U) != 0) {
        RTMPCancelTimer(puVar6 + 8,auStack_29);
        return 1;
      }
      RTMPInitTimer(param_1,puVar6 + 8,rtmp_timer_ba_ori_session_setup_timeout,puVar6,0);
      return 1;
    }
    if (DebugLevel < 3) {
      return 0;
    }
    printk("%s(): ori BA session already exist, status = %d\n","ba_resrc_ori_prep");
    return 0;
  }
LAB_000a5be0:
  if (2 < DebugLevel) {
    printk("%s(): alloc BA session failed\n","ba_resrc_ori_prep");
  }
  return 0;
}

