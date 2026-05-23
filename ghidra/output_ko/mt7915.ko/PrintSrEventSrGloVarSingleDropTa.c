// module: mt7915.ko
// function: PrintSrEventSrGloVarSingleDropTa @ 0x1711dc
// size: 60 bytes
//

void PrintSrEventSrGloVarSingleDropTa(int param_1)

{
  undefined1 uVar1;
  undefined1 uVar2;
  
  uVar1 = *(undefined1 *)(param_1 + 4);
  uVar2 = *(undefined1 *)(param_1 + 5);
  if (-1 < DebugLevel) {
    FUN_0016b708();
  }
  PrintSrGloVarSingleDropTa(param_1 + 0xc,uVar1,uVar2);
  return;
}

