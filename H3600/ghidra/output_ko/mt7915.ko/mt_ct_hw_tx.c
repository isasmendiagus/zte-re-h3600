// module: mt7915.ko
// function: mt_ct_hw_tx @ 0x1c94bc
// size: 728 bytes
//

int mt_ct_hw_tx(int param_1,undefined1 *param_2)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  undefined1 local_180 [12];
  int local_174;
  uint local_168;
  undefined4 local_158;
  undefined1 local_154;
  undefined4 local_150;
  undefined1 local_14c;
  undefined1 local_14b;
  undefined1 local_147;
  int local_128;
  int local_34;
  undefined2 local_2e;
  int local_2c [2];
  
  local_2e = 1;
  iVar2 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  uVar4 = *(uint *)(param_2 + 0x18);
  if ((uVar4 & 0x1000000) == 0) {
    tx_bytes_calculate(param_1,param_2);
    uVar4 = *(uint *)(param_2 + 0x18);
  }
  if ((uVar4 & 0x800000) == 0) {
    memcpy(local_180,param_2,0x140);
    if ((*(uint *)(param_1 + 0xa3ac14) & 1) == 0) {
      if ((*(int *)(param_1 + 0xa77bb4) == 1) &&
         ((*(uint *)(*(int *)(param_1 + 0xa77bb8) + 0x4e0) & 1) != 0)) {
        iVar3 = 0;
      }
      else {
        iVar3 = (uint)(byte)param_2[0x35] + (uint)(byte)param_2[0x34];
      }
    }
    else {
      iVar3 = 0;
    }
    bVar1 = *(byte *)(iVar2 + 2);
    iVar5 = *(int *)(param_2 + 0x58);
    if (3 < DebugLevel) {
      local_34 = iVar3;
      printk("%s():DataFrm, MpduHdrL=%d,WFHdrL=%d,HdrPadL=%d,HwRsvL=%d, NeedCopyHdrLen=%d\n",
             "mt_ct_hw_tx",param_2[0x35],param_2[0x2c],param_2[0x34],param_2[0x39],iVar3);
      iVar3 = local_34;
    }
    iVar3 = RTMPAllocateNdisPacket
                      (param_1,local_2c,iVar5 + (uint)bVar1,iVar3,*(undefined4 *)(param_2 + 0x30),
                       *(undefined4 *)(param_2 + 0x28));
    if (iVar3 == 0) {
      *(undefined1 *)(local_2c[0] + 0x2d) = *(undefined1 *)(*(int *)(param_2 + 0xc) + 0x2d);
      if (param_2[0x2f] == '\0' || param_2[0x2f] == '\x03') {
        RTMPFreeNdisPacket(param_1,*(undefined4 *)(param_2 + 0xc));
      }
      local_128 = hif_get_tx_buf(*(undefined4 *)(param_1 + 0xa797a0),local_180,*param_2,param_2[5]);
      local_150 = *(undefined4 *)(local_2c[0] + 0xcc);
      local_168 = local_168 | 0x100000;
      local_174 = local_2c[0];
      local_158 = *(undefined4 *)(local_2c[0] + 100);
      if (param_2[0x2e] == '\0' || param_2[0x2e] == '\x03') {
        asic_write_tmac_info(param_1,local_128,local_180);
      }
      local_14b = 0;
      local_154 = 0;
      *param_2 = local_180[0];
      local_14c = 0;
      local_147 = 0;
      iVar2 = asic_write_txp_info(param_1,local_128 + (uint)*(byte *)(iVar2 + 2),local_180);
      if ((iVar2 == 0) && (iVar2 = 0, param_2[0x2e] == '\0' || param_2[0x2e] == '\x03')) {
        asic_write_tx_resource(param_1,local_180,1,&local_2e);
      }
    }
    else {
      iVar2 = 1;
    }
  }
  else {
    if (param_2[0x2e] == '\0' || param_2[0x2e] == '\x03') {
      asic_write_tmac_info(param_1,*(undefined4 *)(param_2 + 0x58),param_2);
    }
    iVar2 = asic_write_txp_info(param_1,*(int *)(param_2 + 0x58) + (uint)*(byte *)(iVar2 + 2),
                                param_2);
    if (iVar2 == 0) {
      if (param_2[0x2e] == '\0' || param_2[0x2e] == '\x03') {
        asic_write_tx_resource(param_1,param_2,1,&local_2e);
        return 0;
      }
      iVar2 = 0;
    }
  }
  return iVar2;
}

