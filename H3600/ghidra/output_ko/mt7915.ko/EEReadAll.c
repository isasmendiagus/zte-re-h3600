// module: mt7915.ko
// function: EEReadAll @ 0x26061c
// size: 72 bytes
//

void EEReadAll(undefined4 param_1,int param_2,uint param_3)

{
  int iVar1;
  uint uVar2;
  undefined2 *puVar3;
  undefined2 local_1a [3];
  
  if (param_3 >> 1 != 0) {
    puVar3 = (undefined2 *)(param_2 + -2);
    uVar2 = 0;
    do {
      iVar1 = uVar2 << 1;
      uVar2 = uVar2 + 1;
      chip_eeprom_read16(param_1,iVar1,local_1a);
      puVar3 = puVar3 + 1;
      *puVar3 = local_1a[0];
    } while (uVar2 != param_3 >> 1);
  }
  return;
}

