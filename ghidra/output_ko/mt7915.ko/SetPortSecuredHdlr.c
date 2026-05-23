// module: mt7915.ko
// function: SetPortSecuredHdlr @ 0xc4794
// size: 164 bytes
//

undefined4 SetPortSecuredHdlr(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined1 uStack_19;
  
  iVar3 = *(int *)(param_2 + 4);
  iVar1 = GetStaCfgByWdev(param_1,iVar3);
  iVar2 = GetAssociatedAPByWdev(param_1,iVar3);
  *(undefined1 *)(iVar3 + 0x888) = 1;
  RTMP_IndicateMediaState(param_1);
  _raw_spin_lock_bh(param_1 + 0x285958);
  if (iVar2 != 0) {
    *(undefined1 *)(param_1 + (uint)*(ushort *)(iVar2 + 0xe0) * 0x620 + 0x2f762) =
         *(undefined1 *)(iVar3 + 0x888);
    *(undefined4 *)(iVar2 + 0xadc) = 0;
  }
  _raw_spin_unlock_bh(param_1 + 0x285958);
  RTMPCancelTimer(iVar1 + 0x212470,&uStack_19);
  return 0;
}

