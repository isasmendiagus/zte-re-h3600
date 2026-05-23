// module: mt7915.ko
// function: mt_serv_calibration_test_mode @ 0x251ecc
// size: 64 bytes
//

int mt_serv_calibration_test_mode(undefined4 *param_1)

{
  int iVar1;
  
  iVar1 = (**(code **)(param_1[0x7c4] + 0xb0))(*param_1);
  if (iVar1 != 0) {
    printk("%s: err=0x%08x\n","mt_serv_calibration_test_mode",iVar1);
  }
  return iVar1;
}

