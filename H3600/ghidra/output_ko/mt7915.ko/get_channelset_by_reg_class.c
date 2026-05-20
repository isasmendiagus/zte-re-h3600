// module: mt7915.ko
// function: get_channelset_by_reg_class @ 0x141b3c
// size: 284 bytes
//

byte * get_channelset_by_reg_class(int param_1,uint param_2,uint param_3)

{
  int iVar1;
  byte *pbVar2;
  uint uVar3;
  byte *pbVar4;
  
  param_1 = param_1 + 0x794c31;
  if ((param_3 & 0x1c0) == 0) {
    if ((param_3 & 0x20) == 0) {
      iVar1 = get_reg_table_by_country(param_1,param_3);
      if (iVar1 != 0) {
        pbVar2 = (byte *)(iVar1 + 0x20);
        uVar3 = (uint)*pbVar2;
        do {
          if ((param_2 == uVar3) || (pbVar2[1] == param_2)) goto LAB_00141be4;
          pbVar2 = pbVar2 + 0x20;
          uVar3 = (uint)*pbVar2;
        } while (uVar3 != 0);
      }
    }
    else {
      iVar1 = get_reg_table_by_country(param_1,param_3);
      if (iVar1 != 0) {
        pbVar2 = (byte *)(iVar1 + 0x30);
        uVar3 = (uint)*pbVar2;
        do {
          if ((param_2 == uVar3) || (pbVar2[1] == param_2)) {
            if ((param_2 ^ 0x80) < 3) {
              return pbVar2 + 0x19;
            }
LAB_00141be4:
            return pbVar2 + 9;
          }
          pbVar2 = pbVar2 + 0x30;
          uVar3 = (uint)*pbVar2;
        } while (uVar3 != 0);
      }
    }
  }
  else {
    iVar1 = get_reg_table_by_country(param_1,param_3);
    if (iVar1 != 0) {
      uVar3 = (uint)*(byte *)(iVar1 + 0x88);
      pbVar2 = (byte *)0x0;
      pbVar4 = (byte *)(iVar1 + 0xcd);
      do {
        while ((param_2 != uVar3 && (pbVar4[-0x44] != param_2))) {
          uVar3 = (uint)pbVar4[0x43];
          pbVar4 = pbVar4 + 0x88;
          if (uVar3 == 0) {
            return pbVar2;
          }
        }
        pbVar2 = pbVar4 + -0x3c;
        if ((param_2 ^ 0x80) < 8) {
          pbVar2 = pbVar4;
        }
        uVar3 = (uint)pbVar4[0x43];
        pbVar4 = pbVar4 + 0x88;
      } while (uVar3 != 0);
      return pbVar2;
    }
  }
  return (byte *)0x0;
}

