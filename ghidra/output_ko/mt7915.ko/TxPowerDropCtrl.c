// module: mt7915.ko
// function: TxPowerDropCtrl @ 0xed684
// size: 120 bytes
//

bool TxPowerDropCtrl(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  
  uVar3 = param_2 - 0x5b;
  if (uVar3 < 9) {
    uVar2 = 0;
  }
  else {
    uVar3 = param_2 - 0x3d;
    if (uVar3 < 0x1e) {
      uVar2 = 2;
    }
    else {
      uVar3 = param_2 - 0x1f;
      if (uVar3 < 0x1e) {
        uVar2 = 6;
      }
      else {
        uVar3 = param_2 - 0x10;
        if (uVar3 < 0xf) {
          uVar2 = 0xc;
        }
        else {
          uVar3 = param_2 - 10;
          if (uVar3 < 6) {
            uVar2 = 0x12;
          }
          else if (param_2 - 1U < 9) {
            uVar2 = 0x18;
          }
          else {
            uVar2 = 0;
          }
        }
      }
    }
  }
  iVar1 = MtCmdTxPowerDropCtrl(param_1,uVar2,param_3,uVar3,param_4);
  return iVar1 == 0;
}

