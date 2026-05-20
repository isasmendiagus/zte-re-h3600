// module: mt7915.ko
// function: printCNNum @ 0x1554b4
// size: 200 bytes
//

undefined4 printCNNum(int param_1,char *param_2,undefined4 param_3,undefined4 param_4)

{
  size_t sVar1;
  uint uVar2;
  undefined4 *puVar3;
  
  uVar2 = *(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff;
  if (uVar2 == 0x7615 || uVar2 == 0x7622) {
    if (*(char *)(param_1 + 0xa7c2ec) != '\n') {
      setCNNum(param_1,0,uVar2,*(char *)(param_1 + 0xa7c2ec),param_4);
    }
    sVar1 = strlen(param_2);
    puVar3 = (undefined4 *)(param_1 + 0xa789e0);
    sprintf(param_2 + sVar1,"%-32s= ","Condition Number ");
    do {
      sVar1 = strlen(param_2);
      puVar3 = puVar3 + 1;
      sprintf(param_2 + sVar1,"%-2d ",*puVar3);
    } while (puVar3 != (undefined4 *)(param_1 + 0xa78a08));
    sVar1 = strlen(param_2);
    (param_2 + sVar1)[0] = '\n';
    (param_2 + sVar1)[1] = '\0';
  }
  return 1;
}

