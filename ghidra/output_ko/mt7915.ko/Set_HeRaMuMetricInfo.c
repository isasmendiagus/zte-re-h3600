// module: mt7915.ko
// function: Set_HeRaMuMetricInfo @ 0xe8ee4
// size: 380 bytes
//

undefined4 Set_HeRaMuMetricInfo(undefined4 param_1,undefined4 param_2)

{
  undefined2 uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  undefined1 uStack_6a;
  char local_69;
  undefined1 local_68;
  undefined1 local_67;
  undefined1 local_66;
  undefined1 local_65;
  undefined1 local_64;
  undefined1 local_63;
  undefined1 local_62;
  undefined1 local_61;
  undefined1 local_60;
  undefined1 local_5f;
  undefined1 local_5e;
  undefined1 local_5d;
  undefined1 local_5a;
  undefined1 local_59;
  undefined1 local_58;
  undefined1 local_57;
  char local_4e [4];
  undefined1 local_4a;
  undefined1 local_48;
  undefined1 local_46;
  undefined1 local_44;
  undefined1 local_42;
  undefined1 local_40;
  undefined1 local_3e;
  undefined1 local_3c;
  undefined1 local_3a;
  undefined1 local_38;
  undefined1 local_36;
  undefined1 local_34;
  undefined1 local_32;
  
  memset(local_4e,0,0x26);
  iVar2 = rstrtok(param_2,&_LC232);
  if (iVar2 == 0) {
    os_zero_mem(&uStack_6a,0x1c);
    local_69 = '\0';
  }
  else {
    uVar4 = 0;
    do {
      uVar1 = os_str_toul(iVar2,0,0x10);
      uVar3 = uVar4 & 0xff;
      uVar4 = uVar4 + 1;
      *(undefined2 *)(local_4e + uVar3 * 2) = uVar1;
      iVar2 = rstrtok(0,&_LC232);
    } while (iVar2 != 0);
    os_zero_mem(&uStack_6a,0x1c);
    local_69 = local_4e[0];
    if (local_4e[0] == '\x01') {
      local_66 = local_4a;
      local_64 = local_46;
      local_5a = local_38;
      local_59 = local_36;
      local_65 = local_48;
      local_63 = local_44;
      local_62 = local_42;
      local_61 = local_40;
      local_60 = local_3e;
      local_5f = local_3c;
      local_5e = local_3a;
      local_58 = local_34;
      local_57 = local_32;
      local_67 = local_4e[2];
      goto LAB_000e8f8c;
    }
    if (local_4e[0] != '\0') {
      if (local_4e[0] == '\x02') {
        local_5d = local_4e[2];
      }
      goto LAB_000e8f8c;
    }
  }
  local_68 = local_4e[2];
LAB_000e8f8c:
  HeRaMuMetricInfo(param_1,&uStack_6a);
  return 1;
}

