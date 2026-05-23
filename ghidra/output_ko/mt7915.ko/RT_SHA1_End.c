// module: mt7915.ko
// function: RT_SHA1_End @ 0x125a2c
// size: 164 bytes
//

void RT_SHA1_End(void *param_1,void *param_2)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint *puVar4;
  
  *(undefined1 *)((int)param_1 + *(int *)((int)param_1 + 0x60) + 0x20) = 0x80;
  if (0x37 < *(uint *)((int)param_1 + 0x60)) {
    RT_SHA1_Hash();
  }
  uVar2 = *(uint *)((int)param_1 + 0x18);
  uVar3 = *(int *)((int)param_1 + 0x1c) << 3;
  uVar1 = uVar2 << 3;
  *(uint *)((int)param_1 + 0x58) =
       (uVar3 & 0xff | uVar2 >> 0x1d) << 0x18 | (uVar3 >> 8 & 0xff) << 0x10 |
       (uVar3 >> 0x10 & 0xff) << 8 | uVar3 >> 0x18;
  *(uint *)((int)param_1 + 0x5c) =
       uVar2 << 0x1b | (uVar1 >> 8 & 0xff) << 0x10 | (uVar1 >> 0x10 & 0xff) << 8 | uVar1 >> 0x18;
  RT_SHA1_Hash(param_1);
  puVar4 = (uint *)((int)param_1 + -4);
  do {
    puVar4 = puVar4 + 1;
    uVar3 = *puVar4;
    *puVar4 = uVar3 << 0x18 | (uVar3 >> 8 & 0xff) << 0x10 | (uVar3 >> 0x10 & 0xff) << 8 |
              uVar3 >> 0x18;
  } while (puVar4 != (uint *)((int)param_1 + 0x10));
  memmove(param_2,param_1,0x14);
  return;
}

