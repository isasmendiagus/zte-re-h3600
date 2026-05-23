// module: mt7915.ko
// function: mt_serv_mps_set_seq_data @ 0x25266c
// size: 108 bytes
//

int mt_serv_mps_set_seq_data(undefined4 *param_1)

{
  int iVar1;
  
  if (*(char *)(param_1 + 0x7d1) == '\0') {
    iVar1 = 0;
  }
  else {
    iVar1 = (**(code **)(param_1[0x7c4] + 0xd0))
                      (*param_1,param_1[(uint)*(byte *)(param_1 + 0x133) * 0x346 + 0x46e],
                       param_1[(uint)*(byte *)(param_1 + 0x133) * 0x346 + 0x472]);
    if (iVar1 != 0) {
      printk("%s: err=0x%08x\n","mt_serv_mps_set_seq_data",iVar1);
    }
  }
  return iVar1;
}

