// module: mt7915.ko
// function: mt_serv_do_cal_item @ 0x251f10
// size: 72 bytes
//

int mt_serv_do_cal_item(undefined4 *param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = (**(code **)(param_1[0x7c4] + 0xc4))(*param_1,param_2,*(undefined1 *)(param_1 + 0x133));
  if (iVar1 != 0) {
    printk("%s: err=0x%08x\n","mt_serv_do_cal_item",iVar1);
  }
  return iVar1;
}

