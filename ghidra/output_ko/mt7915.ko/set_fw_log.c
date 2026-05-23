// module: mt7915.ko
// function: set_fw_log @ 0xbbc50
// size: 512 bytes
//

undefined4 set_fw_log(int param_1,char *param_2)

{
  char *pcVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  char *local_3c [2];
  char *apcStack_34 [6];
  
  apcStack_34[0] = "Print MCU Log to UART";
  apcStack_34[1] = "Send MCU log by Event";
  apcStack_34[2] = "Send MCU log to EMI(currently not support)";
  apcStack_34[3] = "Send MCU log by Event to Storage";
  apcStack_34[4] = "Send MCU log by Event to Ethernet";
  local_3c[0] = param_2;
  if (0 < DebugLevel) {
    printk(":%s: arg = %s\n","set_fw_log",param_2);
  }
  pcVar1 = strsep(local_3c,":");
  if ((pcVar1 == (char *)0x0) || (local_3c[0] == (char *)0x0)) {
    if (DebugLevel < 1) {
      return 0;
    }
    printk(":%s: Invalid parameters\n","set_fw_log");
    return 0;
  }
  uVar2 = os_str_toul(pcVar1,0,10);
  uVar3 = os_str_toul(local_3c[0],0,10);
  if (uVar2 == 0) {
    if ((uVar3 & 0xffffffe0) != 0) goto LAB_000bbce4;
    *(char *)(param_1 + 0xa7cc32) = (char)uVar3;
LAB_000bbd1c:
    if (DebugLevel < 0) goto LAB_000bbd28;
    pcVar1 = "HOST2CR4";
    if (uVar2 == 0) {
      pcVar1 = "HOST2N9";
    }
LAB_000bbe04:
    printk(":%s: Mcu Dest = %s, ","set_fw_log",pcVar1);
    if (uVar3 == 0) {
      if (-1 < DebugLevel) {
        printk("Log Type = Disable MCU Log Message\n");
      }
      goto LAB_000bbd58;
    }
  }
  else {
    if (uVar2 == 1) {
      if ((uVar3 & 0xfffffffc) != 0) {
LAB_000bbce4:
        if (0 < DebugLevel) {
          printk(":%s: Unknown Mcu Dest = %d, Log Type = %x\n","set_fw_log",uVar2,uVar3);
        }
        return 0;
      }
      goto LAB_000bbd1c;
    }
    if (uVar2 != 2) goto LAB_000bbce4;
    if (-1 < DebugLevel) {
      pcVar1 = "HOST2CR4";
      goto LAB_000bbe04;
    }
LAB_000bbd28:
    if (uVar3 == 0) goto LAB_000bbd58;
  }
  uVar4 = 0;
  do {
    if (((uVar3 & 1 << (uVar4 & 0xff)) != 0) && (-1 < DebugLevel)) {
      printk("Log Type = %s\n",apcStack_34[uVar4]);
    }
    uVar4 = uVar4 + 1;
  } while (uVar4 != 5);
LAB_000bbd58:
  MtCmdFwLog2Host(param_1,uVar2 & 0xff,uVar3 & 0xff);
  return 1;
}

