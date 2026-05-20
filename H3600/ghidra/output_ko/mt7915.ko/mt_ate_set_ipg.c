// module: mt7915.ko
// function: mt_ate_set_ipg @ 0x27bd94
// size: 800 bytes
//

undefined4 mt_ate_set_ipg(int param_1,undefined4 param_2)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  undefined1 uVar9;
  undefined2 uVar10;
  uint uVar11;
  bool bVar12;
  uint uVar13;
  uint local_30;
  
  bVar1 = *(byte *)(param_1 + 0xa3ae36);
  if (2 < DebugLevel) {
    printk("%s: IPG=%dus, control_band_idx=%d\n","mt_ate_set_ipg",param_2);
    bVar1 = *(byte *)(param_1 + 0xa3ae36);
  }
  uVar8 = (uint)bVar1;
  iVar2 = net_ad_wrap_service(param_1);
  iVar2 = iVar2 + uVar8 * 0xd18 + 0x10f0;
  iVar3 = net_ad_wrap_service(param_1);
  uVar6 = *(uint *)(iVar2 + 4);
  if (*(char *)(iVar3 + uVar8 * 0xd18 + 0x1135) == '\0') {
    uVar11 = 0x13;
    iVar3 = 0;
  }
  else {
    iVar3 = 6;
    uVar11 = 0x19;
  }
  if (0 < DebugLevel) {
    printk("%s: Expected ipg=%d, control_band_idx=%d\n","mt_ate_get_ipg_param",uVar6,uVar8);
  }
  if (uVar6 < uVar11) {
    iVar4 = net_ad_wrap_service(param_1);
    iVar4 = *(int *)(uVar8 * 0xd18 + iVar4 + 0x10e8);
    *(undefined4 *)(iVar2 + 4) = 0;
    if (-1 < DebugLevel) {
      printk("%s: Invalid IPG!! sig_ext=%d, slot_time=%d, sifs_time=%d\n%s: Set ipg=%d\n",
             "mt_ate_get_ipg_param",iVar3,9,10,"mt_ate_get_ipg_param",uVar6);
    }
    if (iVar4 != 0) {
      iVar2 = net_ad_wrap_service(param_1);
      bVar12 = -1 < DebugLevel;
      *(undefined4 *)(uVar8 * 0xd18 + iVar2 + 0x10e8) = 0;
      if (bVar12) {
        printk("%s: Invalid IPG with such duty_cycle and pkt_tx_time!!\n%s: Set duty_cycle=%d\n",
               "mt_ate_get_ipg_param","mt_ate_get_ipg_param");
      }
    }
  }
  else {
    uVar6 = uVar6 - iVar3;
    if (uVar6 < 0x89) {
      iVar5 = 0;
      uVar8 = 1;
      uVar11 = 0;
      uVar7 = uVar6 - 9 & 0xffff;
      uVar10 = 0;
      uVar9 = 1;
      local_30 = 9;
      uVar6 = uVar7;
    }
    else {
      uVar8 = (uVar6 + 9) / 0x12;
      if (uVar8 == 0) {
        iVar4 = 0;
        uVar11 = 0;
        iVar5 = 0;
        uVar8 = 0;
      }
      else {
        uVar11 = 0;
        do {
          uVar8 = (int)uVar8 >> 1;
          uVar11 = uVar11 + 1;
        } while (uVar8 != 0);
        if ((int)uVar11 < 0x10) {
          iVar5 = 1 << (uVar11 & 0xff);
          iVar4 = (1 - iVar5) * 9;
          iVar5 = (iVar5 + -1) * 9;
          uVar8 = uVar11 & 0xffff;
        }
        else {
          uVar11 = 0x10;
          iVar5 = 0x8fff7;
          iVar4 = -0x8fff7;
          uVar8 = uVar11;
        }
      }
      uVar10 = (undefined2)uVar8;
      uVar8 = (uint)((int)((ulonglong)(iVar4 + uVar6) * 0x38e38e39 >> 0x20) << 0x17) >> 0x18;
      if (uVar8 < 0xf) {
        uVar7 = uVar8 * 9;
        local_30 = uVar7;
      }
      else {
        uVar7 = 0xf;
        local_30 = 0x87;
      }
      uVar6 = (iVar4 + uVar6) - local_30;
      if (0xe < uVar8) {
        uVar8 = uVar7;
      }
      uVar9 = (undefined1)uVar8;
      if (uVar6 < 0xb) {
        uVar7 = 10;
        uVar6 = uVar7;
      }
      else if (uVar6 - 0xb < 0x75) {
        uVar7 = uVar6 & 0xffff;
      }
      else {
        uVar7 = 0x7f;
        uVar6 = uVar7;
      }
    }
    if ((0 < DebugLevel) &&
       (uVar13 = uVar6,
       printk("%s: sig_ext=%d, slot_time=%d, sifs_time=%d, aifsn=%d, cw=%d\n","mt_ate_get_ipg_param"
              ,iVar3,9,uVar6,uVar8,uVar11), 0 < DebugLevel)) {
      printk("%s: Real ipg=%d\n","mt_ate_get_ipg_param",iVar3 + uVar6 + local_30 + iVar5,local_30,
             uVar13,uVar8,uVar11);
    }
    *(char *)(iVar2 + 8) = (char)iVar3;
    *(short *)(iVar2 + 0xc) = (short)uVar7;
    *(undefined1 *)(iVar2 + 0xf) = uVar9;
    *(undefined2 *)(iVar2 + 0x10) = uVar10;
    *(undefined2 *)(iVar2 + 10) = 9;
    *(undefined2 *)(iVar2 + 0x12) = 0;
  }
  return 0;
}

