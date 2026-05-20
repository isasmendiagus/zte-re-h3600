// module: mt7915.ko
// function: scan_partial_init @ 0x144400
// size: 164 bytes
//

undefined4 scan_partial_init(int param_1)

{
  *(undefined1 *)(param_1 + 0x8293ec) = 0;
  *(undefined1 *)(param_1 + 0x8293ee) = 0;
  *(undefined4 *)(param_1 + 0x8293f0) = 0;
  *(undefined1 *)(param_1 + 0x8293ed) = 1;
  RTMPInitTimer(param_1,param_1 + 0x8293f8,rtmp_timer_restart_partial_scan,param_1 + 0x8293ec,0);
  *(undefined1 *)(param_1 + 0x8d89c5) = 1;
  *(undefined1 *)(param_1 + 0x8d89c4) = 0;
  *(undefined1 *)(param_1 + 0x8d89c6) = 0;
  *(undefined4 *)(param_1 + 0x8d89c8) = 0;
  RTMPInitTimer(param_1,param_1 + 0x8d89d0,rtmp_timer_restart_partial_scan,param_1 + 0x8d89c4,0);
  return 0;
}

