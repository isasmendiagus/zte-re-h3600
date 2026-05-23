// module: mt7915.ko
// function: bss_table_maintenance @ 0x11020c
// size: 504 bytes
//

void bss_table_maintenance
               (undefined4 param_1,undefined4 param_2,uint *param_3,int param_4,byte param_5)

{
  int iVar1;
  int iVar2;
  byte bVar3;
  uint *puVar4;
  void *__dest;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint *__dest_00;
  bool bVar8;
  
  uVar6 = *param_3;
  iVar1 = GetStaCfgByWdev();
  if (uVar6 != 0) {
    uVar7 = 0;
LAB_001102ac:
    do {
      if (param_3[uVar7 * 0x2bd + 0x30] == param_3[uVar7 * 0x2bd + 0x31]) {
        iVar2 = param_4 * 100 - jiffies;
        bVar3 = *(char *)((int)param_3 + uVar7 * 0xaf4 + 0xbd) + 1;
        *(byte *)((int)param_3 + uVar7 * 0xaf4 + 0xbd) = bVar3;
        if (((int)(iVar2 + param_3[uVar7 * 0x2bd + 0x31]) < 0) || (param_5 < bVar3)) {
LAB_00110300:
          if (((*(uint *)(iVar1 + 0x212464) & 0x80) == 0) ||
             (iVar2 = memcmp((void *)((int)param_3 + uVar7 * 0xaf4 + 0x9d),
                             (void *)(iVar1 + 0x212406),(uint)*(byte *)(iVar1 + 0x212426)),
             iVar2 != 0)) {
            uVar6 = uVar6 - 1;
            puVar4 = param_3 + uVar7 * 0x2bd + 0x3fb;
            uVar5 = uVar7;
            __dest_00 = param_3 + uVar7 * 0x2bd + 2;
            while (bVar8 = uVar5 < uVar6, uVar5 = uVar5 + 1, bVar8) {
              __dest = (void *)__dest_00[0x13c];
              memmove(__dest_00,__dest_00 + 0x2bd,0xaf4);
              if (__dest != (void *)0x0) {
                RTMPZeroMemory(__dest,0x400);
                memmove(__dest,(void *)__dest_00[0x3f9],(uint)*(ushort *)((int)puVar4 + -2));
                __dest_00[0x13c] = (uint)__dest;
              }
              puVar4 = puVar4 + 0x2bd;
              __dest_00 = __dest_00 + 0x2bd;
            }
            uVar5 = param_3[uVar6 * 0x2bd + 0x13e];
            __memzero(param_3 + uVar6 * 0x2bd + 2,0xaf4);
            if (uVar5 != 0) {
              RTMPZeroMemory(uVar5,0x400);
            }
            if (uVar6 <= uVar7) break;
            goto LAB_001102ac;
          }
        }
      }
      else {
        param_3[uVar7 * 0x2bd + 0x30] = param_3[uVar7 * 0x2bd + 0x31];
        *(undefined1 *)((int)param_3 + uVar7 * 0xaf4 + 0xbd) = 0;
        if ((int)((param_4 * 100 - jiffies) + param_3[uVar7 * 0x2bd + 0x31]) < 0) goto LAB_00110300;
      }
      uVar7 = uVar7 + 1;
    } while (uVar7 < uVar6);
  }
  *param_3 = uVar6;
  return;
}

