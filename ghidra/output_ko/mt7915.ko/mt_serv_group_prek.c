// module: mt7915.ko
// function: mt_serv_group_prek @ 0x251188
// size: 68 bytes
//

int mt_serv_group_prek(undefined4 *param_1)

{
  int iVar1;
  
  iVar1 = (**(code **)(param_1[0x7c4] + 0x18c))(*param_1,2);
  if (iVar1 != 0) {
    printk("%s: err=0x%08x\n","mt_serv_group_prek",iVar1);
  }
  return iVar1;
}

