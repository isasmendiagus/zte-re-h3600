// module: switch.ko
// function: sw_mld_mulrule_deal @ 0x1fe10
// size: 376 bytes
//

undefined4 sw_mld_mulrule_deal(int param_1,int param_2,int param_3)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 *puVar3;
  undefined1 *puVar4;
  undefined1 uVar5;
  undefined1 *puVar6;
  undefined1 auStack_4b4 [8];
  undefined1 local_4ac;
  undefined1 local_4ab;
  undefined2 local_4aa;
  undefined4 local_4a8;
  undefined1 local_4a4;
  undefined4 local_4a0;
  undefined1 local_49c [16];
  undefined1 local_48c [16];
  undefined4 local_47c;
  undefined1 local_46a;
  undefined1 local_469;
  undefined1 local_468 [16];
  undefined4 local_458;
  undefined1 local_44a;
  undefined1 uStack_445;
  undefined1 local_444 [484];
  undefined4 local_260;
  undefined4 local_25c;
  undefined1 local_256;
  undefined1 local_254;
  
  __memzero(&local_4ac,0x49c);
  __memzero(auStack_4b4,8);
  puVar6 = local_49c + 0xf;
  local_4aa = 0;
  local_4ac = 100;
  local_4ab = 0xf;
  local_4a8 = 1;
  local_4a4 = 3;
  local_4a0 = 0x12;
  puVar3 = puVar6;
  do {
    puVar3 = puVar3 + 1;
    *puVar3 = 0;
  } while (puVar3 != local_48c + 0xf);
  puVar3 = (undefined1 *)(param_1 + 0x10);
  puVar4 = (undefined1 *)((int)&local_4a0 + 3);
  do {
    puVar3 = puVar3 + -1;
    puVar4 = puVar4 + 1;
    *puVar4 = *puVar3;
    puVar6 = puVar6 + 1;
    *puVar6 = 0xff;
  } while (puVar4 != local_49c + 0xf);
  puVar3 = &local_469;
  do {
    puVar3 = puVar3 + 1;
    *puVar3 = 0;
  } while (puVar3 != local_468 + 0xf);
  local_469 = (undefined1)param_2;
  if (param_2 != 0) {
    uVar5 = (undefined1)((uint)param_2 >> 8);
    local_47c = 6;
  }
  else {
    uVar5 = 0;
  }
  local_468[0xf] = 0xff;
  puVar3 = &uStack_445;
  if (param_2 == 0) {
    local_47c = 4;
    uVar5 = local_46a;
  }
  do {
    local_46a = uVar5;
    puVar3 = puVar3 + 1;
    *puVar3 = 0;
    uVar5 = local_46a;
  } while (puVar3 != local_444 + 0xf);
  local_254 = 0;
  local_458 = 2;
  local_44a = 0x33;
  local_444[10] = 0xff;
  local_260 = 1;
  local_25c = 1;
  local_256 = 5;
  if (param_3 == 1) {
    iVar1 = zte_api_sw_qos_add_port_streamselect(&local_4ac,auStack_4b4);
  }
  else {
    iVar1 = zte_api_sw_qos_del_port_streamselect();
  }
  uVar2 = 0;
  if (iVar1 != 0) {
    printk("zte_api_sw_qos_add_port_streamselect failed!\n");
    uVar2 = 0xffffffff;
  }
  return uVar2;
}

