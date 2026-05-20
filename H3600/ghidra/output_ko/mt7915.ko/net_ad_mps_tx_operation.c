// module: mt7915.ko
// function: net_ad_mps_tx_operation @ 0x25db50
// size: 256 bytes
//

int net_ad_mps_tx_operation(undefined4 param_1,uint *param_2,int param_3)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  
  uVar3 = param_2[0x33a];
  if (uVar3 == 0) {
    iVar1 = 0x607;
  }
  else {
    uVar2 = param_2[0x336];
    if (uVar2 == 0) {
      iVar1 = 0x607;
      goto LAB_0025dc08;
    }
    if (param_3 == 0) {
      uVar2 = *param_2;
      *param_2 = uVar2 & 0xfffffffd;
      if ((uVar2 & 0x40) != 0) {
        return 0;
      }
      if ((char)param_2[0x338] != '\0') {
        return 0;
      }
      param_2[0x336] = 0;
      sys_ad_free_mem(uVar3);
      param_2[0x33a] = 0;
      return 0;
    }
    if (((*param_2 & 0x42) != 0) || ((char)param_2[0x338] != '\0')) {
      iVar1 = 0x600;
      goto LAB_0025dc08;
    }
    param_2[0x339] = 1;
    *param_2 = *param_2 | 0x40;
    *(undefined1 *)(param_2 + 0x338) = 1;
    iVar1 = FUN_0025c704();
    if (iVar1 == 0) {
      iVar1 = FUN_0025a2d4(param_2,0xffff);
      return iVar1;
    }
  }
  uVar2 = param_2[0x336];
LAB_0025dc08:
  printk("%s: error, mps_cnt=%d, mps_setting=%p\n","net_ad_mps_tx_operation",uVar2,uVar3);
  printk("%s: error, op_mode=0x%x, setting_inuse=0x%x\n","net_ad_mps_tx_operation",*param_2,
         (char)param_2[0x338]);
  return iVar1;
}

