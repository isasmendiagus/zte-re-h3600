// module: mt7915.ko
// function: DfsRadarDetectStart @ 0x2359c8
// size: 492 bytes
//

void DfsRadarDetectStart(int param_1,byte *param_2,int param_3)

{
  undefined1 uVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  if (param_3 == 0) {
    return;
  }
  iVar5 = *(int *)(param_3 + 0x3fe4);
  iVar3 = HcGetBandByWdev(param_3);
  uVar1 = *(undefined1 *)(param_1 + 0x795075);
  if (((iVar5 != 0) && (iVar4 = scan_in_run_state(param_1,0), iVar4 == 0)) &&
     (cVar2 = *(char *)(iVar5 + 4), cVar2 != '\x01')) {
    if (cVar2 == '\x02') {
      if (2 < DebugLevel) {
        printk("[%s]:ZeroWaitState:%d\n","DfsRadarDetectStart",*(undefined1 *)(param_1 + 0x7953f7));
      }
      if (param_2[iVar3 + 0x2b7] == 0) {
        if (*(char *)(param_1 + 0x79504d) == '\0') {
          if (param_2[iVar3 + 4] == 3) {
            if (0xc < *param_2 - 0x24) {
              mtRddControl(param_1,1,0,0,uVar1);
            }
          }
          else {
            if (param_2[iVar3 + 4] != 6) {
              mtRddControl(param_1,1,iVar3,0,uVar1);
              goto LAB_00235afc;
            }
            if (param_2[0x2b1] != 0) {
              mtRddControl(param_1,1,0,0,uVar1);
            }
            if (param_2[0x2b2] == 0) goto LAB_00235afc;
          }
          mtRddControl(param_1,1,1,0,uVar1);
        }
        else {
          mtRddControl(param_1,1,iVar3,0,uVar1);
        }
      }
LAB_00235afc:
      param_2[iVar3 + 0x2b7] = 1;
      return;
    }
    iVar5 = DfsIsOutBandAvailable(param_1,param_3);
    if ((iVar5 != 0) && (param_2[0x2ca] != 0)) {
      if (2 < DebugLevel) {
        printk("[%s]: out-band is available\n","DfsRadarDetectStart");
      }
      mtRddControl(param_1,1,iVar3,0,uVar1);
    }
  }
  return;
}

