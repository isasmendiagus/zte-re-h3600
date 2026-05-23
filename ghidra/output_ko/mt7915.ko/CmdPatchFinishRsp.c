// module: mt7915.ko
// function: CmdPatchFinishRsp @ 0x1ac698
// size: 72 bytes
//

void CmdPatchFinishRsp(undefined4 param_1,char *param_2)

{
  if (*param_2 != '\0') {
    if (DebugLevel < 1) {
      return;
    }
    printk("%s: WiFi ROM Patch Fail (%d)\n","CmdPatchFinishRsp");
    return;
  }
  if (DebugLevel < 1) {
    return;
  }
  printk("%s: WiFI ROM Patch Download Success\n","CmdPatchFinishRsp");
  return;
}

