// module: mt7915.ko
// function: GetTimBit @ 0x52f74
// size: 208 bytes
//

undefined4
GetTimBit(int param_1,uint param_2,byte *param_3,undefined1 *param_4,char *param_5,
         undefined1 *param_6,undefined1 *param_7)

{
  byte bVar1;
  uint uVar2;
  int iVar3;
  
  *param_3 = *(byte *)(param_1 + 1);
  *param_5 = *(char *)(param_1 + 2);
  *param_6 = *(undefined1 *)(param_1 + 3);
  bVar1 = *(byte *)(param_1 + 4);
  if ((*param_5 == '\0') && ((bVar1 & 1) != 0)) {
    *param_4 = 1;
  }
  else {
    *param_4 = 0;
  }
  uVar2 = bVar1 & 0xfe;
  if (((int)(uVar2 * 8) <= (int)param_2) &&
     ((int)param_2 < (int)(((uVar2 + (*param_3 - 4) & 0xff) + 1) * 8))) {
    uVar2 = (param_2 >> 3) - uVar2;
    iVar3 = 0;
    if ((uVar2 & 1) != 0) {
      iVar3 = 8;
    }
    if (((int)*(char *)(param_1 + (uVar2 & 0xff) + 5) >> ((param_2 & 0xf) - iVar3 & 0xff) & 1U) != 0
       ) {
      *param_7 = 1;
      return 1;
    }
  }
  *param_7 = 0;
  return 1;
}

