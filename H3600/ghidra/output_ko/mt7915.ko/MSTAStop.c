// module: mt7915.ko
// function: MSTAStop @ 0x68acc
// size: 312 bytes
//

void MSTAStop(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = GetStaCfgByWdev();
  *(undefined4 *)(iVar1 + 0x2127a8) = 0;
  RTMPZeroMemory(iVar1 + 0x212649,0x15c);
  if ((*(uint *)(param_1 + 0xa39f84) & 0x100) != 0) {
    return;
  }
  if (((*(uint *)(iVar1 + 0x212464) & 1) != 0) || ((*(uint *)(param_1 + 0x795124) & 2) != 0)) {
    uVar2 = HcGetBandByWdev(iVar1);
    repeater_disconnect_by_band(param_1,uVar2);
    *(undefined4 *)(iVar1 + 0x213244) = 0;
    __init_waitqueue_head(iVar1 + 0x213248,"&x->wait",sta_cntl_api_ops);
    *(undefined4 *)(iVar1 + 0x213350) = 4;
    __cntl_disconnect_request(param_2,1,iVar1 + 0x212428,8,"MSTAStop",0x205);
    sta_wait_link_down(iVar1);
  }
  *(undefined4 *)(iVar1 + 0x213234) = 0;
  __init_waitqueue_head(iVar1 + 0x213238,"&x->wait",sta_cntl_api_ops);
  cntl_reset_all_fsm_in_ifdown(param_2);
  sta_wait_ifdown(iVar1);
  return;
}

