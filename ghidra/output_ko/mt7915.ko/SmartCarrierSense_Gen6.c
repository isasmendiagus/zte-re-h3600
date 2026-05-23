// module: mt7915.ko
// function: SmartCarrierSense_Gen6 @ 0x238aa8
// size: 64 bytes
//

void SmartCarrierSense_Gen6(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 extraout_r2;
  
  if ((&DAT_00a7c241)[param_1] == '\x01') {
    SendSCSDataProc_CONNAC3(param_1,0);
    param_3 = extraout_r2;
  }
  if (*(char *)(param_1 + 0xa7c242) != '\x01') {
    return;
  }
  SendSCSDataProc_CONNAC3(param_1,1,param_3,param_4);
  return;
}

