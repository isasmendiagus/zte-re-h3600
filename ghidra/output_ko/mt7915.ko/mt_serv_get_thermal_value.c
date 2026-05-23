// module: mt7915.ko
// function: mt_serv_get_thermal_value @ 0x2529ac
// size: 68 bytes
//

int mt_serv_get_thermal_value(undefined4 *param_1)

{
  int iVar1;
  
  iVar1 = (**(code **)(param_1[0x7c4] + 0x44))(*param_1,param_1 + 0x138);
  if (iVar1 != 0) {
    printk("%s: err=0x%08x\n","mt_serv_get_thermal_value",iVar1);
  }
  return iVar1;
}

