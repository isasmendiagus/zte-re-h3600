// module: mt7915.ko
// function: mt_serv_get_chipid @ 0x252628
// size: 64 bytes
//

int mt_serv_get_chipid(undefined4 *param_1)

{
  int iVar1;
  
  iVar1 = (**(code **)(param_1[0x7c4] + 0xcc))(*param_1);
  if (iVar1 != 0) {
    printk("%s: err=0x%08x\n","mt_serv_get_chipid",iVar1);
  }
  return iVar1;
}

