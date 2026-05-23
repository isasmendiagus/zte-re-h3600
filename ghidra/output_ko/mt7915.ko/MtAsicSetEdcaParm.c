// module: mt7915.ko
// function: MtAsicSetEdcaParm @ 0x199908
// size: 216 bytes
//

void MtAsicSetEdcaParm(undefined4 param_1,undefined4 param_2,undefined1 param_3,char *param_4)

{
  int iVar1;
  char cVar2;
  byte bVar3;
  undefined2 uVar4;
  undefined1 uVar5;
  undefined4 *puVar6;
  uint uVar7;
  char *pcVar8;
  undefined1 auStack_1a8 [188];
  undefined4 local_ec;
  undefined4 local_e8;
  undefined4 local_e4;
  undefined1 auStack_e0 [188];
  
  os_zero_mem(&local_ec,0xc4);
  if ((param_4 != (char *)0x0) && (*param_4 != '\0')) {
    pcVar8 = param_4 + 0x12;
    uVar7 = 0;
    local_ec = CONCAT13(param_3,(undefined3)local_ec);
    local_ec = CONCAT31(local_ec._1_3_,4);
    local_ec._0_3_ = CONCAT12(1,(undefined2)local_ec);
    local_ec = CONCAT13(param_3,(undefined3)local_ec);
    puVar6 = &local_ec;
    do {
      *(undefined1 *)((int)puVar6 + 5) = 0xf;
      uVar5 = asic_get_hwq_from_ac(param_1,param_2,uVar7 & 0xff);
      cVar2 = param_4[0xb];
      bVar3 = param_4[0xf];
      pcVar8 = pcVar8 + 2;
      uVar4 = *(undefined2 *)pcVar8;
      *(char *)((int)puVar6 + 6) = param_4[7];
      *(char *)((int)puVar6 + 7) = cVar2;
      *(undefined1 *)(puVar6 + 1) = uVar5;
      iVar1 = uVar7 * 8;
      uVar7 = uVar7 + 1;
      *(ushort *)(auStack_e0 + iVar1 + -4) = (ushort)bVar3;
      *(undefined2 *)(auStack_e0 + iVar1 + -2) = uVar4;
      param_4 = param_4 + 1;
      puVar6 = puVar6 + 2;
    } while (uVar7 != 4);
  }
  memcpy(auStack_1a8,auStack_e0,0xb8);
  MtCmdEdcaParameterSet(param_1,local_ec,local_e8,local_e4);
  return;
}

