// module: tm.ko
// function: tm_acl_check_matchfiled @ 0x6acb8
// size: 328 bytes
//

undefined4
tm_acl_check_matchfiled(byte *param_1,byte *param_2,undefined4 param_3,undefined4 param_4)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  int iVar5;
  byte *pbVar6;
  byte bVar7;
  byte *__s2;
  byte bVar8;
  byte *__s1;
  
  if (param_1 == (byte *)0x0) {
    if (g_tm_debug_level != 0) {
      printk("[%s] input ERROR: p_acl_match=NULL\n","zte_sw_api.c",param_3,g_tm_debug_level,param_4)
      ;
      return 0xffffffff;
    }
  }
  else {
    if (param_2 != (byte *)0x0) {
      bVar1 = *param_1;
      bVar2 = *param_2;
      pbVar6 = param_1;
      bVar3 = bVar1;
      if (bVar2 <= bVar1) {
        pbVar6 = param_2;
        param_2 = param_1;
        bVar3 = bVar2;
      }
      if (bVar3 != 0) {
        bVar4 = *param_2;
        __s1 = pbVar6 + 4;
        do {
          if (bVar4 == 0) {
            return 0;
          }
          __s2 = param_2 + 4;
          bVar8 = 0;
          while( true ) {
            iVar5 = memcmp(__s1,__s2,0x24);
            bVar7 = bVar8 + 1;
            if (iVar5 == 0) break;
            __s2 = __s2 + 0x24;
            bVar8 = bVar7;
            if (bVar7 == bVar4) {
              return 0;
            }
          }
          if (bVar4 == bVar8) {
            return 0;
          }
          __s1 = __s1 + 0x24;
        } while (__s1 != pbVar6 + (uint)(byte)(bVar3 - 1) * 0x24 + 0x28);
      }
      if (bVar1 == bVar2) {
        return 1;
      }
      if (bVar2 < bVar1) {
        return 2;
      }
      return 3;
    }
    if (g_tm_debug_level != 0) {
      printk("[%s] input ERROR: p_flow_match=NULL\n","zte_sw_api.c",param_3,g_tm_debug_level,param_4
            );
      return 0xffffffff;
    }
  }
  return 0xffffffff;
}

