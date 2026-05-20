// module: mt7915.ko
// function: mt7915_get_rx_stat_user @ 0x179500
// size: 344 bytes
//

undefined4 mt7915_get_rx_stat_user(int param_1,short param_2,int param_3,uint *param_4)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  
  iVar1 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  uVar6 = (uint)*(byte *)(iVar1 + 0x224);
  if (uVar6 == 0) {
LAB_00179564:
    uVar6 = 0x14;
  }
  else {
    if (uVar6 == 1) {
      uVar6 = 0x28;
      goto LAB_0017956c;
    }
    if (uVar6 != 2) {
      if (uVar6 == 3) {
        uVar6 = 0xa0;
        goto LAB_0017956c;
      }
      if (uVar6 == 4) {
        uVar6 = 10;
        goto LAB_0017956c;
      }
      if (uVar6 == 5) goto LAB_0017956c;
      if (uVar6 != 6) goto LAB_00179564;
    }
    uVar6 = 0x50;
  }
LAB_0017956c:
  param_1 = param_1 + (param_2 * 0x5a + param_3) * 4;
  uVar5 = *(uint *)(param_1 + 0xa7bf44);
  uVar3 = (uint)((ulonglong)uVar6 * (ulonglong)uVar5);
  iVar4 = uVar6 * ((int)uVar5 >> 0x1f) + (int)((ulonglong)uVar6 * (ulonglong)uVar5 >> 0x20);
  uVar2 = iVar4 * 0x200 | uVar3 >> 0x17;
  iVar1 = ((uVar2 << 5 | uVar3 * 0x200 >> 0x1b) - (uVar2 + (uVar3 * 0x4000 < uVar3 * 0x200))) +
          iVar4 + (uint)CARRY4(uVar3 * 0x3e00,uVar3);
  uVar2 = uVar3 * 1000000 >> 0x18 |
          (((iVar1 * 0x40 | uVar3 * 0x3e01 >> 0x1a) -
           (iVar1 + (uint)(uVar3 * 0xf8040 < uVar3 * 0x3e01))) + iVar4 +
          (uint)CARRY4(uVar3 * 999999,uVar3)) * 0x100;
  if (0x80000 < (int)uVar5) {
    uVar2 = uVar2 - ((int)(uVar6 * 1000000) >> 4);
  }
  *param_4 = uVar2;
  param_4[1] = *(uint *)(param_1 + 0xa7bf94);
  param_4[2] = *(uint *)(param_1 + 0xa7c014);
  return 0;
}

