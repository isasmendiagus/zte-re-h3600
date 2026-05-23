// module: idmfdb.ko
// function: print_idm_node_stat @ 0x10850
// size: 484 bytes
//

uint print_idm_node_stat(byte *param_1,char *param_2,size_t param_3)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  char *apcStack_54 [12];
  
  uVar1 = (uint)(param_1 == (byte *)0x0 || param_2 == (char *)0x0);
  apcStack_54[0] = "WlanTx UNICAST";
  apcStack_54[1] = "WlanTx MULTICAST";
  apcStack_54[2] = "WlanTx BROADCAST";
  apcStack_54[3] = "WlanTx FLOOD";
  apcStack_54[4] = "WlanTx MCASTFLOOD";
  apcStack_54[5] = "WlanTx MTRANS";
  apcStack_54[6] = "WlanRx RECEIVE";
  apcStack_54[7] = "WlanTx SEND_FAIL";
  apcStack_54[8] = "MTRAN_FAIL";
  apcStack_54[9] = "FAIL";
  apcStack_54[10] = "DROP";
  if (param_1 == (byte *)0x0 || param_2 == (char *)0x0) {
    uVar1 = 0;
  }
  else {
    if ((0 < (int)param_3) &&
       (uVar1 = snprintf(param_2,param_3,"en:\t%d\n",(uint)*param_1), (int)uVar1 < (int)param_3)) {
      iVar2 = snprintf(param_2 + uVar1,param_3 - uVar1,"idm:\t%d\n",(uint)param_1[1]);
      uVar1 = uVar1 + iVar2;
      if ((int)uVar1 < (int)param_3) {
        iVar2 = snprintf(param_2 + uVar1,param_3 - uVar1,"ssid:\t%d\n",(uint)param_1[3]);
        uVar1 = uVar1 + iVar2;
        if ((int)uVar1 < (int)param_3) {
          iVar2 = snprintf(param_2 + uVar1,param_3 - uVar1,"dev:\t%s\n",
                           *(undefined4 *)(param_1 + 0x14));
          uVar1 = uVar1 + iVar2;
          if ((int)uVar1 < (int)param_3) {
            iVar2 = snprintf(param_2 + uVar1,param_3 - uVar1,"running:\t%d\n",
                             *(uint *)(*(int *)(param_1 + 0x14) + 0x30) & 1);
            uVar1 = uVar1 + iVar2;
            if ((int)uVar1 < (int)param_3) {
              iVar2 = snprintf(param_2 + uVar1,param_3 - uVar1,"cnt:\n");
              uVar1 = uVar1 + iVar2;
            }
          }
        }
      }
    }
    uVar3 = 0;
    do {
      while ((int)uVar1 < (int)param_3) {
        uVar4 = uVar3 + 1;
        iVar2 = snprintf(param_2 + uVar1,param_3 - uVar1,"%20s: %10lld pkt, %10lld bytes\n",
                         apcStack_54[uVar3 % 0xb],*(undefined4 *)(param_1 + 0x18),
                         *(undefined4 *)(param_1 + 0x1c),*(undefined4 *)(param_1 + 0x20),
                         *(undefined4 *)(param_1 + 0x24));
        uVar1 = uVar1 + iVar2;
        uVar3 = uVar4;
        param_1 = param_1 + 0x18;
        if (uVar4 == 0xb) goto LAB_00010a00;
      }
      uVar3 = uVar3 + 1;
      param_1 = param_1 + 0x18;
    } while (uVar3 != 0xb);
LAB_00010a00:
    if ((int)uVar1 < (int)param_3) {
      iVar2 = snprintf(param_2 + uVar1,param_3 - uVar1,"\n");
      return uVar1 + iVar2;
    }
  }
  return uVar1;
}

