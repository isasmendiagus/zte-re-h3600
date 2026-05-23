// module: mt7915.ko
// function: SendWNMNotifyConfirm @ 0x223e5c
// size: 244 bytes
//

void SendWNMNotifyConfirm(int param_1,byte *param_2)

{
  byte bVar1;
  int *piVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  int *piVar6;
  
  bVar1 = *param_2;
  printk(&_LC4,"SendWNMNotifyConfirm");
  printk("Receive WNM Notify Response Status:%d\n",param_2[0xc]);
  iVar5 = (uint)bVar1 * 0x5834;
  down_interruptible(&_LC170 + param_1 + iVar5);
  piVar6 = *(int **)("RT_OID_WSC_SET_MODE::WscMode = %d\n" + param_1 + iVar5 + 4);
  if (piVar6 != (int *)("RT_OID_WSC_SET_MODE::WscMode = %d\n" + param_1 + iVar5 + 4)) {
    piVar2 = (int *)*piVar6;
    do {
      piVar4 = piVar2;
      iVar3 = memcmp((char *)((int)piVar6 + 0xd),param_2 + 1,6);
      if (iVar3 == 0) {
        if (*piVar6 != 0) {
          *(int *)(*piVar6 + 4) = piVar6[1];
        }
        if ((int *)piVar6[1] != (int *)0x0) {
          *(int *)piVar6[1] = *piVar6;
        }
        *piVar6 = 0;
        piVar6[1] = 0;
        os_free_mem(piVar6);
        break;
      }
      piVar2 = (int *)*piVar4;
      piVar6 = piVar4;
    } while (piVar4 != (int *)("RT_OID_WSC_SET_MODE::WscMode = %d\n" + param_1 + iVar5 + 4));
  }
  up(&_LC170 + param_1 + iVar5);
  return;
}

