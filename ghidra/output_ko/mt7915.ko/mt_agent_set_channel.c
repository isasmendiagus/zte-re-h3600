// module: mt7915.ko
// function: mt_agent_set_channel @ 0x24ca04
// size: 612 bytes
//

undefined4 mt_agent_set_channel(int param_1,undefined4 param_2)

{
  int iVar1;
  uint uVar2;
  char cVar3;
  uint uVar4;
  uint *puVar5;
  uint uVar6;
  uint uVar7;
  uint local_3c;
  uint local_38;
  undefined *local_34;
  uint local_30 [5];
  
  cVar3 = '\0';
  local_34 = &DAT_005f5b58;
  local_3c = 0;
  local_38 = 0;
  local_30[0] = 0;
  local_30[1] = 0;
  local_30[2] = 0;
  local_30[3] = 0;
  sys_ad_zero_mem(&_LANCHOR1,0x80c);
  printk("%s: control_band_idx:%x, Channel = %s\n","mt_agent_set_channel",
         *(undefined1 *)(param_1 + 0x4cc),param_2);
  iVar1 = agent_trtok(param_2,&_LC90);
  if (iVar1 == 0) {
    uVar4 = 0;
    uVar6 = 0;
    uVar2 = 0;
    uVar7 = 0;
  }
  else {
    puVar5 = local_30;
    do {
      iVar1 = _kstrtol(iVar1,10,&local_3c);
      if (iVar1 != 0) {
        return 0x104;
      }
      cVar3 = cVar3 + '\x01';
      *puVar5 = local_3c;
      iVar1 = agent_trtok(0,&_LC90);
      uVar7 = local_30[3];
      uVar4 = local_30[2];
      uVar6 = local_30[0];
      puVar5 = puVar5 + 1;
    } while (cVar3 != '\x04' && iVar1 != 0);
    uVar2 = local_30[1];
    if ((local_30[0] - 0x24 < 0x92) && (local_30[1] == 0)) {
      uVar2 = 1;
      printk(&_LC93,"mt_agent_set_channel",local_30[0]);
    }
  }
  FUN_00246ac8(1,4,&local_38,&local_34);
  local_38 = 8;
  FUN_00246ac8(1,4,&local_38,&local_34);
  local_38 = (uint)*(byte *)(param_1 + 0x4cc);
  FUN_00246ac8(1,4,&local_38,&local_34);
  local_38 = uVar6;
  FUN_00246ac8(1,4,&local_38,&local_34);
  local_38 = uVar7;
  FUN_00246ac8(1,4,&local_38,&local_34);
  local_38 = (uint)*(byte *)((uint)*(byte *)(param_1 + 0x4cc) * 0xd18 + param_1 + 0x1136);
  FUN_00246ac8(1,4,&local_38,&local_34);
  local_38 = (uint)*(byte *)((uint)*(byte *)(param_1 + 0x4cc) * 0xd18 + param_1 + 0x1137);
  FUN_00246ac8(1,4,&local_38,&local_34);
  local_38 = uVar4;
  FUN_00246ac8(1,4,&local_38,&local_34);
  local_38 = 0;
  FUN_00246ac8(1,4,&local_38,&local_34);
  local_38 = uVar2;
  FUN_00246ac8(1,4,&local_38,&local_34);
  local_38 = 0;
  FUN_00246ac8(1,4,&local_38,&local_34);
  hqa_set_channel_ext(param_1,&_LANCHOR1);
  return 0;
}

