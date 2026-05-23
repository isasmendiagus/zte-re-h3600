// module: mt7915.ko
// function: ATEExit @ 0x269584
// size: 4 bytes
//

undefined4 ATEExit(int param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  
  uVar2 = *(undefined4 *)(param_1 + 0xa39fd4);
  uVar1 = *(undefined4 *)(param_1 + 0xa39fd0);
  os_free_mem(*(undefined4 *)(param_1 + 0xa39fd8));
  os_free_mem(uVar2);
  os_free_mem(uVar1);
  if ((*(uint *)(param_1 + 0x286280) & 0xfffffffb) == 1) {
    complete(param_1 + 0xa77ba4);
  }
  complete(param_1 + 0xa77b90);
  return 0;
}

