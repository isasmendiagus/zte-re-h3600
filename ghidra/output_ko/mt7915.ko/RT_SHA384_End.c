// module: mt7915.ko
// function: RT_SHA384_End @ 0x126540
// size: 176 bytes
//

void RT_SHA384_End(void *param_1,void *param_2)

{
  uint uVar1;
  uint uVar2;
  uint *puVar3;
  uint uVar5;
  uint *puVar4;
  
  *(undefined1 *)((int)param_1 + *(int *)((int)param_1 + 200) + 0x48) = 0x80;
  if (0x77 < *(uint *)((int)param_1 + 200)) {
    RT_SHA384_Hash();
  }
  uVar1 = *(uint *)((int)param_1 + 0x40);
  uVar2 = *(int *)((int)param_1 + 0x44) << 3;
  uVar5 = uVar1 << 3;
  *(uint *)((int)param_1 + 0xc0) =
       (uVar2 & 0xff | uVar1 >> 0x1d) << 0x18 | (uVar2 >> 8 & 0xff) << 0x10 |
       (uVar2 >> 0x10 & 0xff) << 8 | uVar2 >> 0x18;
  *(uint *)((int)param_1 + 0xc4) =
       uVar1 << 0x1b | (uVar5 >> 8 & 0xff) << 0x10 | (uVar5 >> 0x10 & 0xff) << 8 | uVar5 >> 0x18;
  RT_SHA384_Hash(param_1);
  puVar3 = (uint *)((int)param_1 + -8);
  do {
    puVar4 = puVar3 + 2;
    uVar5 = *puVar4;
    uVar2 = puVar3[3];
    puVar3[3] = uVar5 << 0x18 | (uVar5 >> 8 & 0xff) << 0x10 | (uVar5 >> 0x10 & 0xff) << 8 |
                uVar5 >> 0x18;
    *puVar4 = uVar2 << 0x18 | (uVar2 >> 8 & 0xff) << 0x10 | (uVar2 >> 0x10 & 0xff) << 8 |
              uVar2 >> 0x18;
    puVar3 = puVar4;
  } while (puVar4 != (uint *)((int)param_1 + 0x38));
  memmove(param_2,param_1,0x30);
  return;
}

