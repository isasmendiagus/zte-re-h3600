// module: mt7915.ko
// function: mt_serv_get_rxv_dump_content @ 0x251c88
// size: 64 bytes
//

int mt_serv_get_rxv_dump_content(undefined4 *param_1)

{
  int iVar1;
  
  iVar1 = (**(code **)(param_1[0x7c4] + 0xa0))(*param_1);
  if (iVar1 != 0) {
    printk("%s: err=0x%08x\n","mt_serv_get_rxv_dump_content",iVar1);
  }
  return iVar1;
}

