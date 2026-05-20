// module: mt7915.ko
// function: check_vht_op_bw @ 0x1032f8
// size: 124 bytes
//

char check_vht_op_bw(char *param_1)

{
  byte bVar1;
  char cVar2;
  byte bVar3;
  
  cVar2 = *param_1;
  bVar3 = param_1[1];
  bVar1 = param_1[2];
  if ((cVar2 != '\x02') && (cVar2 != '\x03')) {
    if (cVar2 != '\x01') {
      return '\0';
    }
    if (bVar1 != 0) {
      if (bVar3 < bVar1) {
        bVar3 = bVar1 - bVar3;
      }
      else {
        bVar3 = bVar3 - bVar1;
      }
      if (bVar3 != 8) {
        if (bVar3 < 0x10) {
          cVar2 = '\0';
        }
        else {
          cVar2 = '\x03';
        }
        return cVar2;
      }
      return '\x02';
    }
  }
  return cVar2;
}

