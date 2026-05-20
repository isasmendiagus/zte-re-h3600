// module: mt7915.ko
// function: print_vie @ 0x145988
// size: 308 bytes
//

void print_vie(int param_1)

{
  char *pcVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 *puVar4;
  int iVar5;
  
  puVar4 = (undefined4 *)(param_1 + 0x3ff0);
  iVar5 = 0;
  do {
    if (-1 < DebugLevel) {
      if (iVar5 == 0) {
        pcVar1 = "Beacon";
      }
      else if (iVar5 == 1) {
        pcVar1 = "Probe_Req";
      }
      else if (iVar5 == 2) {
        pcVar1 = "Probe_Resp";
      }
      else if (iVar5 == 3) {
        pcVar1 = "Assoc_Req";
      }
      else if (iVar5 == 4) {
        pcVar1 = "Assoc_Resp";
      }
      else {
        pcVar1 = "Auth_Resp";
        if (iVar5 == 5) {
          pcVar1 = "Auth_Req";
        }
      }
      printk("\nFrm_Type:%s, vie_num:%d\n",pcVar1,*(undefined1 *)(puVar4 + -1));
    }
    puVar2 = (undefined4 *)*puVar4;
    if (puVar2 != (undefined4 *)0x0) {
      iVar3 = 0;
      do {
        if (-1 < DebugLevel) {
          printk("vie_index:%d oui:0x%02x 0x%02x 0x%02x\n",iVar3,*(undefined1 *)(puVar2 + 1),
                 *(undefined1 *)((int)puVar2 + 5),*(undefined1 *)((int)puVar2 + 6));
        }
        hex_dump("ie_content:",puVar2[2],*puVar2);
        puVar2 = (undefined4 *)puVar2[3];
        iVar3 = iVar3 + 1;
      } while (puVar2 != (undefined4 *)0x0);
    }
    iVar5 = iVar5 + 1;
    puVar4 = puVar4 + 3;
  } while (iVar5 != 7);
  return;
}

