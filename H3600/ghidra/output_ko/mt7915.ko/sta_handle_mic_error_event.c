// module: mt7915.ko
// function: sta_handle_mic_error_event @ 0x68830
// size: 112 bytes
//

void sta_handle_mic_error_event(int param_1,int param_2,int param_3,undefined4 param_4)

{
  byte bVar1;
  int iVar2;
  
  bVar1 = *(byte *)(param_3 + 0x51);
  iVar2 = GetStaCfgByWdev(param_1,*(undefined4 *)(param_2 + 8));
  if (iVar2 == 0) {
    printk(&_LC12,0x314);
    dump_stack();
    return;
  }
  if ((*(uint *)(iVar2 + 0x212464) & 1) == 0) {
    return;
  }
  RTMPReportMicError(param_1,iVar2,param_1 + (uint)bVar1 * 0x49 + 0xa37764,param_4);
  return;
}

