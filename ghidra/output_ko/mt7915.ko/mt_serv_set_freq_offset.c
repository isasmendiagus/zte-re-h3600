// module: mt7915.ko
// function: mt_serv_set_freq_offset @ 0x2512f0
// size: 88 bytes
//

int mt_serv_set_freq_offset(undefined4 *param_1)

{
  int iVar1;
  
  iVar1 = (**(code **)(param_1[0x7c4] + 0x48))
                    (*param_1,param_1[(uint)*(byte *)(param_1 + 0x133) * 0x346 + 0x452]);
  if (iVar1 != 0) {
    printk("%s: err=0x%08x\n","mt_serv_set_freq_offset",iVar1);
  }
  return iVar1;
}

