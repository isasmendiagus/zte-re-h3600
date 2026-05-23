// module: mt7915.ko
// function: isIgmpPkt @ 0x240dd8
// size: 92 bytes
//

bool isIgmpPkt(char *param_1,ushort *param_2)

{
  if ((((*param_1 == '\x01') && (param_1[1] == '\0')) && (param_1[2] == '^')) &&
     ((ushort)(*param_2 << 8 | *param_2 >> 8) == 0x800)) {
    return *(char *)((int)param_2 + 0xb) == '\x02';
  }
  return false;
}

