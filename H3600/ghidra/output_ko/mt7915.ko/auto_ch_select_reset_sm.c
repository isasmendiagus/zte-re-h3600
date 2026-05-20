// module: mt7915.ko
// function: auto_ch_select_reset_sm @ 0x26a78
// size: 52 bytes
//

void auto_ch_select_reset_sm(undefined4 param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  
  if (param_2 != 0) {
    uVar1 = HcGetBandByWdev(param_2);
    iVar2 = HcGetAutoChCtrlbyBandIdx(param_1,uVar1);
    if (iVar2 != 0) {
      *(undefined4 *)(iVar2 + 0x58) = 0;
    }
    return;
  }
  return;
}

