// module: mt7915.ko
// function: mt_serv_set_rx_vector_idx @ 0x251b18
// size: 80 bytes
//

int mt_serv_set_rx_vector_idx(undefined4 *param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  
  iVar1 = (**(code **)(param_1[0x7c4] + 0x90))
                    (*param_1,*(undefined1 *)(param_1 + 0x133),param_2,param_3);
  if (iVar1 != 0) {
    printk("%s: err=0x%08x\n","mt_serv_set_rx_vector_idx",iVar1);
  }
  return iVar1;
}

