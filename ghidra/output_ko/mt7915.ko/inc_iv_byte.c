// module: mt7915.ko
// function: inc_iv_byte @ 0x118968
// size: 120 bytes
//

void inc_iv_byte(int param_1,uint param_2,char param_3)

{
  byte bVar1;
  byte *pbVar2;
  byte bVar3;
  uint uVar4;
  uint uVar5;
  
  if (param_2 != 0) {
    uVar4 = 0;
    pbVar2 = (byte *)(param_1 + -1);
    uVar5 = uVar4;
    do {
      pbVar2 = pbVar2 + 1;
      bVar1 = *pbVar2;
      bVar3 = bVar1 + param_3;
      if (uVar4 == 1) {
        bVar3 = bVar1 + 1;
      }
      *pbVar2 = bVar3;
      uVar4 = 1;
      if (bVar1 < bVar3) {
        if (uVar5 < param_2) {
          return;
        }
        break;
      }
      uVar5 = uVar5 + 1;
    } while (uVar5 != param_2);
  }
  if (DebugLevel < 2) {
    return;
  }
  printk("!!! inc_iv_byte overflow !!!\n");
  return;
}

