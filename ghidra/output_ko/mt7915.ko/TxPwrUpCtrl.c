// module: mt7915.ko
// function: TxPwrUpCtrl @ 0xed8c0
// size: 24 bytes
//

bool TxPwrUpCtrl(undefined4 param_1,char param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  iVar1 = MtCmdTxPwrUpCtrl(param_1,(int)param_2,param_3,param_4,param_4);
  return iVar1 == 0;
}

