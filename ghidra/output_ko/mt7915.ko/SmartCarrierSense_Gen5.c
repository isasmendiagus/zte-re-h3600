// module: mt7915.ko
// function: SmartCarrierSense_Gen5 @ 0x238a84
// size: 36 bytes
//

void SmartCarrierSense_Gen5(int param_1)

{
  if (((&DAT_00a7c241)[param_1] != '\x01') && (*(char *)(param_1 + 0xa7c242) != '\x01')) {
    return;
  }
  SendSCSDataProc();
  return;
}

