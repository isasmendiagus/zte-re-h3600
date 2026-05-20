// module: mt7915.ko
// function: mt_serv_set_cal_bypass @ 0x2515f0
// size: 76 bytes
//

int mt_serv_set_cal_bypass(undefined4 *param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = (**(code **)(param_1[0x7c4] + 0x128))(*param_1,*(undefined1 *)(param_1 + 0x133),param_2);
  if (iVar1 != 0) {
    printk("%s: err=0x%08x\n","mt_serv_set_cal_bypass",iVar1);
  }
  return iVar1;
}

