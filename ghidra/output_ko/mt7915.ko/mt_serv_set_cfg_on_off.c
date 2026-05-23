// module: mt7915.ko
// function: mt_serv_set_cfg_on_off @ 0x2521a8
// size: 96 bytes
//

int mt_serv_set_cfg_on_off(undefined4 *param_1)

{
  int iVar1;
  
  iVar1 = (**(code **)(param_1[0x7c4] + 300))
                    (*param_1,*(undefined1 *)
                               (param_1 + (uint)*(byte *)(param_1 + 0x133) * 0x346 + 0x46c),
                     *(undefined1 *)
                      ((int)param_1 + (uint)*(byte *)(param_1 + 0x133) * 0xd18 + 0x11b1));
  if (iVar1 != 0) {
    printk("%s: err=0x%08x\n","mt_serv_set_cfg_on_off",iVar1);
  }
  return iVar1;
}

