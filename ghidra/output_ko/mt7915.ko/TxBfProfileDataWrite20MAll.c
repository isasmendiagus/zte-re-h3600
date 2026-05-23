// module: mt7915.ko
// function: TxBfProfileDataWrite20MAll @ 0x88164
// size: 68 bytes
//

bool TxBfProfileDataWrite20MAll(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  bool bVar1;
  int iVar2;
  undefined1 auStack_210 [516];
  
  iVar2 = TxBfProfileDataFormatTranslate(param_1,param_3,auStack_210);
  bVar1 = false;
  if (iVar2 != 0) {
    iVar2 = CmdETxBfPfmuProfileDataWrite20MAll(param_1,param_2,auStack_210);
    bVar1 = iVar2 == 0;
  }
  return bVar1;
}

