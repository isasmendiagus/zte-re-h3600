// module: tm.ko
// function: tmAclTestMain @ 0x102a8
// size: 388 bytes
//

undefined4 tmAclTestMain(undefined1 param_1,uint param_2)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  undefined1 auStack_130 [4];
  undefined4 local_12c;
  undefined1 auStack_128 [20];
  undefined4 local_114;
  undefined4 local_10c;
  
  switch(param_1) {
  case 6:
    uVar4 = *(uint *)(((uint)auStack_130 & 0xffffe000) + 8);
    uVar2 = param_2 + 0x120;
    uVar3 = uVar2;
    if (param_2 < 0xfffffee0) {
      uVar3 = uVar2 - (uVar4 + 1);
    }
    if (param_2 < 0xfffffee0 && uVar2 <= uVar4) {
      uVar4 = 0;
    }
    if (uVar4 == 0) {
      iVar1 = __copy_from_user(auStack_128,param_2,0x120);
      if (iVar1 != 0) {
        return 0xfffffff2;
      }
      printk("parse mask=0x%08x\n",local_10c);
      addAclRuleTest(auStack_128);
      return 1;
    }
    __memzero(auStack_128,0x120,uVar3);
    return 0xfffffff2;
  case 7:
    uVar4 = *(uint *)(((uint)auStack_130 & 0xffffe000) + 8);
    uVar2 = param_2 + 0x18;
    uVar3 = uVar2;
    if (param_2 < 0xffffffe8) {
      uVar3 = uVar2 - (uVar4 + 1);
    }
    if (param_2 < 0xffffffe8 && uVar2 <= uVar4) {
      uVar4 = 0;
    }
    if (uVar4 == 0) {
      iVar1 = __copy_from_user(auStack_128,param_2,0x18);
      if (iVar1 != 0) {
        return 0xfffffff2;
      }
      tm_del_acl_flow_rule(auStack_128,local_114);
      return 1;
    }
    __memzero(auStack_128,0x18,uVar3);
    return 0xfffffff2;
  default:
    return 1;
  case 0xc:
    local_12c = 0;
    uVar4 = *(uint *)(((uint)auStack_130 & 0xffffe000) + 8);
    uVar2 = param_2 + 0x14;
    uVar3 = uVar2;
    if (param_2 < 0xffffffec) {
      uVar3 = uVar2 - (uVar4 + 1);
    }
    if (param_2 < 0xffffffec && uVar2 <= uVar4) {
      uVar4 = 0;
    }
    break;
  case 0xd:
    uVar4 = *(uint *)(((uint)auStack_130 & 0xffffe000) + 8);
    uVar2 = param_2 + 0x14;
    uVar3 = uVar2;
    if (param_2 < 0xffffffec) {
      uVar3 = uVar2 - (uVar4 + 1);
    }
    if (param_2 < 0xffffffec && uVar2 <= uVar4) {
      uVar4 = 0;
    }
  }
  if (uVar4 == 0) {
    iVar1 = __copy_from_user(auStack_128,param_2,0x14);
    if (iVar1 == 0) {
      tm_get_acl_flow_status(auStack_128,&local_12c);
      return 1;
    }
  }
  else {
    __memzero(auStack_128,0x14,uVar3);
  }
  return 0xfffffff2;
}

