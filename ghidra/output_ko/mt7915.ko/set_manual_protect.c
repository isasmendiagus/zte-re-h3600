// module: mt7915.ko
// function: set_manual_protect @ 0xec290
// size: 648 bytes
//

undefined4 set_manual_protect(int param_1,char *param_2)

{
  char *pcVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  char *local_24 [2];
  
  local_24[0] = param_2;
  if (param_2 != (char *)0x0) {
    pcVar1 = strsep(local_24,"-");
    iVar2 = os_str_tol(pcVar1,0,10);
    iVar5 = param_1 + iVar2 * 4;
    iVar6 = *(int *)(iVar5 + 0xc);
    if (iVar6 != 0) {
      uVar4 = 0;
      iVar3 = DebugLevel;
joined_r0x000ec2ec:
      do {
        while( true ) {
          while( true ) {
            while( true ) {
              while( true ) {
                while( true ) {
                  while( true ) {
                    DebugLevel = iVar3;
                    if (local_24[0] == (char *)0x0) {
                      *(uint *)(*(int *)(iVar5 + 0xc) + 0x8dc) = uVar4;
                      if ((0 < iVar3) &&
                         (printk(" <<< manual trigger >>>\n HWFLAG_ID_UPDATE_PROTECT\n"),
                         0 < DebugLevel)) {
                        printk("   -- wdev_%d->protection: 0x%08x\n",iVar2,
                               *(undefined4 *)(*(int *)(iVar5 + 0xc) + 0x8dc));
                      }
                      HW_SET_PROTECT(param_1,iVar6,0,0,0);
                      return 1;
                    }
                    pcVar1 = strsep(local_24,"+");
                    iVar3 = strcmp(pcVar1,"erp");
                    if (iVar3 != 0) break;
                    uVar4 = uVar4 | 0x20;
                    iVar3 = DebugLevel;
                  }
                  iVar3 = strcmp(pcVar1,"no");
                  if (iVar3 != 0) break;
                  uVar4 = uVar4 | 1;
                  iVar3 = DebugLevel;
                }
                iVar3 = strcmp(pcVar1,"non_member");
                if (iVar3 != 0) break;
                uVar4 = uVar4 | 2;
                iVar3 = DebugLevel;
              }
              iVar3 = strcmp(pcVar1,"ht20");
              if (iVar3 != 0) break;
              uVar4 = uVar4 | 4;
              iVar3 = DebugLevel;
            }
            iVar3 = strcmp(pcVar1,"non_ht_mixmode");
            if (iVar3 != 0) break;
            uVar4 = uVar4 | 8;
            iVar3 = DebugLevel;
          }
          iVar3 = strcmp(pcVar1,"longnav");
          if (iVar3 != 0) break;
LAB_000ec3a4:
          uVar4 = uVar4 | 0x40;
          iVar3 = DebugLevel;
        }
        iVar3 = strcmp(pcVar1,"gf");
        if (iVar3 != 0) {
          iVar3 = strcmp(pcVar1,"rifs");
          if (iVar3 == 0) {
            uVar4 = uVar4 | 0x100;
            iVar3 = DebugLevel;
          }
          else {
            iVar3 = strcmp(pcVar1,"rdg");
            if (iVar3 == 0) goto LAB_000ec3a4;
            iVar3 = strcmp(pcVar1,"force_rts");
            if (iVar3 != 0) {
              if (DebugLevel < 0) {
                return 1;
              }
              printk(" -no mode [ERROR 3]\n");
              goto LAB_000ec480;
            }
            uVar4 = uVar4 | 0x400;
            iVar3 = DebugLevel;
          }
          goto joined_r0x000ec2ec;
        }
        uVar4 = uVar4 | 0x80;
        iVar3 = DebugLevel;
      } while( true );
    }
    if (DebugLevel < 0) {
      return 1;
    }
    printk(" -no wdev_idx: 0x%x [ERROR 2]\n",iVar2);
  }
LAB_000ec480:
  if ((-1 < DebugLevel) &&
     (printk("Usage:\niwpriv ra0 set protect=[wdev_idx]-[mode]+...\n"), -1 < DebugLevel)) {
    printk("       mode: [erp|no|non_member|ht20|non_ht_mixmode|longnav|gf|rifs|rdg|force_rts]\n");
  }
  return 1;
}

