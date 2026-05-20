// module: mt7915.ko
// function: BN_consttime_swap @ 0x20dc70
// size: 720 bytes
//

void BN_consttime_swap(uint param_1,int *param_2,int *param_3,int param_4)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  
  if (param_2 == param_3) {
    printk(&_LC0,0x3ca);
    dump_stack();
  }
  if ((param_1 - 1 & param_1) != 0) {
    printk(&_LC1,0x3cb);
    dump_stack();
  }
  uVar1 = 0xffffffff - ((int)(param_1 - 1) >> 0x1f);
  uVar2 = (param_3[1] ^ param_2[1]) & uVar1;
  param_2[1] = param_2[1] ^ uVar2;
  param_3[1] = uVar2 ^ param_3[1];
  switch(param_4) {
  default:
    if (10 < param_4) {
      iVar3 = 10;
      do {
        uVar4 = *(uint *)(*param_2 + iVar3 * 4);
        uVar2 = (*(uint *)(*param_3 + iVar3 * 4) ^ uVar4) & uVar1;
        *(uint *)(*param_2 + iVar3 * 4) = uVar4 ^ uVar2;
        *(uint *)(*param_3 + iVar3 * 4) = uVar2 ^ *(uint *)(*param_3 + iVar3 * 4);
        iVar3 = iVar3 + 1;
      } while (iVar3 != param_4);
    }
  case 10:
    uVar2 = *(uint *)(*param_2 + 0x24);
    uVar4 = (*(uint *)(*param_3 + 0x24) ^ uVar2) & uVar1;
    *(uint *)(*param_2 + 0x24) = uVar2 ^ uVar4;
    *(uint *)(*param_3 + 0x24) = uVar4 ^ *(uint *)(*param_3 + 0x24);
  case 9:
    uVar2 = *(uint *)(*param_2 + 0x20);
    uVar4 = (*(uint *)(*param_3 + 0x20) ^ uVar2) & uVar1;
    *(uint *)(*param_2 + 0x20) = uVar2 ^ uVar4;
    *(uint *)(*param_3 + 0x20) = uVar4 ^ *(uint *)(*param_3 + 0x20);
  case 8:
    uVar2 = *(uint *)(*param_2 + 0x1c);
    uVar4 = (*(uint *)(*param_3 + 0x1c) ^ uVar2) & uVar1;
    *(uint *)(*param_2 + 0x1c) = uVar2 ^ uVar4;
    *(uint *)(*param_3 + 0x1c) = uVar4 ^ *(uint *)(*param_3 + 0x1c);
  case 7:
    uVar2 = *(uint *)(*param_2 + 0x18);
    uVar4 = (*(uint *)(*param_3 + 0x18) ^ uVar2) & uVar1;
    *(uint *)(*param_2 + 0x18) = uVar2 ^ uVar4;
    *(uint *)(*param_3 + 0x18) = uVar4 ^ *(uint *)(*param_3 + 0x18);
  case 6:
    uVar2 = *(uint *)(*param_2 + 0x14);
    uVar4 = (*(uint *)(*param_3 + 0x14) ^ uVar2) & uVar1;
    *(uint *)(*param_2 + 0x14) = uVar2 ^ uVar4;
    *(uint *)(*param_3 + 0x14) = uVar4 ^ *(uint *)(*param_3 + 0x14);
  case 5:
    uVar2 = *(uint *)(*param_2 + 0x10);
    uVar4 = (*(uint *)(*param_3 + 0x10) ^ uVar2) & uVar1;
    *(uint *)(*param_2 + 0x10) = uVar2 ^ uVar4;
    *(uint *)(*param_3 + 0x10) = uVar4 ^ *(uint *)(*param_3 + 0x10);
  case 4:
    uVar2 = *(uint *)(*param_2 + 0xc);
    uVar4 = (*(uint *)(*param_3 + 0xc) ^ uVar2) & uVar1;
    *(uint *)(*param_2 + 0xc) = uVar2 ^ uVar4;
    *(uint *)(*param_3 + 0xc) = uVar4 ^ *(uint *)(*param_3 + 0xc);
  case 3:
    uVar2 = *(uint *)(*param_2 + 8);
    uVar4 = (*(uint *)(*param_3 + 8) ^ uVar2) & uVar1;
    *(uint *)(*param_2 + 8) = uVar2 ^ uVar4;
    *(uint *)(*param_3 + 8) = uVar4 ^ *(uint *)(*param_3 + 8);
  case 2:
    uVar2 = *(uint *)(*param_2 + 4);
    uVar4 = (*(uint *)(*param_3 + 4) ^ uVar2) & uVar1;
    *(uint *)(*param_2 + 4) = uVar2 ^ uVar4;
    *(uint *)(*param_3 + 4) = uVar4 ^ *(uint *)(*param_3 + 4);
  case 1:
    uVar2 = *(uint *)*param_2;
    uVar1 = uVar1 & (*(uint *)*param_3 ^ uVar2);
    *(uint *)*param_2 = uVar2 ^ uVar1;
    *(uint *)*param_3 = uVar1 ^ *(uint *)*param_3;
    return;
  }
}

