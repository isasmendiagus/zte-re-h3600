// module: mt7915.ko
// function: SetATELoadE2p @ 0x26243c
// size: 516 bytes
//

int SetATELoadE2p(int param_1,undefined4 param_2)

{
  undefined2 uVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  int extraout_r1;
  int iVar5;
  undefined8 uVar6;
  int local_30;
  undefined1 auStack_2c [12];
  
  local_30 = 0;
  iVar2 = simple_strtol(param_2,0,10);
  if (0 < DebugLevel) {
    printk("===> %s (value=%d)\n\n","SetATELoadE2p",iVar2);
  }
  iVar3 = os_alloc_mem(param_1,&local_30,0x400);
  if (iVar3 != 1) {
    if (iVar2 != 0) {
      __memzero(local_30,0x400);
      RtmpOSFSInfoChange(auStack_2c,1);
      uVar4 = RtmpOSFileOpen("/etc/Wireless/RT2860STA/e2p.bin",0,0);
      if ((uVar4 == 0) || (0xfffff000 < uVar4)) {
        if (-1 < DebugLevel) {
          printk("%s: Error opening file %s\n","SetATELoadE2p","/etc/Wireless/RT2860STA/e2p.bin");
        }
      }
      else {
        uVar6 = RtmpOSFileRead(uVar4,local_30,0x400);
        if ((int)uVar6 == 0x400) {
          if ((*(uint *)(param_1 + 0x286280) & 0xfffffffb) == 1) {
            iVar3 = 0;
            iVar2 = (int)((ulonglong)uVar6 >> 0x20);
            do {
              iVar5 = iVar3 * 2;
              iVar3 = iVar3 + 1;
              uVar1 = *(undefined2 *)(local_30 + iVar5);
              iVar2 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0),iVar2);
              if (*(code **)(iVar2 + 0xc) != (code *)0x0) {
                (**(code **)(iVar2 + 0xc))(param_1,iVar5,uVar1);
                iVar5 = extraout_r1;
              }
              iVar2 = iVar5;
            } while (iVar3 != 0x100);
          }
          iVar3 = 1;
        }
        else if (-1 < DebugLevel) {
          printk("%s: error file length (=%d) in e2p.bin\n","SetATELoadE2p",(int)uVar6);
        }
        iVar2 = RtmpOSFileClose(uVar4);
        if ((iVar2 != 0) && (-1 < DebugLevel)) {
          printk("--> Error %d closing %s\n",-iVar2,"/etc/Wireless/RT2860STA/e2p.bin");
        }
      }
      RtmpOSFSInfoChange(auStack_2c,0);
    }
    os_free_mem(local_30);
    if (0 < DebugLevel) {
      printk("<=== %s (Ret=%d)\n","SetATELoadE2p",iVar3);
    }
  }
  return iVar3;
}

