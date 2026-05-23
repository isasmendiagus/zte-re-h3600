// module: mt7915.ko
// function: sta_deauth_act_handle @ 0xc42e8
// size: 88 bytes
//

undefined4 sta_deauth_act_handle(undefined4 param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  uVar2 = *(undefined4 *)(param_2 + 4);
  iVar1 = GetStaCfgByWdev(param_1,uVar2);
  if (iVar1 != 0) {
    __cntl_disconnect_request(uVar2,0,iVar1 + 0x212428,3,"sta_deauth_act_handle",0x1f7);
  }
  return 0;
}

