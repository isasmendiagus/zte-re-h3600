// module: mt7915.ko
// function: MacAddrRandomBssid @ 0x12f358
// size: 60 bytes
//

void MacAddrRandomBssid(undefined4 param_1,byte *param_2)

{
  byte bVar1;
  byte *pbVar2;
  
  pbVar2 = param_2 + -1;
  do {
    bVar1 = RandomByte(param_1);
    pbVar2 = pbVar2 + 1;
    *pbVar2 = bVar1;
  } while (pbVar2 != param_2 + 5);
  *param_2 = *param_2 & 0xfc | 2;
  return;
}

