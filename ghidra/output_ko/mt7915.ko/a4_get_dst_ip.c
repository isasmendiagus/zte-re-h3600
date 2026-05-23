// module: mt7915.ko
// function: a4_get_dst_ip @ 0x9f400
// size: 100 bytes
//

bool a4_get_dst_ip(int param_1,undefined4 *param_2)

{
  undefined1 *puVar1;
  undefined1 *puVar2;
  int iVar3;
  short sVar4;
  int iVar5;
  
  sVar4 = CONCAT11(*(undefined1 *)(param_1 + 0xc),*(undefined1 *)(param_1 + 0xd));
  if (sVar4 == -0x7f00) {
    iVar5 = 0xc;
    iVar3 = param_1;
    do {
      puVar1 = (undefined1 *)(iVar3 + 0xe);
      iVar5 = iVar5 + 2;
      puVar2 = (undefined1 *)(iVar3 + 0xf);
      iVar3 = iVar3 + 2;
      sVar4 = CONCAT11(*puVar1,*puVar2);
    } while (sVar4 == -0x7f00);
  }
  else {
    iVar5 = 0xc;
  }
  if (sVar4 == 0x800) {
    *param_2 = *(undefined4 *)(param_1 + iVar5 + 0x12);
  }
  return sVar4 == 0x800;
}

