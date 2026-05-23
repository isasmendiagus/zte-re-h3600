// module: mt7915.ko
// function: RxvEnCtrl @ 0xed844
// size: 20 bytes
//

bool RxvEnCtrl(void)

{
  int iVar1;
  
  iVar1 = mt_cmd_set_rxv_ctrl();
  return iVar1 == 0;
}

