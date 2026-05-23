// module: mt7915.ko
// function: ap_chk_cl2_cl3_err @ 0x1e82c
// size: 284 bytes
//

undefined4 ap_chk_cl2_cl3_err(int param_1,int param_2)

{
  undefined1 uVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  undefined1 uVar4;
  undefined1 uVar5;
  undefined1 uVar6;
  ushort uVar7;
  undefined2 uVar8;
  uint uVar9;
  undefined4 uVar10;
  undefined1 *puVar11;
  int iVar12;
  int iVar13;
  
  uVar7 = *(ushort *)(param_2 + 0x4e);
  uVar9 = HcGetMaxStaNum();
  if (uVar7 < uVar9) {
    iVar12 = (uint)*(ushort *)(param_2 + 0x4e) * 0x14c0 + param_1;
    iVar13 = *(int *)(iVar12 + 0xa1e1c);
    if ((iVar13 == 2) || (*(int *)(iVar12 + 0xa1e20) == 2)) {
      return 0;
    }
    if (iVar13 == 1) {
      ap_cls3_err_action(param_1,param_2);
      return 1;
    }
  }
  else {
    iVar12 = MacTableLookup(param_1,*(undefined4 *)(param_2 + 0x2c));
    if (iVar12 != 0) {
      return 0;
    }
    if (3 < DebugLevel) {
      puVar11 = *(undefined1 **)(param_2 + 0x2c);
      uVar8 = *(undefined2 *)(param_2 + 0x4e);
      uVar1 = *puVar11;
      uVar2 = puVar11[1];
      uVar3 = puVar11[2];
      uVar4 = puVar11[3];
      uVar5 = puVar11[4];
      uVar6 = puVar11[5];
      uVar10 = HcGetMaxStaNum(param_1);
      printk("%s():Rx a frame from %02x:%02x:%02x:%02x:%02x:%02x with WCID(%d) > %d\n",
             "ap_chk_cl2_cl3_err",uVar1,uVar2,uVar3,uVar4,uVar5,uVar6,uVar8,uVar10);
    }
  }
  ap_cls2_err_action(param_1,param_2);
  return 1;
}

