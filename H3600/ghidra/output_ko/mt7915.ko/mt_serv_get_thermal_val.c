// module: mt7915.ko
// function: mt_serv_get_thermal_val @ 0x251578
// size: 116 bytes
//

int mt_serv_get_thermal_val(undefined4 *param_1,undefined4 param_2,undefined4 *param_3)

{
  int iVar1;
  uint uVar2;
  
  uVar2 = (uint)*(byte *)(param_1 + 0x133);
  iVar1 = (**(code **)(param_1[0x7c4] + 0x124))
                    (*param_1,param_1 + uVar2 * 0x346 + 0x138,uVar2,param_3);
  param_1[uVar2 * 0x346 + 0x453] = *param_3;
  if (iVar1 != 0) {
    printk("%s: err=0x%08x\n","mt_serv_get_thermal_val",iVar1);
  }
  return iVar1;
}

