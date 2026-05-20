// module: mt7915.ko
// function: mt_TxBFFwInit @ 0x8541c
// size: 76 bytes
//

void mt_TxBFFwInit(int param_1)

{
  undefined4 uVar1;
  bool bVar2;
  
  bVar2 = *(int *)(param_1 + 0x79599c) == 0;
  if (bVar2) {
    uVar1 = 0;
  }
  else {
    uVar1 = 4;
  }
  CmdETxBfSoundingPeriodicTriggerCtrl(param_1,!bVar2,0,uVar1,0,0);
  return;
}

