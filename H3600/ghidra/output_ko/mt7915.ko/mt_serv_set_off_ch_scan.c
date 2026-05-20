// module: mt7915.ko
// function: mt_serv_set_off_ch_scan @ 0x2517a8
// size: 124 bytes
//

int mt_serv_set_off_ch_scan(undefined4 *param_1)

{
  int iVar1;
  
  if ((param_1 + (uint)*(byte *)(param_1 + 0x133) * 0x346 + 0x138 != (undefined4 *)0x0) &&
     (param_1 + (uint)*(byte *)(param_1 + 0x133) * 0x346 != (undefined4 *)0xffffee24)) {
    iVar1 = (**(code **)(param_1[0x7c4] + 0x140))(*param_1);
    if (iVar1 == 0) {
      return 0;
    }
    printk("%s: err=0x%08x\n","mt_serv_set_off_ch_scan",iVar1);
    return iVar1;
  }
  return 0x201;
}

