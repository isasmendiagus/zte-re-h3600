// module: mt7915.ko
// function: MATProto_ARP_Rx @ 0x7a300
// size: 140 bytes
//

undefined6 * MATProto_ARP_Rx(undefined4 param_1,undefined4 param_2,int param_3)

{
  undefined6 *__src;
  byte bVar1;
  
  bVar1 = (((((*(byte *)(param_3 + 0x12) != 0 || *(char *)(param_3 + 0x13) != '\0') ||
             *(char *)(param_3 + 0x14) != '\0') || *(char *)(param_3 + 0x15) != '\0') ||
           *(char *)(param_3 + 0x16) != '\0') || *(char *)(param_3 + 0x17) != '\0') &
          ~*(byte *)(param_3 + 0x12);
  if (*(int *)(param_3 + 0x18) == 0) {
    bVar1 = 0;
  }
  if ((bVar1 != 0) && (__src = (undefined6 *)FUN_0007a21c(), __src != (undefined6 *)0x0)) {
    memmove((void *)(param_3 + 0x12),__src,6);
    return __src;
  }
  return &BROADCAST_ADDR;
}

