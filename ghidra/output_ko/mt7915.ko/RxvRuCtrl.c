// module: mt7915.ko
// function: RxvRuCtrl @ 0xed858
// size: 20 bytes
//

bool RxvRuCtrl(void)

{
  int iVar1;
  
  iVar1 = mt_cmd_set_rxv_ru_ctrl();
  return iVar1 == 0;
}

