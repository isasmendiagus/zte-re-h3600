// module: mt7915.ko
// function: bcolor_acquire_entry @ 0x16afdc
// size: 224 bytes
//

uint bcolor_acquire_entry(int param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  undefined8 uVar7;
  
  uVar7 = RcGetBandIdx(*(undefined4 *)(param_2 + 8));
  uVar1 = jiffies;
  uVar3 = jiffies % 0x3f;
  uVar5 = uVar3 + 0x3f;
  iVar6 = param_1 + (int)uVar7 * 0x100 + 0x31d4;
  _raw_spin_lock_bh(iVar6,(int)((ulonglong)uVar7 >> 0x20),jiffies * 0x4104105);
  while( true ) {
    uVar4 = uVar3;
    if (0x3e < uVar3) {
      uVar4 = uVar3 + (uVar3 / 0x3f + (uVar3 - uVar3 / 0x3f >> 1) >> 5) * -0x3f & 0xff;
    }
    iVar2 = param_1 + 0x1000 + ((int)uVar7 * 0x40 + uVar4 + 0x75e) * 4;
    if (*(int *)(iVar2 + 0x360) == 0) break;
    uVar3 = uVar3 + 1 & 0xff;
    if (uVar5 <= uVar3) {
LAB_0016b0a0:
      _raw_spin_unlock_bh(iVar6);
      if (uVar3 == uVar5) {
        uVar1 = 0;
      }
      else {
        uVar1 = uVar4 + 1 & 0xff;
      }
      return uVar1;
    }
  }
  *(uint *)(iVar2 + 0x360) = uVar1;
  goto LAB_0016b0a0;
}

