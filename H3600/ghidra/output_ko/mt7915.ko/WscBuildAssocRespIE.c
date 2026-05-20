// module: mt7915.ko
// function: WscBuildAssocRespIE @ 0x1e49b4
// size: 508 bytes
//

void WscBuildAssocRespIE(int param_1,int param_2,undefined4 param_3,undefined4 *param_4,
                        char *param_5)

{
  char cVar1;
  undefined1 *puVar2;
  int iVar3;
  undefined1 local_35;
  undefined1 *local_34;
  undefined1 *local_30;
  size_t local_2c;
  undefined4 local_26;
  undefined2 local_22;
  
  local_34 = (undefined1 *)0x0;
  local_2c = 0;
  local_35 = 0;
  if (2 < DebugLevel) {
    printk("-----> WscBuildAssocRespIE\n");
  }
  os_alloc_mem(0,&local_34,0x200);
  if (local_34 == (undefined1 *)0x0) {
    if (-1 < DebugLevel) {
      printk("%s: Allocate memory fail!!!\n","WscBuildAssocRespIE");
    }
  }
  else {
    param_2 = param_2 * 0x5834;
    *local_34 = 0;
    local_30 = local_34;
    local_22 = 0x4f2;
    local_2c = 0;
    local_26 = 0x500004dd;
    iVar3 = AppendWSCTLV(0x104a,local_34,
                         "4/home/ws/zx279128s/packages/function/wlan/mtk/drivers/MT7915_V7.0.1.0/mt_wifi_ap/../mt_wifi/embedded/fsm/ap_mgmt_sync.c:%d assert 0failed\n"
                         + param_1 + param_2 + 0xb,0);
    local_30 = local_30 + iVar3;
    local_35 = 3;
    local_2c = local_2c + iVar3;
    iVar3 = AppendWSCTLV(0x103b,local_30,&local_35,0);
    local_30 = local_30 + iVar3;
    local_2c = iVar3 + local_2c;
    if ("%-10d, %d, %d%%\n"[param_1 + param_2 + 0xd] != '\0') {
      WscGenV2Msg("4/home/ws/zx279128s/packages/function/wlan/mtk/drivers/MT7915_V7.0.1.0/mt_wifi_ap/../mt_wifi/embedded/fsm/ap_mgmt_cntl.c:%d assert pAdfailed\n"
                  + param_1 + param_2 + 0x2b,0,0,0,&local_30,&local_2c);
    }
    puVar2 = local_34;
    cVar1 = (char)local_2c;
    local_26._0_2_ = CONCAT11(cVar1 + '\x04',(undefined1)local_26);
    *param_4 = local_26;
    *(undefined2 *)(param_4 + 1) = local_22;
    memmove((void *)((int)param_4 + 6),local_34,local_2c);
    *param_5 = cVar1 + '\x06';
    if (puVar2 != (undefined1 *)0x0) {
      os_free_mem(puVar2);
    }
    if (2 < DebugLevel) {
      printk("<----- WscBuildAssocRespIE\n");
    }
  }
  return;
}

