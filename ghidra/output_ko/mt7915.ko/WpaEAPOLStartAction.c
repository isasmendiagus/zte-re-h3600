// module: mt7915.ko
// function: WpaEAPOLStartAction @ 0x11ef60
// size: 592 bytes
//

void WpaEAPOLStartAction(int param_1,undefined1 *param_2)

{
  undefined1 uVar1;
  undefined1 uVar2;
  ushort uVar3;
  int iVar4;
  undefined4 uVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  undefined4 uVar9;
  code *pcVar10;
  int local_38;
  undefined1 auStack_34 [20];
  
  local_38 = 0;
  log_time_begin(1,auStack_34);
  iVar6 = *(int *)(param_2 + 0x92c);
  iVar8 = *(int *)(iVar6 + 0x904);
  if (2 < DebugLevel) {
    printk("WpaEAPOLStartAction ===>\n");
    iVar6 = *(int *)(param_2 + 0x92c);
  }
  pcVar10 = *(code **)(iVar8 + 0xb8);
  if (*(int *)(param_2 + 0x908) == 6) {
    (*pcVar10)(param_1,param_2,iVar6,&local_38);
    if (local_38 == 0) goto LAB_0011f100;
  }
  else {
    (*pcVar10)(param_1,param_2 + 10,iVar6,&local_38);
    if (local_38 == 0) {
LAB_0011f100:
      if (DebugLevel < 0) {
        return;
      }
      printk("%s, cannot find entry:%02x:%02x:%02x:%02x:%02x:%02x\n","WpaEAPOLStartAction",*param_2,
             param_2[1],param_2[2],param_2[3],param_2[4],param_2[5]);
      return;
    }
    if ((((*(char *)(local_38 + 0xe4) == '\0') &&
         (*(int *)(
                  "4/home/ws/zx279128s/packages/function/wlan/mtk/drivers/MT7915_V7.0.1.0/mt_wifi_ap/../mt_wifi/embedded/fsm/ap_mgmt_cntl.c:%d assert pAdfailed\n"
                  + param_1 + 0x2b) != 0)) && ((*(uint *)(local_38 + 0x17c) & 0x2090) != 0)) &&
       (*(char *)(local_38 + 0xd24) != '\0')) {
      if (DebugLevel < 3) {
        return;
      }
      printk("WPS enabled AP: Ignore EAPOL-Start frames received from clients.\n");
      return;
    }
  }
  iVar6 = local_38;
  iVar8 = local_38 + 0x17c;
  uVar3 = *(ushort *)(local_38 + 0xe0);
  if (2 < DebugLevel) {
    uVar1 = *(undefined1 *)(local_38 + 0x514);
    uVar9 = *(undefined4 *)(local_38 + 0x17c);
    uVar2 = *(undefined1 *)((uint)uVar3 * 0x620 + param_1 + 0x2f762);
    uVar5 = is_pmkid_cache_in_sec_config(iVar8);
    printk(" PortSecured(%d), WpaState(%d), AKM(0x%x), is_cache(%d)\n",uVar2,uVar1,uVar9,uVar5);
  }
  if ((*(char *)(param_1 + (uint)uVar3 * 0x620 + 0x2f762) != '\x02') ||
     (7 < *(byte *)(iVar6 + 0x514))) goto LAB_0011f008;
  uVar7 = *(uint *)(iVar6 + 0x17c);
  if ((uVar7 & 0x2090) == 0) {
    if ((uVar7 & 0x40) != 0) {
      iVar4 = is_pmkid_cache_in_sec_config(iVar8);
      if (iVar4 != 0) goto LAB_0011f0b4;
      uVar7 = *(uint *)(iVar6 + 0x17c);
    }
    if (((uVar7 & 0x10000) == 0) || (iVar8 = is_pmkid_cache_in_sec_config(iVar8), iVar8 == 0))
    goto LAB_0011f008;
  }
LAB_0011f0b4:
  *(undefined4 *)(local_38 + 0xadc) = 1;
  __memzero(iVar6 + 0x50c,8);
  *(undefined1 *)(iVar6 + 0x554) = 0;
  WPABuildPairMsg1(param_1,local_38 + 0x17c);
LAB_0011f008:
  log_time_end(2,"eapol_start",1,auStack_34);
  return;
}

