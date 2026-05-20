// module: mt7915.ko
// function: mtf_txpower_boost @ 0x1a1108
// size: 488 bytes
//

void mtf_txpower_boost(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  
  iVar1 = param_2 * 0xa1;
  iVar2 = param_1 + iVar1 + 0x794d68;
  TxPwrUpCtrl(param_1,param_2,0,iVar2);
  TxPwrUpCtrl(param_1,param_2,1,iVar2 + 4);
  TxPwrUpCtrl(param_1,param_2,2,param_1 + iVar1 + 0x794d74);
  TxPwrUpCtrl(param_1,param_2,3,param_1 + iVar1 + 0x794d7c);
  TxPwrUpCtrl(param_1,param_2,4,param_1 + iVar1 + 0x794d85);
  TxPwrUpCtrl(param_1,param_2,5,param_1 + iVar1 + 0x794d91);
  TxPwrUpCtrl(param_1,param_2,6,param_1 + iVar1 + 0x794d9d);
  TxPwrUpCtrl(param_1,param_2,7,param_1 + iVar1 + 0x794da9);
  TxPwrUpCtrl(param_1,param_2,8,param_1 + iVar1 + 0x794db5);
  TxPwrUpCtrl(param_1,param_2,9,param_1 + iVar1 + 0x794dc1);
  TxPwrUpCtrl(param_1,param_2,10,param_1 + iVar1 + 0x794dcd);
  TxPwrUpCtrl(param_1,param_2,0xb,param_1 + iVar1 + 0x794dd9);
  TxPwrUpCtrl(param_1,param_2,0xc,param_1 + iVar1 + 0x794de5);
  TxPwrUpCtrl(param_1,param_2,0xd,param_1 + iVar1 + 0x794df1);
  TxPwrUpCtrl(param_1,param_2,0xe,param_1 + iVar1 + 0x794dfd);
  return;
}

