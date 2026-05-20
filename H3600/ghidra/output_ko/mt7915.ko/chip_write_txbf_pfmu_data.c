// module: mt7915.ko
// function: chip_write_txbf_pfmu_data @ 0x17c924
// size: 92 bytes
//

bool chip_write_txbf_pfmu_data
               (undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  
  iVar1 = hc_get_hdev_privdata();
  iVar2 = CmdETxBfPfmuFullDimDataWrite(iVar1,param_2,param_3,param_4,iVar1 + 0xa78734,0x84);
  os_zero_mem(iVar1 + 0xa78734,0x84);
  return iVar2 == 0;
}

