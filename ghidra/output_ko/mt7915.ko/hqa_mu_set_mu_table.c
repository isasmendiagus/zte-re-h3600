// module: mt7915.ko
// function: hqa_mu_set_mu_table @ 0x927e8
// size: 796 bytes
//

undefined4 hqa_mu_set_mu_table(undefined4 param_1,char *param_2)

{
  char *pcVar1;
  int iVar2;
  uint uVar3;
  undefined4 uVar4;
  uint uVar5;
  undefined1 *puVar6;
  undefined1 *puVar7;
  char *local_254;
  undefined2 local_250;
  uint local_24c;
  undefined1 *local_248;
  undefined1 auStack_244 [60];
  undefined1 auStack_208 [484];
  
  local_254 = param_2;
  if (param_2 == (char *)0x0) {
    if (-1 < DebugLevel) {
      printk("%s: Argument is NULL\n","hqa_mu_set_mu_table");
      goto LAB_00092984;
    }
LAB_00092868:
    uVar4 = 0;
  }
  else {
    pcVar1 = strsep(&local_254,":");
    if (pcVar1 == (char *)0x0) {
      if (DebugLevel < 0) goto LAB_00092868;
      printk("%s: Type (SU/MU) is NULL\n","hqa_mu_set_mu_table");
LAB_00092984:
      if (DebugLevel < 1) goto LAB_00092868;
      uVar4 = 0;
      pcVar1 = "Fail";
    }
    else {
      iVar2 = os_str_toul(pcVar1,0,10);
      if (local_254 == (char *)0x0) {
        if (DebugLevel < 0) goto LAB_00092868;
        printk("%s: specific_metric_content is NULL\n","hqa_mu_set_mu_table");
        goto LAB_00092984;
      }
      uVar3 = os_str_toul(local_254,0,10);
      if (iVar2 == 1) {
        __memzero(auStack_208,0x1e0);
        memset(auStack_208,uVar3 & 0xff,0x1e0);
        uVar3 = 0x1e0;
        if (0 < DebugLevel) {
LAB_00092a78:
          printk("%s: type:%u, length:%u, data = %zu\n","hqa_mu_set_mu_table",iVar2,uVar3,uVar3);
          if (0 < DebugLevel) {
            pcVar1 = "mu_metric_table:";
            if (iVar2 != 1) {
              pcVar1 = "su_metric_table:";
            }
            printk(&_LC0,pcVar1);
          }
          if (iVar2 != 1) goto LAB_00092934;
        }
        puVar7 = auStack_208;
        uVar5 = 0;
        puVar6 = puVar7;
        do {
          if (0 < DebugLevel) {
            printk("0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x\n",puVar7[uVar5],puVar6[1],puVar6[2],
                   puVar6[3],puVar6[4],puVar6[5],puVar6[6],puVar6[7]);
          }
          uVar5 = uVar5 + 8;
          puVar6 = puVar6 + 8;
        } while (uVar5 < uVar3);
      }
      else {
        if (iVar2 != 0) {
          if (-1 < DebugLevel) {
            printk("%s: Type error(%u)!!! neither MU nor SU\n","hqa_mu_set_mu_table",iVar2);
            goto LAB_00092984;
          }
          goto LAB_00092868;
        }
        __memzero(auStack_244,0x3c);
        memset(auStack_244,uVar3 & 0xff,0x3c);
        uVar3 = 0x3c;
        if (0 < DebugLevel) goto LAB_00092a78;
LAB_00092934:
        puVar7 = auStack_244;
        uVar5 = 0;
        puVar6 = puVar7;
        do {
          if (0 < DebugLevel) {
            printk("0x%x 0x%x 0x%x\n",puVar7[uVar5],puVar6[1],puVar6[2]);
          }
          uVar5 = uVar5 + 3;
          puVar6 = puVar6 + 3;
        } while ((uVar5 < uVar3) && (uVar5 != 0x3c));
      }
      local_250 = (undefined2)iVar2;
      local_24c = uVar3;
      local_248 = puVar7;
      iVar2 = hqa_wifi_test_mu_table_set(param_1);
      if (iVar2 != 0) goto LAB_00092984;
      if (DebugLevel < 1) {
        return 1;
      }
      uVar4 = 1;
      pcVar1 = "Success";
    }
    printk("%s: CMD %s\n","hqa_mu_set_mu_table",pcVar1);
  }
  return uVar4;
}

