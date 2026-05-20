// module: mt7915.ko
// function: MtCmdATERFTestResp @ 0x1ae610
// size: 60 bytes
//

void MtCmdATERFTestResp(int param_1,int *param_2)

{
  int iVar1;
  
  iVar1 = *param_2;
  if (iVar1 == 0x11) {
    MtCmdRfTestSolicitICapIQDataCb();
    return;
  }
  if (iVar1 != 0x13) {
    if (iVar1 != 0xc) {
      return;
    }
    MtCmdRfTestSolicitICapStatusCb();
    return;
  }
  os_move_mem(*(void **)(param_1 + 0xc),param_2 + 2,1);
  return;
}

