# Offline libnice diagnostic

Generated: Sat May 16 12:21:13 AM EDT 2026

## ss -unap (UDP sockets bound by backend)

```
```

## Candidate / STUN / binding lines

```
0:00:03.652393650 [34m 8865[00m 0xffff9000b4c0 [37mDEBUG  [00m [00m           webrtcice gstwebrtcice.c:797:gst_webrtc_ice_gather_candidates:<webrtcbin0:ice>[00m gather candidates for stream 1
0:00:03.742866519 [34m 8865[00m 0xffff900086a0 [37mDEBUG  [00m [00m           webrtcice gstwebrtcice.c:797:gst_webrtc_ice_gather_candidates:<webrtcbin1:ice>[00m gather candidates for stream 1
0:00:03.944692420 [34m 8865[00m 0xffff981bdc60 [37mDEBUG  [00m [00m           webrtcice gstwebrtcice.c:797:gst_webrtc_ice_gather_candidates:<webrtcbin2:ice>[00m gather candidates for stream 1
0:00:04.174704805 [34m 8865[00m 0xffff981bdd20 [37mDEBUG  [00m [00m           webrtcice gstwebrtcice.c:797:gst_webrtc_ice_gather_candidates:<webrtcbin3:ice>[00m gather candidates for stream 1
0:00:08.738661960 [34m 8865[00m 0xffff28003d20 [37mDEBUG  [00m [00m           webrtcice gstwebrtcice.c:797:gst_webrtc_ice_gather_candidates:<webrtcbin4:ice>[00m gather candidates for stream 1
0:00:09.080481851 [34m 8865[00m 0xffff981bdf00 [37mDEBUG  [00m [00m           webrtcice gstwebrtcice.c:797:gst_webrtc_ice_gather_candidates:<webrtcbin5:ice>[00m gather candidates for stream 1
0:00:09.283297796 [34m 8865[00m 0xffff28007580 [37mDEBUG  [00m [00m           webrtcice gstwebrtcice.c:797:gst_webrtc_ice_gather_candidates:<webrtcbin6:ice>[00m gather candidates for stream 1
0:00:09.484923247 [34m 8865[00m 0xffff28003d80 [37mDEBUG  [00m [00m           webrtcice gstwebrtcice.c:797:gst_webrtc_ice_gather_candidates:<webrtcbin7:ice>[00m gather candidates for stream 1
```

## libnice marker lines (sanity)

```
```

## ICE state transitions

```
0:00:03.682885752  8865 0xffff9000b4c0 INFO               webrtcbin gstwebrtcbin.c:1373:_update_ice_gathering_state_task:<webrtcbin> ICE gathering state change from new(0) to gathering(1)
0:00:03.745493697  8865 0xffff900086a0 INFO               webrtcbin gstwebrtcbin.c:1373:_update_ice_gathering_state_task:<webrtcbin> ICE gathering state change from new(0) to gathering(1)
0:00:03.883418754  8865 0xffff9000b4c0 INFO               webrtcbin gstwebrtcbin.c:1373:_update_ice_gathering_state_task:<webrtcbin> ICE gathering state change from gathering(1) to complete(2)
0:00:03.945868606  8865 0xffff900086a0 INFO               webrtcbin gstwebrtcbin.c:1373:_update_ice_gathering_state_task:<webrtcbin> ICE gathering state change from gathering(1) to complete(2)
0:00:03.947595683  8865 0xffff981bdc60 INFO               webrtcbin gstwebrtcbin.c:1373:_update_ice_gathering_state_task:<webrtcbin> ICE gathering state change from new(0) to gathering(1)
0:00:04.148043398  8865 0xffff981bdc60 INFO               webrtcbin gstwebrtcbin.c:1373:_update_ice_gathering_state_task:<webrtcbin> ICE gathering state change from gathering(1) to complete(2)
0:00:04.178576239  8865 0xffff981bdd20 INFO               webrtcbin gstwebrtcbin.c:1373:_update_ice_gathering_state_task:<webrtcbin> ICE gathering state change from new(0) to gathering(1)
0:00:04.240511780  8865 0xffff9000b4c0 INFO               webrtcbin gstwebrtcbin.c:1409:_update_ice_connection_state_task:<webrtcbin> ICE connection state change from new(0) to checking(1)
0:00:04.240557799  8865 0xffff9000b4c0 INFO               webrtcbin gstwebrtcbin.c:1446:_update_peer_connection_state_task:<webrtcbin> Peer connection state change from new(0) to connecting(1)
0:00:04.241016714  8865 0xffff900086a0 INFO               webrtcbin gstwebrtcbin.c:1409:_update_ice_connection_state_task:<webrtcbin> ICE connection state change from new(0) to checking(1)
0:00:04.241043565  8865 0xffff900086a0 INFO               webrtcbin gstwebrtcbin.c:1446:_update_peer_connection_state_task:<webrtcbin> Peer connection state change from new(0) to connecting(1)
0:00:04.241077935  8865 0xffff981bdd20 INFO               webrtcbin gstwebrtcbin.c:1409:_update_ice_connection_state_task:<webrtcbin> ICE connection state change from new(0) to checking(1)
0:00:04.241096753  8865 0xffff981bdd20 INFO               webrtcbin gstwebrtcbin.c:1446:_update_peer_connection_state_task:<webrtcbin> Peer connection state change from new(0) to connecting(1)
0:00:04.241289407  8865 0xffff981bdc60 INFO               webrtcbin gstwebrtcbin.c:1409:_update_ice_connection_state_task:<webrtcbin> ICE connection state change from new(0) to checking(1)
0:00:04.241321090  8865 0xffff981bdc60 INFO               webrtcbin gstwebrtcbin.c:1446:_update_peer_connection_state_task:<webrtcbin> Peer connection state change from new(0) to connecting(1)
0:00:04.379055923  8865 0xffff981bdd20 INFO               webrtcbin gstwebrtcbin.c:1373:_update_ice_gathering_state_task:<webrtcbin> ICE gathering state change from gathering(1) to complete(2)
0:00:08.741187114  8865 0xffff28003d20 INFO               webrtcbin gstwebrtcbin.c:1373:_update_ice_gathering_state_task:<webrtcbin> ICE gathering state change from new(0) to gathering(1)
0:00:08.941666080  8865 0xffff28003d20 INFO               webrtcbin gstwebrtcbin.c:1373:_update_ice_gathering_state_task:<webrtcbin> ICE gathering state change from gathering(1) to complete(2)
0:00:09.083295923  8865 0xffff981bdf00 INFO               webrtcbin gstwebrtcbin.c:1373:_update_ice_gathering_state_task:<webrtcbin> ICE gathering state change from new(0) to gathering(1)
0:00:09.283598459  8865 0xffff981bdf00 INFO               webrtcbin gstwebrtcbin.c:1373:_update_ice_gathering_state_task:<webrtcbin> ICE gathering state change from gathering(1) to complete(2)
0:00:09.285880906  8865 0xffff28007580 INFO               webrtcbin gstwebrtcbin.c:1373:_update_ice_gathering_state_task:<webrtcbin> ICE gathering state change from new(0) to gathering(1)
0:00:09.486291352  8865 0xffff28007580 INFO               webrtcbin gstwebrtcbin.c:1373:_update_ice_gathering_state_task:<webrtcbin> ICE gathering state change from gathering(1) to complete(2)
0:00:09.487923093  8865 0xffff28003d80 INFO               webrtcbin gstwebrtcbin.c:1373:_update_ice_gathering_state_task:<webrtcbin> ICE gathering state change from new(0) to gathering(1)
0:00:09.553015063  8865 0xffff28003d20 INFO               webrtcbin gstwebrtcbin.c:1409:_update_ice_connection_state_task:<webrtcbin> ICE connection state change from new(0) to checking(1)
0:00:09.553062618  8865 0xffff28003d20 INFO               webrtcbin gstwebrtcbin.c:1446:_update_peer_connection_state_task:<webrtcbin> Peer connection state change from new(0) to connecting(1)
0:00:09.554882214  8865 0xffff28007580 INFO               webrtcbin gstwebrtcbin.c:1409:_update_ice_connection_state_task:<webrtcbin> ICE connection state change from new(0) to checking(1)
0:00:09.554916841  8865 0xffff28007580 INFO               webrtcbin gstwebrtcbin.c:1446:_update_peer_connection_state_task:<webrtcbin> Peer connection state change from new(0) to connecting(1)
0:00:09.556591145  8865 0xffff981bdf00 INFO               webrtcbin gstwebrtcbin.c:1409:_update_ice_connection_state_task:<webrtcbin> ICE connection state change from new(0) to checking(1)
0:00:09.556625036  8865 0xffff981bdf00 INFO               webrtcbin gstwebrtcbin.c:1446:_update_peer_connection_state_task:<webrtcbin> Peer connection state change from new(0) to connecting(1)
0:00:09.556670319  8865 0xffff28003d80 INFO               webrtcbin gstwebrtcbin.c:1409:_update_ice_connection_state_task:<webrtcbin> ICE connection state change from new(0) to checking(1)
0:00:09.556693073  8865 0xffff28003d80 INFO               webrtcbin gstwebrtcbin.c:1446:_update_peer_connection_state_task:<webrtcbin> Peer connection state change from new(0) to connecting(1)
0:00:09.688420906  8865 0xffff28003d80 INFO               webrtcbin gstwebrtcbin.c:1373:_update_ice_gathering_state_task:<webrtcbin> ICE gathering state change from gathering(1) to complete(2)
```

## Errors / warnings

```
0:00:03.283041699  8865 0xffff9000b4c0 WARN               webrtcbin gstwebrtcbin.c:3112:sdp_media_from_transceiver:<webrtcbin> Caps application/x-rtp, media=(string)video, payload=(int)96, encoding-name=(string)H264, packetization-mode=(string)1, clock-rate=(int)90000, rtcp-fb-nack-pli=(boolean)true, rtcp-fb-transport-cc=(boolean)true are missing ssrc
Failed to open /dev/video3: No such file or directory
0:00:03.737026326  8865 0xffff900086a0 WARN               webrtcbin gstwebrtcbin.c:3112:sdp_media_from_transceiver:<webrtcbin> Caps application/x-rtp, media=(string)video, payload=(int)96, encoding-name=(string)H264, packetization-mode=(string)1, clock-rate=(int)90000, rtcp-fb-nack-pli=(boolean)true, rtcp-fb-transport-cc=(boolean)true are missing ssrc
Failed to open /dev/video3: No such file or directory
0:00:03.939708133  8865 0xffff981bdc60 WARN               webrtcbin gstwebrtcbin.c:3112:sdp_media_from_transceiver:<webrtcbin> Caps application/x-rtp, media=(string)video, payload=(int)96, encoding-name=(string)H264, packetization-mode=(string)1, clock-rate=(int)90000, rtcp-fb-nack-pli=(boolean)true, rtcp-fb-transport-cc=(boolean)true are missing ssrc
0:00:04.167591491  8865 0xffff981bdd20 WARN               webrtcbin gstwebrtcbin.c:3112:sdp_media_from_transceiver:<webrtcbin> Caps application/x-rtp, media=(string)video, payload=(int)96, encoding-name=(string)H264, packetization-mode=(string)1, clock-rate=(int)90000, rtcp-fb-nack-pli=(boolean)true, rtcp-fb-transport-cc=(boolean)true are missing ssrc
0:00:08.733887610  8865 0xffff28003d20 WARN               webrtcbin gstwebrtcbin.c:3112:sdp_media_from_transceiver:<webrtcbin> Caps application/x-rtp, media=(string)video, payload=(int)96, encoding-name=(string)H264, packetization-mode=(string)1, clock-rate=(int)90000, rtcp-fb-nack-pli=(boolean)true, rtcp-fb-transport-cc=(boolean)true are missing ssrc
Failed to open /dev/video3: No such file or directory
0:00:09.075511293  8865 0xffff981bdf00 WARN               webrtcbin gstwebrtcbin.c:3112:sdp_media_from_transceiver:<webrtcbin> Caps application/x-rtp, media=(string)video, payload=(int)96, encoding-name=(string)H264, packetization-mode=(string)1, clock-rate=(int)90000, rtcp-fb-nack-pli=(boolean)true, rtcp-fb-transport-cc=(boolean)true are missing ssrc
Failed to open /dev/video3: No such file or directory
0:00:09.278144185  8865 0xffff28007580 WARN               webrtcbin gstwebrtcbin.c:3112:sdp_media_from_transceiver:<webrtcbin> Caps application/x-rtp, media=(string)video, payload=(int)96, encoding-name=(string)H264, packetization-mode=(string)1, clock-rate=(int)90000, rtcp-fb-nack-pli=(boolean)true, rtcp-fb-transport-cc=(boolean)true are missing ssrc
0:00:09.480336623  8865 0xffff28003d80 WARN               webrtcbin gstwebrtcbin.c:3112:sdp_media_from_transceiver:<webrtcbin> Caps application/x-rtp, media=(string)video, payload=(int)96, encoding-name=(string)H264, packetization-mode=(string)1, clock-rate=(int)90000, rtcp-fb-nack-pli=(boolean)true, rtcp-fb-transport-cc=(boolean)true are missing ssrc
```

## Raw stderr line count
317 /tmp/cam.err
