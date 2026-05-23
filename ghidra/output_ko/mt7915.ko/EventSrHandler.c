// module: mt7915.ko
// function: EventSrHandler @ 0x171444
// size: 268 bytes
//

void EventSrHandler(undefined4 param_1,undefined1 *param_2)

{
  undefined1 uVar1;
  
  uVar1 = *param_2;
  if (3 < DebugLevel) {
    printk("%s: u1EventSubId = %d\n","EventSrHandler",uVar1);
  }
  switch(uVar1) {
  case 1:
    PrintSrEventSrCap(param_2);
    return;
  case 2:
    PrintSrEventSrPara(param_2);
    return;
  case 3:
    PrintSrEventSrGloVarSingleDropTa(param_2);
    return;
  case 4:
    PrintSrEventSrInd(param_2);
    return;
  case 5:
    PrintSrEventSrCond(param_2);
    return;
  case 6:
    PrintSrEventSrRcpiTbl(param_2);
    return;
  case 7:
    PrintSrEventSrRcpiTblOfst(param_2);
    return;
  case 8:
    PrintSrEventSrQCtrl(param_2);
    return;
  case 9:
    PrintSrEventSrIBPD(param_2);
    return;
  case 10:
    PrintSrEventSrNRT(param_2);
    return;
  case 0xb:
    PrintSrEventSrNRTCtrl(param_2);
    return;
  case 0xc:
  case 0xd:
  case 0xe:
  case 0xf:
  case 0x10:
  case 0x11:
  case 0x12:
  case 0x13:
  case 0x14:
  case 0x15:
  case 0x16:
  case 0x17:
  case 0x18:
  case 0x19:
    break;
  case 0x1a:
    PrintSrEventSrCnt(param_2);
    return;
  case 0x1b:
    PrintSrEventSrSd(param_2);
    return;
  case 0x1c:
    PrintSrEventSrSrgBitmap(param_2);
    return;
  default:
    return;
  }
  if (-1 < DebugLevel) {
    FUN_0016b708(param_2);
    return;
  }
  return;
}

