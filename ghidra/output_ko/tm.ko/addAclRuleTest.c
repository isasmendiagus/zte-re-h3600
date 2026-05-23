// module: tm.ko
// function: addAclRuleTest @ 0x10254
// size: 60 bytes
//

undefined4 addAclRuleTest(int param_1)

{
  undefined1 auStack_1c [20];
  
  __memzero(auStack_1c,0x14);
  *(undefined2 *)(param_1 + 2) = 2000;
  tm_add_acl_flow_rule(param_1,param_1 + 0xbc,auStack_1c);
  return 1;
}

