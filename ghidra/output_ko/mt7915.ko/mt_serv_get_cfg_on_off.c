// module: mt7915.ko
// function: mt_serv_get_cfg_on_off @ 0x2514d0
// size: 80 bytes
//

int mt_serv_get_cfg_on_off(undefined4 *param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  
  iVar1 = (**(code **)(param_1[0x7c4] + 0x104))
                    (*param_1,*(undefined1 *)(param_1 + 0x133),param_2,param_3);
  if (iVar1 != 0) {
    printk("%s: err=0x%08x\n","mt_serv_get_cfg_on_off",iVar1);
  }
  return iVar1;
}

