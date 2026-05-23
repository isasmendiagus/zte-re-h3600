// module: mt7915.ko
// function: TxCCKStreamCtrl @ 0xed6fc
// size: 180 bytes
//

bool TxCCKStreamCtrl(int param_1,uint param_2,undefined4 param_3)

{
  int iVar1;
  
  if (2 < DebugLevel) {
    printk("u1CCKTxStream = %d \n");
  }
  if (param_2 == 0) {
    param_2 = 1;
  }
  else if (3 < param_2) {
    if (DebugLevel < 2) {
      return false;
    }
    printk("%s: set wrong parameters\n","TxCCKStreamCtrl");
    return false;
  }
  if ((*(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff) != 0x7622) {
    return false;
  }
  iVar1 = MtCmdTxCCKStream(param_1,param_2,param_3);
  return iVar1 == 0;
}

