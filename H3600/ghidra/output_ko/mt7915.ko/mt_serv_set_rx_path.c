// module: mt7915.ko
// function: mt_serv_set_rx_path @ 0x250c9c
// size: 84 bytes
//

int mt_serv_set_rx_path(undefined4 *param_1)

{
  int iVar1;
  
  iVar1 = (**(code **)(param_1[0x7c4] + 0xc))
                    (*param_1,(uint)*(byte *)(param_1 + 0x133),
                     param_1 + (uint)*(byte *)(param_1 + 0x133) * 0x346 + 0x138);
  if (iVar1 != 0) {
    printk("%s: err=0x%08x\n","mt_serv_set_rx_path",iVar1);
  }
  return iVar1;
}

