// module: mt7915.ko
// function: mt_serv_set_fagc_rssi_path @ 0x251b6c
// size: 76 bytes
//

int mt_serv_set_fagc_rssi_path(undefined4 *param_1)

{
  int iVar1;
  
  iVar1 = (**(code **)(param_1[0x7c4] + 0xa8))
                    (*param_1,*(undefined1 *)(param_1 + 0x133),
                     *(undefined1 *)((int)param_1 + 0x113e));
  if (iVar1 != 0) {
    printk("%s: err=0x%08x\n","mt_serv_set_fagc_rssi_path",iVar1);
  }
  return iVar1;
}

