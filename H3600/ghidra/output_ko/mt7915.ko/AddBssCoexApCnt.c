// module: mt7915.ko
// function: AddBssCoexApCnt @ 0x10000
// size: 164 bytes
//

void AddBssCoexApCnt(int param_1,int param_2,undefined4 *param_3)

{
  char cVar1;
  undefined2 uVar2;
  int iVar3;
  undefined1 *__s1;
  int iVar4;
  
  __s1 = g_tBssCoexApEntryTable + 8;
  iVar4 = 0;
  do {
    if (__s1[-8] == '\0') goto LAB_0001005c;
    iVar3 = memcmp(__s1,param_3,6);
    iVar4 = iVar4 + 1;
    if ((iVar3 == 0) && (param_2 == *(int *)(__s1 + -4))) {
      return;
    }
    __s1 = __s1 + 0x10;
  } while (iVar4 != 0x80);
  iVar4 = 0;
LAB_0001005c:
  iVar3 = iVar4 * 0x10;
  *(undefined4 *)(g_tBssCoexApEntryTable + iVar3 + 8) = *param_3;
  uVar2 = *(undefined2 *)(param_3 + 1);
  cVar1 = *(char *)(param_1 + 0x795650);
  *(int *)(g_tBssCoexApEntryTable + iVar3 + 4) = param_2;
  *(undefined2 *)(g_tBssCoexApEntryTable + iVar3 + 0xc) = uVar2;
  g_tBssCoexApEntryTable[iVar4 * 0x10] = 1;
  *(char *)(param_1 + 0x795650) = cVar1 + '\x01';
  return;
}

