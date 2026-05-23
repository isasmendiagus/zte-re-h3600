// module: mt7915.ko
// function: cmd_calculate_ecc @ 0x1bf090
// size: 632 bytes
//

undefined4
cmd_calculate_ecc(undefined4 param_1,undefined4 param_2,int param_3,void *param_4,void *param_5,
                 void *param_6)

{
  bool bVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  size_t __n;
  char local_5c;
  int local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 local_2c;
  
  local_50 = 0;
  local_4c = 0;
  local_48 = 0;
  local_44 = 0;
  local_40 = 0;
  local_54 = 0;
  if (-1 < DebugLevel) {
    printk("%s(): oper = %d, group = %d\n","cmd_calculate_ecc",param_2,param_3);
  }
  if (ec_group_map._0_4_ == param_3) {
    iVar4 = 0;
LAB_001bf294:
    __n = *(size_t *)(ec_group_map + iVar4 + 4);
LAB_001bf11c:
    if (param_4 != (void *)0x0) {
      iVar4 = __n + 0xc;
      if (param_5 != (void *)0x0 && param_6 != (void *)0x0) {
        iVar4 = iVar4 + __n * 2;
        bVar1 = true;
      }
      else {
        bVar1 = false;
        if ((param_5 != (void *)0x0) != (param_6 != (void *)0x0)) goto LAB_001bf158;
      }
      iVar2 = AndesAllocCmdMsg(param_1,iVar4);
      if ((iVar2 == 0) || (os_alloc_mem(param_1,&local_54,iVar4), local_54 == 0)) {
        uVar3 = 3;
      }
      else {
        local_50 = CONCAT13(0x9c,CONCAT12(0xed,(undefined2)local_50));
        local_4c = CONCAT31(local_4c._1_3_,8);
        local_4c = CONCAT22(0xffff,(undefined2)local_4c);
        local_3c = local_50;
        uStack_38 = local_4c;
        uStack_34 = local_48;
        uStack_30 = local_44;
        local_2c = local_40;
        AndesInitCmdMsg(iVar2,local_50,local_4c,local_48,local_44,local_40);
        iVar5 = local_54;
        *(ushort *)(local_54 + 2) = ((ushort)iVar4 & 0xff) + 0xc;
        local_5c = _LANCHOR1 + '\x01';
        *(char *)(local_54 + 8) = _LANCHOR1;
        *(char *)(local_54 + 6) = (char)iVar4;
        *(char *)(local_54 + 5) = (char)param_3;
        *(bool *)(local_54 + 7) = bVar1;
        *(undefined1 *)(local_54 + 4) = 0;
        _LANCHOR1 = local_5c;
        memmove((void *)(local_54 + 0xc),param_4,__n);
        if (bVar1) {
          memmove((void *)(iVar5 + __n + 0xc),param_5,__n);
          memmove((void *)(local_54 + __n * 2 + 0xc),param_6,__n);
          iVar5 = local_54;
        }
        AndesAppendCmdMsg(iVar2,iVar5,iVar4);
        uVar3 = chip_cmd_tx(param_1,iVar2);
        os_free_mem(local_54);
      }
      goto LAB_001bf15c;
    }
  }
  else if (ec_group_map._0_4_ != 0) {
    iVar2 = 1;
    do {
      iVar5 = iVar2 * 8;
      iVar4 = iVar2 << 3;
      iVar2 = iVar2 + 1;
      if (*(int *)(ec_group_map + iVar5) == param_3) goto LAB_001bf294;
      if (*(int *)(ec_group_map + iVar5) == 0) goto LAB_001bf158;
    } while (iVar2 != 6);
    __n = 0;
    goto LAB_001bf11c;
  }
LAB_001bf158:
  uVar3 = 2;
LAB_001bf15c:
  if (3 < DebugLevel) {
    printk("%s:(ret = %d)\n","cmd_calculate_ecc",uVar3);
  }
  return uVar3;
}

