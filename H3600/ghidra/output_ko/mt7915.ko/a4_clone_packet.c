// module: mt7915.ko
// function: a4_clone_packet @ 0x9f708
// size: 32 bytes
//

void a4_clone_packet(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  
  iVar1 = skb_copy(param_3,0x20);
  if (iVar1 != 0) {
    *(undefined4 *)(iVar1 + 0x18) = param_2;
  }
  return;
}

