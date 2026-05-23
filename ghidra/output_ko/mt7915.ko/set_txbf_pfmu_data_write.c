// module: mt7915.ko
// function: set_txbf_pfmu_data_write @ 0xe81e4
// size: 220 bytes
//

undefined4 set_txbf_pfmu_data_write(int param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  undefined4 uVar4;
  int iVar5;
  uint local_24 [4];
  
  iVar5 = 0;
  iVar1 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  local_24[0] = 0;
  local_24[1] = 0;
  local_24[2] = 0;
  iVar2 = rstrtok(param_2,&_LC232);
  if (iVar2 != 0) {
    do {
      uVar3 = os_str_toul(iVar2,0,0x10);
      local_24[iVar5] = uVar3;
      iVar2 = rstrtok(0,&_LC232);
      iVar5 = iVar5 + 1;
    } while (iVar2 != 0);
    if (iVar5 == 3) {
      if (*(code **)(iVar1 + 0x174) != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x000e82ac. Too many branches */
                    /* WARNING: Treating indirect jump as call */
        uVar4 = (**(code **)(iVar1 + 0x174))
                          (*(undefined4 *)(param_1 + 0xa797a0),local_24[0] & 0xff,
                           local_24[1] & 0xffff,local_24[2] & 0xff);
        return uVar4;
      }
      return 0;
    }
  }
  if (-1 < DebugLevel) {
    printk("Error: Un-expected format!\n");
  }
  return 0;
}

