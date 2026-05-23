// module: mt7915.ko
// function: wmm_ctrl_acquire_entry @ 0xad304
// size: 892 bytes
//

byte * wmm_ctrl_acquire_entry(undefined1 *param_1,char *param_2)

{
  byte *pbVar1;
  byte bVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  byte *pbVar6;
  byte *pbVar7;
  byte bVar8;
  int iVar9;
  uint uVar10;
  int iVar11;
  undefined1 auStack_4c [40];
  
  if ((param_1 == (undefined1 *)0x0) || (*(int *)(param_1 + 8) == 0)) {
    if (3 < DebugLevel) {
      printk("%s(): Can\'t find HdevObj\n","wmm_ctrl_acquire_entry");
      return (byte *)0x0;
    }
    return (byte *)0x0;
  }
  iVar11 = *(int *)(*(int *)(param_1 + 8) + 0x18);
  uVar10 = (uint)*(byte *)(iVar11 + 0x1a08);
  uVar3 = RcGetBandIdx();
  os_zero_mem(auStack_4c,0x24);
  iVar4 = os_cmp_mem(auStack_4c,param_2,0x24);
  if ((iVar4 == 0) || (*param_2 != '\x01')) {
    set_default_sta_edca_param(param_2);
  }
  pbVar6 = (byte *)0x0;
  if (param_1[6] != '\0') {
    bVar8 = param_1[5];
    iVar9 = *(int *)(iVar11 + 0x1a0c);
    pbVar6 = (byte *)(iVar9 + (uint)bVar8 * 0x28);
    iVar4 = FUN_000ad100(pbVar6 + 4,param_2);
    if (((iVar4 != 0) && (*(byte *)(iVar9 + (uint)bVar8 * 0x28) == uVar3)) &&
       (pbVar6[2] == param_1[0x1e])) {
      if (DebugLevel < 3) {
        return pbVar6;
      }
      printk("WMM already ready, keep use  WmmIdx:%d to  ObjIdx: %d\n",param_1[5],*param_1);
      return pbVar6;
    }
    wmm_ctrl_release_entry(param_1);
  }
  if (uVar10 == 0) {
LAB_000ad514:
    if (2 < DebugLevel) {
      printk("Allocate WmmSet to ObjIdx:%d  fail since Wmm is full and no WmmSet can match band\n",
             *param_1);
    }
    return pbVar6;
  }
  uVar5 = 0;
  do {
    iVar9 = *(int *)(iVar11 + 0x1a0c);
    pbVar6 = (byte *)(iVar9 + uVar5 * 0x28);
    iVar4 = FUN_000ad100(pbVar6 + 4,param_2);
    if (((iVar4 != 0) && (*(byte *)(iVar9 + uVar5 * 0x28) == uVar3)) && (pbVar6[2] == param_1[0x1e])
       ) {
      pbVar6[1] = pbVar6[1] + 1;
      iVar4 = DebugLevel;
      param_1[5] = (char)uVar5;
      param_1[6] = 1;
      if (iVar4 < 3) {
        return pbVar6;
      }
      printk("WMM already created, assign  WmmIdx:%d to  ObjIdx: %d\n",uVar5,*param_1);
      return pbVar6;
    }
    uVar5 = uVar5 + 1;
  } while (uVar5 != uVar10);
  pbVar6 = *(byte **)(iVar11 + 0x1a0c);
  if (pbVar6[4] == 0) {
    uVar5 = 0;
    bVar8 = 0;
  }
  else {
    uVar5 = 0;
    pbVar7 = pbVar6;
    do {
      uVar5 = uVar5 + 1;
      pbVar6 = pbVar7 + 0x28;
      if (uVar5 == uVar10) {
        uVar5 = 0;
        pbVar7 = *(byte **)(iVar11 + 0x1a0c);
        do {
          pbVar6 = pbVar7;
          if (((pbVar6[4] != 0) && (*pbVar6 == uVar3)) && (pbVar6[2] == param_1[0x1e])) {
            param_1[5] = (char)uVar5;
            param_1[6] = 1;
            pbVar6[1] = pbVar6[1] + 1;
            if (DebugLevel < 3) {
              return pbVar6;
            }
            printk("assign a old WmmIdx:%d to ObjIdx: %d, but not apply new parameter\n",uVar5,
                   *param_1);
            return pbVar6;
          }
          uVar5 = uVar5 + 1;
          pbVar7 = pbVar6 + 0x28;
        } while (uVar5 != uVar10);
        goto LAB_000ad514;
      }
      pbVar1 = pbVar7 + 0x2c;
      pbVar7 = pbVar6;
    } while (*pbVar1 != 0);
    bVar8 = (byte)uVar5;
  }
  param_1[5] = bVar8;
  param_1[6] = 1;
  os_move_mem(pbVar6 + 0xb,param_2 + 7,4);
  os_move_mem(pbVar6 + 0x13,param_2 + 0xf,4);
  os_move_mem(pbVar6 + 0xf,param_2 + 0xb,4);
  os_move_mem(pbVar6 + 0x18,param_2 + 0x14,8);
  pbVar6[1] = 1;
  *pbVar6 = (byte)uVar3;
  pbVar6[4] = 1;
  bVar2 = param_1[0x1e];
  pbVar6[3] = bVar8;
  pbVar6[2] = bVar2;
  if (DebugLevel < 3) {
    return pbVar6;
  }
  printk("Create a new WmmIdx:%d to ObjIdx: %d\n",uVar5,*param_1);
  return pbVar6;
}

