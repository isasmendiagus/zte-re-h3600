// module: mt7915.ko
// function: mt_notify_call_chain @ 0x105b94
// size: 76 bytes
//

uint mt_notify_call_chain(int param_1,undefined4 param_2,undefined4 param_3)

{
  uint uVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  
  puVar2 = *(undefined4 **)(param_1 + 4);
  if (*(undefined4 **)(param_1 + 4) == (undefined4 *)0x0) {
    return 0;
  }
  do {
    puVar3 = (undefined4 *)puVar2[1];
    uVar1 = (*(code *)*puVar2)(puVar2,param_2,param_3);
    if ((uVar1 & 0x8000) != 0) {
      return uVar1;
    }
    puVar2 = puVar3;
  } while (puVar3 != (undefined4 *)0x0);
  return uVar1;
}

