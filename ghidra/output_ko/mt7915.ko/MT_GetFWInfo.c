// module: mt7915.ko
// function: MT_GetFWInfo @ 0x27de70
// size: 468 bytes
//

undefined4 MT_GetFWInfo(int param_1,void *param_2)

{
  uint uVar1;
  char *__s2;
  char cVar2;
  undefined **ppuVar3;
  undefined **ppuVar4;
  uint uVar5;
  int iVar6;
  char cVar7;
  undefined1 uStack_60;
  undefined1 local_5f;
  undefined2 local_5e;
  undefined2 local_5c;
  undefined2 local_5a;
  undefined4 local_58;
  undefined4 local_54;
  undefined *apuStack_50 [12];
  
  local_58 = 0;
  apuStack_50[0] = &DAT_00327330;
  apuStack_50[1] = &DAT_00327334;
  apuStack_50[2] = &DAT_00327338;
  apuStack_50[3] = &DAT_0032733c;
  local_54 = 0;
  local_5e = 0;
  apuStack_50[4] = &DAT_00327340;
  apuStack_50[5] = &DAT_00327344;
  apuStack_50[6] = &DAT_00327348;
  apuStack_50[7] = &DAT_0032734c;
  local_5c = 0;
  local_5a = 0;
  iVar6 = *(int *)(*(int *)(*(int *)(((uint)&uStack_60 & 0xffffe000) + 0xc) + 0x314) + 4);
  apuStack_50[8] = &DAT_00327350;
  apuStack_50[9] = &DAT_00327354;
  apuStack_50[10] = &DAT_00327358;
  apuStack_50[0xb] = &DAT_0032735c;
  ppuVar3 = apuStack_50;
  while( true ) {
    ppuVar4 = ppuVar3 + 1;
    __s2 = strstr((char *)(iVar6 + 199),*ppuVar3);
    if (__s2 != (char *)0x0) break;
    ppuVar3 = ppuVar4;
    if (ppuVar4 == (undefined **)&stack0xffffffe0) {
      return 1;
    }
  }
  uVar5 = 0;
  local_5f = *(undefined1 *)(param_1 + 0x286285);
  os_move_mem(&local_5e,__s2 + 7,2);
  os_move_mem(&local_5c,__s2 + 10,2);
  os_move_mem(&local_5a,__s2 + 0xd,2);
  os_move_mem(&local_58,__s2 + 0x14,4);
  os_move_mem((void *)((int)&local_54 + 2),__s2 + 4,2);
  ppuVar3 = apuStack_50;
  do {
    uVar5 = uVar5 + 1;
    iVar6 = os_cmp_mem(*ppuVar3,__s2,3);
    if (iVar6 == 0) {
      uVar1 = (uVar5 & 0xff) / 10;
      cVar7 = (char)uVar1;
      cVar2 = (char)uVar5 + cVar7 * -10 + '0';
      cVar7 = cVar7 + (char)(uVar1 / 10) * -10 + '0';
      goto LAB_0027df98;
    }
    ppuVar3 = ppuVar3 + 1;
  } while (uVar5 != 0xc);
  cVar2 = '0';
  cVar7 = '0';
LAB_0027df98:
  local_54._0_2_ = CONCAT11(cVar2,cVar7);
  os_move_mem(param_2,&local_5f,1);
  os_move_mem((void *)((int)param_2 + 1),&local_58,8);
  os_move_mem((void *)((int)param_2 + 9),&local_5e,6);
  os_move_mem((void *)((int)param_2 + 0xf),
              (void *)(*(int *)(param_1 + 0xa78540) + *(int *)(param_1 + 0xa78544) + -0x13),0xf);
  return 0;
}

