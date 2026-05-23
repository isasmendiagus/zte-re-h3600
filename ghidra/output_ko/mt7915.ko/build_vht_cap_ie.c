// module: mt7915.ko
// function: build_vht_cap_ie @ 0x203054
// size: 912 bytes
//

undefined4 build_vht_cap_ie(int param_1,undefined4 param_2,uint *param_3)

{
  byte bVar1;
  byte bVar2;
  uint uVar3;
  uint uVar4;
  byte bVar5;
  char cVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  byte bVar10;
  uint uVar11;
  uint uVar12;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  
  iVar7 = wlan_config_get_vht_bw(param_2);
  iVar8 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  __memzero(&local_24,0xc);
  uVar9 = wlan_config_get_vht_max_mpdu_len(param_2);
  if (*(byte *)(iVar8 + 0x60) <= uVar9) {
    uVar9 = (uint)*(byte *)(iVar8 + 0x60);
  }
  if (iVar7 == 2) {
    cVar6 = '\x01';
  }
  else {
    if (iVar7 != 3) {
      local_24._0_1_ = (byte)local_24 & 0xf0 | (byte)uVar9 & 3;
      goto LAB_002030dc;
    }
    cVar6 = '\x02';
  }
  local_24._0_1_ = (byte)local_24 & 0xf0 | (byte)uVar9 & 3 | cVar6 << 2;
  bVar5 = wlan_config_get_vht_sgi(param_2);
  local_24._0_1_ = (byte)local_24 & 0xbf | (bVar5 & 1) << 6;
LAB_002030dc:
  iVar7 = wlan_config_get_vht_ldpc(param_2);
  if ((iVar7 == 0) || ((*(uint *)(iVar8 + 0x2c) & 0x40) == 0)) {
    local_24._0_1_ = (byte)local_24 & 0xef;
  }
  else {
    local_24._0_1_ = (byte)local_24 | 0x10;
  }
  bVar5 = wlan_config_get_vht_sgi(param_2);
  local_24 = CONCAT31(CONCAT21((ushort)(local_24 >> 0x10) & 0xfc7f | 0x40 |
                               (*(byte *)(iVar8 + 0x61) & 7) << 7,local_24._1_1_),
                      (byte)local_24 & 0x5f | (bVar5 & 1) << 5) & 0xfffff8ff;
  iVar7 = wlan_config_get_vht_stbc(param_2);
  if (iVar7 != 0) {
    bVar5 = (byte)"SetPartProfileParameters"[param_1 + 0x18] >> 4;
    if (*(char *)(param_1 + 0x79504d) != '\0') {
      iVar7 = HcGetBandByWdev(param_2);
      if (iVar7 == 0) {
        bVar5 = "SetPartProfileParameters"[param_1 + 0x1a];
      }
      else {
        bVar5 = "rtmp_read_vow_parms_from_file"[param_1];
      }
    }
    if (bVar5 < 2) {
      bVar5 = (byte)local_24 & 0x7f;
    }
    else {
      bVar5 = (byte)local_24 | 0x80;
    }
    local_24 = CONCAT22(local_24._2_2_,CONCAT11(local_24._1_1_,bVar5)) & 0xfffff8ff | 0x100;
  }
  local_24 = local_24 | 0x30000000;
  if (*(char *)(iVar8 + 0x96) != '\0') {
    local_28 = *(uint *)(param_1 + 0x795960);
    mt_WrapSetVHTETxBFCap(param_1,param_2,&local_28);
    bVar5 = local_24._2_1_ & 0xf8;
    local_24._0_3_ = CONCAT12(bVar5 | local_28._2_1_ & 7,(undefined2)local_24);
    cVar6 = txbf_bfee_get_bfee_sts(local_28._1_1_ >> 5);
    uVar9 = local_28 >> 8 & 0xff;
    uVar12 = local_28 >> 0x10 & 0xff;
    local_24._0_2_ =
         CONCAT11(local_24._1_1_ & 7 | cVar6 << 5 | (byte)(((uVar9 << 0x1b) >> 0x1f) << 4) |
                  (byte)(((uVar9 << 0x1c) >> 0x1f) << 3),(byte)local_24);
    local_24 = CONCAT22(CONCAT11(local_24._3_1_,
                                 local_24._2_1_ & 0xe7 | (byte)(((uVar12 << 0x1b) >> 0x1f) << 4) |
                                 (byte)(((uVar12 << 0x1c) >> 0x1f) << 3)),(undefined2)local_24);
  }
  local_20 = CONCAT22(local_20._2_2_,0xff00);
  local_1c = CONCAT22(local_1c._2_2_,0xff00);
  local_20 = CONCAT31(local_20._1_3_,0xff);
  uVar11 = (uint)*(byte *)(iVar8 + 0x6e);
  local_1c = CONCAT31(local_1c._1_3_,0xff);
  iVar7 = wlan_operate_get_rx_stream(param_2);
  iVar8 = wlan_operate_get_tx_stream(param_2);
  uVar12 = local_1c;
  uVar9 = local_20;
  if (((uVar11 < 3) && (iVar7 - 1U < 4)) && (iVar8 - 1U < 4)) {
    local_20 = CONCAT22(local_20._2_2_ & 0xe000 |
                        *(ushort *)(&DAT_002a14fe + (uVar11 * 4 + iVar7) * 2) & 0x1fff,
                        (undefined2)local_20);
    uVar3 = local_20;
    local_1c = CONCAT22(local_1c._2_2_ & 0xe000 |
                        *(ushort *)(&DAT_002a14fe + (uVar11 * 4 + iVar8) * 2) & 0x1fff,
                        (undefined2)local_1c);
    uVar4 = local_1c;
    if (iVar7 != 0) {
      local_20._0_1_ = (byte)uVar9;
      bVar10 = (byte)local_20;
      uVar9 = uVar11 & 3;
      bVar5 = (byte)uVar9;
      local_20._1_3_ = SUB43(uVar3,1);
      local_20 = CONCAT31(local_20._1_3_,(byte)local_20 & 0xfc | bVar5);
      if (iVar7 != 1) {
        bVar1 = (byte)(uVar9 << 2);
        local_20 = CONCAT31(local_20._1_3_,bVar10 & 0xf0 | bVar5 | bVar1);
        if (iVar7 != 2) {
          bVar2 = (byte)(uVar9 << 4);
          local_20 = CONCAT31(local_20._1_3_,bVar10 & 0xc0 | bVar5 | bVar1 | bVar2);
          if (iVar7 != 3) {
            local_20 = CONCAT31(local_20._1_3_,bVar5 | bVar1 | bVar2 | (byte)(uVar9 << 6));
          }
        }
      }
    }
    if (iVar8 != 0) {
      local_1c._0_1_ = (byte)uVar12;
      bVar10 = (byte)local_1c;
      uVar11 = uVar11 & 3;
      bVar5 = (byte)uVar11;
      local_1c._1_3_ = SUB43(uVar4,1);
      local_1c = CONCAT31(local_1c._1_3_,(byte)local_1c & 0xfc | bVar5);
      if (iVar8 != 1) {
        bVar1 = (byte)(uVar11 << 2);
        local_1c = CONCAT31(local_1c._1_3_,bVar10 & 0xf0 | bVar5 | bVar1);
        if (iVar8 != 2) {
          bVar2 = (byte)(uVar11 << 4);
          bVar10 = bVar10 & 0xc0 | bVar5 | bVar1 | bVar2;
          if (iVar8 != 3) {
            bVar10 = bVar5 | bVar1 | bVar2 | (byte)(uVar11 << 6);
          }
          local_1c = CONCAT31(local_1c._1_3_,bVar10);
        }
      }
    }
  }
  else {
    local_20 = local_20 & 0xe000ffff;
    local_1c = local_1c & 0xe000ffff;
  }
  *param_3 = local_24;
  param_3[1] = local_20;
  param_3[2] = local_1c;
  return 0xc;
}

