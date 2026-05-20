// module: mt7915.ko
// function: entrytb_aid_aquire @ 0x14ad2c
// size: 172 bytes
//

uint entrytb_aid_aquire(int *param_1)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  
  uVar3 = (uint)*(ushort *)(param_1 + 1);
  if (uVar3 <= *(ushort *)((int)param_1 + 6)) {
    iVar2 = *param_1;
    do {
      if (iVar2 != 0) {
        uVar1 = 1 << (uVar3 & 0x1f);
        uVar4 = *(uint *)(iVar2 + (uVar3 >> 5) * 4);
        if ((uVar4 & uVar1) == 0) {
          *(uint *)(iVar2 + (uVar3 >> 5) * 4) = uVar4 | uVar1;
          if (2 < DebugLevel) {
            printk("%s(): found non-occupied aid:%d, allocated from:%d\n","entrytb_aid_aquire",uVar3
                   ,(short)param_1[1]);
          }
          if (*(ushort *)((int)param_1 + 6) < uVar3) {
            return 0x7d8;
          }
          return uVar3;
        }
      }
      uVar3 = uVar3 + 1 & 0xffff;
    } while (uVar3 <= *(ushort *)((int)param_1 + 6));
  }
  return 0x7d8;
}

