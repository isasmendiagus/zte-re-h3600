// module: plat-zxylzb_9128S.ko
// function: proc_parse_mac @ 0x10210
// size: 120 bytes
//

undefined4 proc_parse_mac(char *param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  undefined1 *puVar4;
  undefined4 uStack_20;
  undefined1 auStack_1c [4];
  undefined1 auStack_18 [4];
  undefined1 auStack_14 [4];
  undefined1 auStack_10 [4];
  undefined1 auStack_c [4];
  
  iVar1 = sscanf(param_1,"%x:%x:%x:%x:%x:%x",&uStack_20,auStack_1c,auStack_18,auStack_14,auStack_10,
                 auStack_c);
  if (iVar1 == 6) {
    puVar4 = (undefined1 *)(param_2 + -1);
    puVar3 = &uStack_20;
    do {
      puVar4 = puVar4 + 1;
      *puVar4 = (char)*puVar3;
      puVar3 = puVar3 + 1;
    } while (puVar4 != (undefined1 *)(param_2 + 5));
    uVar2 = 0;
  }
  else {
    uVar2 = 0xffffffff;
  }
  return uVar2;
}

