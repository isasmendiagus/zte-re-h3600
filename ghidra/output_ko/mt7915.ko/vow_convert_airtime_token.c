// module: mt7915.ko
// function: vow_convert_airtime_token @ 0x42d34
// size: 248 bytes
//

undefined2 vow_convert_airtime_token(int param_1,int param_2,int param_3)

{
  longlong lVar1;
  undefined2 uVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  uint unaff_r11;
  
  iVar3 = param_1 + param_3 * 0x1c;
  uVar5 = 1 << *(sbyte *)(param_1 + 0xa7a2ee) & 0xffff;
  if (param_2 == 1) {
    unaff_r11 = (uint)*(byte *)(iVar3 + 0xa7982d);
  }
  if (param_2 != 1) {
    unaff_r11 = (uint)*(byte *)(iVar3 + 0xa7982c);
  }
  iVar3 = (uint)CARRY4(uVar5 * 0x3e00,uVar5) - (uint)(uVar5 * 0x4000 < uVar5 * 0x200);
  lVar1 = (ulonglong)unaff_r11 * (ulonglong)(uVar5 * 1000000);
  uVar4 = (uint)lVar1;
  uVar2 = div64_u64(uVar4 << 3,
                    (unaff_r11 *
                     (((iVar3 * 0x40 | uVar5 * 0x3e01 >> 0x1a) -
                      (iVar3 + (uint)(uVar5 * 0xf8040 < uVar5 * 0x3e01))) +
                     (uint)CARRY4(uVar5 * 999999,uVar5)) + (int)((ulonglong)lVar1 >> 0x20)) * 8 |
                    uVar4 >> 0x1d,100000000,0);
  if (2 < DebugLevel) {
    printk("%s: period %dus, ratio %u, available time %u, token %u\n","vow_convert_airtime_token",
           uVar5,unaff_r11,1000000,uVar2);
  }
  return uVar2;
}

