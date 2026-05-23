// module: mt7915.ko
// function: mt_pci_chip_cfg @ 0x1d83d4
// size: 540 bytes
//

bool mt_pci_chip_cfg(int param_1,int param_2)

{
  bool bVar1;
  int iVar2;
  bool bVar3;
  bool bVar4;
  undefined4 local_2c;
  
  iVar2 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  bVar4 = param_2 - 0x7615U < 2;
  bVar1 = param_2 == 0x761a;
  bVar3 = 0xfffd < (param_2 - 1U & 0xffff);
  if ((bVar4 || bVar1) || (param_2 == 0x7637 || param_2 == 0x7611)) {
    DriverOwn(param_1);
  }
  *(int *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) = param_2;
  if ((((param_2 == 0x7603 || bVar4) || (bVar1)) || (param_2 == 0x7637 || param_2 == 0x7611)) ||
     ((param_2 == 0x7663 || param_2 == 0x3280 || (param_2 == 0x6867)))) {
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x80021000,&local_2c);
    bVar4 = local_2c == 0;
    *(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0x10) = local_2c;
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x80021004,&local_2c);
    *(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0x14) = local_2c;
    bVar3 = local_2c == 0 || (bVar4 || bVar3);
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x80021008,&local_2c);
    if (param_2 == 0x7616) {
      "rtmp_read_dot11v_mbssid_cfg_from_file"[param_1 + 0x1e] = '!';
    }
    *(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) = local_2c;
    if ((param_2 != 0x7616) && (bVar1)) {
      "rtmp_read_dot11v_mbssid_cfg_from_file"[param_1 + 0x1e] = '\"';
    }
    if (local_2c == 0) {
      bVar3 = true;
    }
    else if ((local_2c & 0xffff) == 0x7603) {
      mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x80021010,&local_2c);
      *(byte *)(param_1 + 0x286284) = local_2c._3_1_ & 1;
    }
    if (0 < DebugLevel) {
      printk("%s(): HWVer=0x%x, FWVer=0x%x, pAd->ChipID=0x%x\n","mt_pci_chip_cfg",
             *(undefined4 *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0x10),
             *(undefined4 *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0x14),
             *(undefined4 *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc));
    }
  }
  *(undefined4 *)(iVar2 + 0x30) = 2;
  *(undefined4 *)(param_1 + 0x286280) = 5;
  return bVar3;
}

