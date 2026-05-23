// module: mt7915.ko
// function: mt_serv_set_tssi @ 0x251684
// size: 64 bytes
//

int mt_serv_set_tssi(undefined4 *param_1)

{
  int iVar1;
  
  iVar1 = (**(code **)(param_1[0x7c4] + 0x134))(*param_1);
  if (iVar1 != 0) {
    printk("%s: err=0x%08x\n","mt_serv_set_tssi",iVar1);
  }
  return iVar1;
}

