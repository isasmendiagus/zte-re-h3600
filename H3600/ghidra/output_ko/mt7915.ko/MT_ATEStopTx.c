// module: mt7915.ko
// function: MT_ATEStopTx @ 0x280ec0
// size: 728 bytes
//

undefined4 MT_ATEStopTx(int param_1)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  code *pcVar12;
  undefined1 local_74;
  undefined1 local_73;
  undefined1 local_71;
  undefined1 local_6e;
  
  iVar2 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  iVar7 = *(int *)(param_1 + 0xa39fd4);
  iVar3 = net_ad_wrap_service(param_1);
  uVar10 = (uint)*(byte *)(iVar3 + 0x4cc);
  iVar3 = uVar10 * 0xd18;
  uVar6 = 0x16f4770;
  if (uVar10 != 0) {
    uVar6 = 50000000;
  }
  iVar4 = net_ad_wrap_service(param_1);
  cVar1 = *(char *)(iVar4 + iVar3 + 0x1135);
  iVar4 = net_ad_wrap_service(param_1);
  iVar8 = *(int *)("Get_RBIST_Raw_Data_Proc" + param_1 + 0x14);
  uVar11 = *(uint *)(iVar4 + iVar3 + 0x4e0);
  iVar4 = net_ad_wrap_service(param_1);
  iVar5 = net_ad_wrap_service(param_1);
  iVar4 = *(int *)(iVar4 + iVar3 + 0x10f4);
  iVar3 = *(int *)(iVar5 + iVar3 + 0x10f0);
  if (2 < DebugLevel) {
    printk("%s: control_band_idx=%u\n","MT_ATEStopTx",uVar10);
  }
  if (cVar1 == '\n') {
    if ((*(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff) != 0x7915) {
      net_ad_wrap_service(param_1);
      net_ad_wrap_service(param_1);
      os_zero_mem(&local_74,0x4c);
      local_74 = 1;
      local_73 = 0x1f;
      local_6e = 0;
      local_71 = 0xf;
      MtCmdATETest(param_1,&local_74);
      return 0;
    }
    iVar5 = hc_get_chip_dbg(*(undefined4 *)(param_1 + 0xa797a0));
    if (*(code **)(iVar5 + 0x98) != (code *)0x0) {
      (**(code **)(iVar5 + 0x98))(param_1,uVar10,2,0,0,0,0);
    }
    MtATESetMacTxRx(param_1,2,0,uVar10);
  }
  iVar5 = net_ad_wrap_service(param_1);
  *(undefined4 *)(uVar10 * 0xd18 + iVar5 + 0x1120) = 0;
  *(undefined4 *)(param_1 + 0xa3a04c) = 0;
  *(undefined4 *)(param_1 + 0xa3a048) = 0;
  if ((uVar11 & 0x12) != 0) {
    pcVar12 = *(code **)(iVar7 + 0xf0);
    if (pcVar12 != (code *)0x0) {
      (*pcVar12)(param_1,0,0,0,0,0,0,uVar6);
    }
    pcVar12 = *(code **)(iVar7 + 0x90);
    if (pcVar12 != (code *)0x0) {
      (*pcVar12)(param_1,0,0,0);
    }
  }
  uVar9 = (uVar11 << 0x1e) >> 0x1f;
  if (uVar11 == 0x100) {
    uVar9 = 1;
  }
  if (uVar9 != 0) {
    iVar7 = net_ad_wrap_service(param_1);
    *(uint *)(uVar10 * 0xd18 + iVar7 + 0x4e0) = uVar11 & 0xfffffffd;
    if (iVar3 != 0 || iVar4 != 0) {
      if (*(code **)(iVar8 + 8) != (code *)0x0) {
        (**(code **)(iVar8 + 8))(param_1,0x7fff);
      }
      MtATESetCleanPerStaTxQueue(param_1,0);
      if ((iVar4 != 0) && (*(code **)(iVar2 + 0x2d8) != (code *)0x0)) {
        (**(code **)(iVar2 + 0x2d8))(param_1,uVar10);
        return 0;
      }
    }
  }
  return 0;
}

