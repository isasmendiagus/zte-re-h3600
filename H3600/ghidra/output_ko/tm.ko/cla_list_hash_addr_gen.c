// module: tm.ko
// function: cla_list_hash_addr_gen @ 0x17190
// size: 60 bytes
//

uint cla_list_hash_addr_gen(byte *param_1,int param_2)

{
  byte *pbVar1;
  uint uVar3;
  byte *pbVar2;
  
  uVar3 = 0;
  if (param_2 != 0) {
    uVar3 = 0;
    pbVar2 = param_1;
    do {
      pbVar1 = pbVar2 + 1;
      uVar3 = *(uint *)(crctable_04C11DB7 + ((uint)*pbVar2 ^ uVar3 >> 0x18) * 4) ^ uVar3 << 8;
      pbVar2 = pbVar1;
    } while (pbVar1 != param_1 + param_2);
  }
  return uVar3;
}

