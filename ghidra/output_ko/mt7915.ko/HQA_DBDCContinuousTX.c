// module: mt7915.ko
// function: HQA_DBDCContinuousTX @ 0x270ae8
// size: 696 bytes
//

undefined4 HQA_DBDCContinuousTX(int param_1,undefined4 param_2,int param_3)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  int iVar9;
  uint uVar10;
  undefined4 uVar11;
  uint uVar12;
  int iVar13;
  uint uVar14;
  int iVar15;
  undefined1 local_68;
  undefined1 local_64;
  undefined1 local_60;
  undefined1 local_5c;
  
  iVar15 = *(int *)(param_1 + 0xa39fd4);
  if (DebugLevel < 3) {
    uVar1 = *(uint *)(param_3 + 0xc);
  }
  else {
    printk(&_LC11,"HQA_DBDCContinuousTX");
    uVar1 = *(uint *)(param_3 + 0xc);
  }
  iVar9 = DebugLevel;
  uVar2 = *(uint *)(param_3 + 0x10);
  uVar12 = uVar1 << 0x18 | (uVar1 >> 8 & 0xff) << 0x10 | (uVar1 >> 0x10 & 0xff) << 8 | uVar1 >> 0x18
  ;
  uVar3 = *(uint *)(param_3 + 0x14);
  uVar10 = uVar2 << 0x18 | (uVar2 >> 8 & 0xff) << 0x10 | (uVar2 >> 0x10 & 0xff) << 8 | uVar2 >> 0x18
  ;
  uVar2 = *(uint *)(param_3 + 0x18);
  uVar14 = uVar3 << 0x18 | (uVar3 >> 8 & 0xff) << 0x10 | (uVar3 >> 0x10 & 0xff) << 8 | uVar3 >> 0x18
  ;
  uVar4 = *(uint *)(param_3 + 0x1c);
  uVar5 = *(uint *)(param_3 + 0x20);
  uVar6 = *(uint *)(param_3 + 0x24);
  uVar7 = *(uint *)(param_3 + 0x28);
  uVar8 = *(uint *)(param_3 + 0x2c);
  uVar8 = uVar8 << 0x18 | (uVar8 >> 8 & 0xff) << 0x10 | (uVar8 >> 0x10 & 0xff) << 8 | uVar8 >> 0x18;
  *(char *)(param_1 + 0xa3ae36) = (char)(uVar1 >> 0x18);
  if (2 < iVar9) {
    printk("%s: Band = %d, Control = %d, AntIndex = %d, Phymode = %d, BW = %d, CH = %d, Rate = %d, Central_Ch = %d, TxfdMode = %d\n"
           ,"HQA_DBDCContinuousTX",uVar12,uVar10,uVar14,
           uVar2 << 0x18 | (uVar2 >> 8 & 0xff) << 0x10 | (uVar2 >> 0x10 & 0xff) << 8 | uVar2 >> 0x18
           ,uVar4 << 0x18 | (uVar4 >> 8 & 0xff) << 0x10 | (uVar4 >> 0x10 & 0xff) << 8 |
            uVar4 >> 0x18,
           uVar5 << 0x18 | (uVar5 >> 8 & 0xff) << 0x10 | (uVar5 >> 0x10 & 0xff) << 8 | uVar5 >> 0x18
           ,uVar6 << 0x18 | (uVar6 >> 8 & 0xff) << 0x10 | (uVar6 >> 0x10 & 0xff) << 8 |
            uVar6 >> 0x18,
           uVar7 << 0x18 | (uVar7 >> 8 & 0xff) << 0x10 | (uVar7 >> 0x10 & 0xff) << 8 | uVar7 >> 0x18
           ,uVar8);
  }
  if (uVar10 == 0) {
    if (*(code **)(iVar15 + 0xa0) != (code *)0x0) {
      (**(code **)(iVar15 + 0xa0))(param_1,uVar8);
      uVar11 = 0;
      goto LAB_00270d08;
    }
  }
  else if (*(int *)(iVar15 + 0x9c) != 0) {
    iVar9 = net_ad_wrap_service(param_1);
    uVar11 = 0;
    iVar13 = uVar12 * 0xd18;
    local_68 = (undefined1)(uVar2 >> 0x18);
    *(undefined1 *)(iVar9 + iVar13 + 0x1135) = local_68;
    iVar9 = net_ad_wrap_service(param_1);
    local_64 = (undefined1)(uVar4 >> 0x18);
    *(undefined1 *)(iVar9 + iVar13 + 0x1136) = local_64;
    iVar9 = net_ad_wrap_service(param_1);
    local_60 = (undefined1)(uVar5 >> 0x18);
    *(undefined1 *)(iVar9 + iVar13 + 0x1132) = local_60;
    iVar9 = net_ad_wrap_service(param_1);
    local_5c = (undefined1)(uVar7 >> 0x18);
    *(undefined1 *)(iVar9 + iVar13 + 0x1130) = local_5c;
    iVar9 = net_ad_wrap_service(param_1);
    *(char *)(iVar9 + iVar13 + 0x1138) = (char)(uVar6 >> 0x18);
    iVar9 = net_ad_wrap_service(param_1);
    *(uint *)(iVar9 + iVar13 + 0x1128) = uVar14;
    (**(code **)(iVar15 + 0x9c))(param_1,(int)(char)(uVar3 >> 0x18),uVar8);
    goto LAB_00270d08;
  }
  uVar11 = 1;
LAB_00270d08:
  FUN_0026cdd0(param_3,param_2,2,uVar11);
  return uVar11;
}

