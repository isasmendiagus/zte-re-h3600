// module: mt7915.ko
// function: PMF_DeriveIGTK @ 0x219e08
// size: 40 bytes
//

void PMF_DeriveIGTK(undefined4 param_1,int param_2)

{
  undefined1 uVar1;
  undefined1 *puVar2;
  
  puVar2 = (undefined1 *)(param_2 + -1);
  do {
    uVar1 = RandomByte(param_1);
    puVar2 = puVar2 + 1;
    *puVar2 = uVar1;
  } while (puVar2 != (undefined1 *)(param_2 + 0x1f));
  return;
}

