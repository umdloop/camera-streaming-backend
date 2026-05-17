# Probes

Generated: Sat May 16 12:25:46 AM EDT 2026

## Backend PID
9052

## ss -unap (no filter, first 60 lines)
```
State  Recv-Q Send-Q   Local Address:Port  Peer Address:PortProcess                                                   
UNCONN 0      0        192.168.88.90:34395      0.0.0.0:*    users:(("camera-stream",pid=9052,fd=95))                 
UNCONN 0      0      239.255.255.250:1900       0.0.0.0:*    users:(("camera-stream",pid=9052,fd=198))                
UNCONN 0      0        192.168.88.90:1900       0.0.0.0:*    users:(("camera-stream",pid=9052,fd=197))                
UNCONN 0      0      239.255.255.250:1900       0.0.0.0:*    users:(("camera-stream",pid=9052,fd=195))                
UNCONN 0      0            127.0.0.1:1900       0.0.0.0:*    users:(("camera-stream",pid=9052,fd=192))                
UNCONN 0      0      239.255.255.250:1900       0.0.0.0:*    users:(("camera-stream",pid=9052,fd=117))                
UNCONN 0      0        192.168.88.90:1900       0.0.0.0:*    users:(("camera-stream",pid=9052,fd=113))                
UNCONN 0      0      239.255.255.250:1900       0.0.0.0:*    users:(("camera-stream",pid=9052,fd=106))                
UNCONN 0      0            127.0.0.1:1900       0.0.0.0:*    users:(("camera-stream",pid=9052,fd=105))                
UNCONN 0      0      239.255.255.250:1900       0.0.0.0:*    users:(("camera-stream",pid=9052,fd=93))                 
UNCONN 0      0        192.168.88.90:1900       0.0.0.0:*    users:(("camera-stream",pid=9052,fd=94))                 
UNCONN 0      0      239.255.255.250:1900       0.0.0.0:*    users:(("camera-stream",pid=9052,fd=91))                 
UNCONN 0      0        192.168.88.90:1900       0.0.0.0:*    users:(("camera-stream",pid=9052,fd=90))                 
UNCONN 0      0      239.255.255.250:1900       0.0.0.0:*    users:(("camera-stream",pid=9052,fd=87))                 
UNCONN 0      0            127.0.0.1:1900       0.0.0.0:*    users:(("camera-stream",pid=9052,fd=85))                 
UNCONN 0      0      239.255.255.250:1900       0.0.0.0:*    users:(("camera-stream",pid=9052,fd=84))                 
UNCONN 0      0            127.0.0.1:1900       0.0.0.0:*    users:(("camera-stream",pid=9052,fd=80))                 
UNCONN 0      0              0.0.0.0:35034      0.0.0.0:*    users:(("avahi-daemon",pid=1116,fd=14))                  
UNCONN 0      0        192.168.88.90:52048      0.0.0.0:*    users:(("camera-stream",pid=9052,fd=82))                 
UNCONN 0      0            127.0.0.1:35685      0.0.0.0:*    users:(("camera-stream",pid=9052,fd=89))                 
UNCONN 0      0            127.0.0.1:35837      0.0.0.0:*    users:(("camera-stream",pid=9052,fd=107))                
UNCONN 0      0        192.168.88.90:35983      0.0.0.0:*    users:(("camera-stream",pid=9052,fd=92))                 
UNCONN 0      0        192.168.88.90:60930      0.0.0.0:*    users:(("camera-stream",pid=9052,fd=81))                 
UNCONN 0      0        192.168.88.90:45778      0.0.0.0:*    users:(("camera-stream",pid=9052,fd=116))                
UNCONN 0      0        192.168.88.90:46171      0.0.0.0:*    users:(("camera-stream",pid=9052,fd=193))                
UNCONN 0      0              0.0.0.0:5353       0.0.0.0:*    users:(("avahi-daemon",pid=1116,fd=12))                  
UNCONN 0      0        192.168.88.90:55383      0.0.0.0:*    users:(("camera-stream",pid=9052,fd=200))                
UNCONN 0      0            127.0.0.1:39502      0.0.0.0:*    users:(("camera-stream",pid=9052,fd=86))                 
UNCONN 0      0            127.0.0.1:56002      0.0.0.0:*    users:(("camera-stream",pid=9052,fd=196))                
UNCONN 0      0        192.168.88.90:56560      0.0.0.0:*    users:(("camera-stream",pid=9052,fd=104))                
UNCONN 0      0           127.0.0.53:53         0.0.0.0:*    users:(("systemd-resolve",pid=887,fd=13))                
UNCONN 0      0              0.0.0.0:111        0.0.0.0:*    users:(("rpcbind",pid=886,fd=5),("systemd",pid=1,fd=290))
UNCONN 0      0                    *:5353             *:*    users:(("avahi-daemon",pid=1116,fd=13))                  
UNCONN 0      0                    *:32833            *:*    users:(("avahi-daemon",pid=1116,fd=15))                  
UNCONN 0      0                    *:111              *:*    users:(("rpcbind",pid=886,fd=7),("systemd",pid=1,fd=292))
```

## lsof UDP for backend
```
COMMAND    PID            USER   FD      TYPE             DEVICE SIZE/OFF     NODE NAME
systemd      1            root  290u     IPv4              31159      0t0      UDP *:111 
systemd      1            root  292u     IPv6              31160      0t0      UDP *:111 
rpcbind    886            _rpc    5u     IPv4              31159      0t0      UDP *:111 
rpcbind    886            _rpc    7u     IPv6              31160      0t0      UDP *:111 
systemd-r  887 systemd-resolve   13u     IPv4              23194      0t0      UDP 127.0.0.53:53 
avahi-dae 1116           avahi   12u     IPv4              41538      0t0      UDP *:5353 
avahi-dae 1116           avahi   13u     IPv6              41539      0t0      UDP *:5353 
avahi-dae 1116           avahi   14u     IPv4              41540      0t0      UDP *:35034 
avahi-dae 1116           avahi   15u     IPv6              41541      0t0      UDP *:32833 
camera-st 9052         umdloop  cwd       DIR              259,1     4096  7495099 /home/umdloop/infrastructure/camera-streaming-backend
camera-st 9052         umdloop  rtd       DIR              259,1     4096        2 /
camera-st 9052         umdloop  txt       REG              259,1  1933152  7490882 /home/umdloop/infrastructure/camera-streaming-backend/build/camera-stream
camera-st 9052         umdloop  mem       REG                0,9              8095 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8096 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8097 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8098 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8103 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8108 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8113 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8118 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8123 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8128 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8133 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8136 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8138 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8139 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8140 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8141 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8142 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8144 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8145 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8149 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8151 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8154 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8161 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8162 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8335 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8312 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8287 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8264 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8326 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8318 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8317 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8315 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8298 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8297 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8157 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8156 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8155 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8160 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8159 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8158 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8296 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8301 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8300 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8299 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8316 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8278 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8250 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8249 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8248 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       CHR               81,2              1601 /dev/video2
camera-st 9052         umdloop  mem       REG                0,9              8239 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8230 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8216 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8197 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8269 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8224 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8223 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8222 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8221 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8220 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8219 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8267 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8253 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8252 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8251 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8173 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8188 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8180 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8179 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8178 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8177 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8270 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              7991 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       CHR               81,4               661 /dev/video4
camera-st 9052         umdloop  mem       CHR               81,6               665 /dev/video6
camera-st 9052         umdloop  mem       REG                0,9              7977 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              7976 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              7975 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              7980 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              7979 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              7978 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG              259,1    83776 13915117 /usr/lib/aarch64-linux-gnu/nvidia/libnvcucompat.so
camera-st 9052         umdloop  mem       REG              259,1    27328 13908092 /usr/lib/aarch64-linux-gnu/gstreamer-1.0/libgstnice.so
camera-st 9052         umdloop  mem       REG              259,1    14384 13919086 /usr/lib/aarch64-linux-gnu/libplds4.so
camera-st 9052         umdloop  mem       REG                0,9              8268 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG              259,1    18448 13921772 /usr/lib/aarch64-linux-gnu/libplc4.so
camera-st 9052         umdloop  mem       REG              259,1  1096384 13915059 /usr/lib/aarch64-linux-gnu/libnss3.so
camera-st 9052         umdloop  mem       REG              259,1 29472384 13922337 /usr/lib/aarch64-linux-gnu/libicudata.so.70.1
camera-st 9052         umdloop  mem       REG              259,1 35810056 13915098 /usr/lib/aarch64-linux-gnu/nvidia/libnvidia-eglcore.so.540.5.0
camera-st 9052         umdloop  mem       REG              259,1   199456 13920571 /usr/lib/aarch64-linux-gnu/libnssutil3.so
camera-st 9052         umdloop  mem       REG              259,1   246112 13922484 /usr/lib/aarch64-linux-gnu/libnspr4.so
camera-st 9052         umdloop  mem       REG              259,1    80208 13918327 /usr/lib/aarch64-linux-gnu/libsrtp2.so.1
camera-st 9052         umdloop  mem       REG              259,1    36072 13922930 /usr/lib/aarch64-linux-gnu/gstreamer-1.0/libgstvideocrop.so
camera-st 9052         umdloop  mem       CHR               81,0               635 /dev/video0
camera-st 9052         umdloop  mem       REG              259,1   879808 13915144 /usr/lib/aarch64-linux-gnu/nvidia/libnvvideo.so
camera-st 9052         umdloop  mem       REG              259,1   888256 13915235 /usr/lib/aarch64-linux-gnu/nvidia/libnvvideoencode_ppe.so
camera-st 9052         umdloop  mem       REG              259,1 41872560 13915288 /usr/lib/aarch64-linux-gnu/nvidia/libcuda.so.1.1
camera-st 9052         umdloop  mem       REG              259,1    65536 13930141 /usr/lib/aarch64-linux-gnu/gstreamer-1.0/libgstsrtp.so
camera-st 9052         umdloop  mem       REG              259,1    39208 13915126 /usr/lib/aarch64-linux-gnu/nvidia/libnvmmlite_image.so
camera-st 9052         umdloop  mem       REG              259,1   231640 13915238 /usr/lib/aarch64-linux-gnu/nvidia/libnvparser.so
camera-st 9052         umdloop  mem       REG              259,1    18280 13915119 /usr/lib/aarch64-linux-gnu/nvidia/libnvmmlite_utils.so
camera-st 9052         umdloop  mem       REG              259,1    10152 13915145 /usr/lib/aarch64-linux-gnu/nvidia/libnvmmlite.so
camera-st 9052         umdloop  mem       REG              259,1    72432 13915232 /usr/lib/aarch64-linux-gnu/nvidia/libnvmm_utils.so
camera-st 9052         umdloop  mem       REG              259,1   939224 13915152 /usr/lib/aarch64-linux-gnu/nvidia/libnvtvmr.so
camera-st 9052         umdloop  mem       REG              259,1   208816 13915103 /usr/lib/aarch64-linux-gnu/nvidia/libnvmmlite_video.so
camera-st 9052         umdloop  mem       REG              259,1   213104 13915276 /usr/lib/aarch64-linux-gnu/nvidia/libtegrav4l2.so
camera-st 9052         umdloop  mem       REG              259,1   107656 13916674 /usr/lib/aarch64-linux-gnu/gstreamer-1.0/libgstdtls.so
camera-st 9052         umdloop  mem       REG              259,1   418032 13922940 /usr/lib/aarch64-linux-gnu/gstreamer-1.0/libgstcoreelements.so
camera-st 9052         umdloop  mem       REG              259,1    93808 13919898 /usr/lib/aarch64-linux-gnu/libgstnet-1.0.so.0.2003.0
camera-st 9052         umdloop  mem       REG              259,1   455464 13922917 /usr/lib/aarch64-linux-gnu/gstreamer-1.0/libgstrtpmanager.so
camera-st 9052         umdloop  mem       REG              259,1  2037928 13917363 /usr/lib/aarch64-linux-gnu/libicuuc.so.70.1
camera-st 9052         umdloop  mem       REG              259,1  1330336 13918260 /usr/lib/aarch64-linux-gnu/libsqlite3.so.0.8.6
camera-st 9052         umdloop  mem       REG              259,1    26616 13916228 /usr/lib/aarch64-linux-gnu/libuuid.so.1.3.0
camera-st 9052         umdloop  mem       REG              259,1  1934032 13908847 /usr/lib/aarch64-linux-gnu/libxml2.so.2.9.13
camera-st 9052         umdloop  mem       REG              259,1   637520 13920733 /usr/lib/aarch64-linux-gnu/libsoup-2.4.so.1.11.2
camera-st 9052         umdloop  mem       REG              259,1    79720 13919902 /usr/lib/aarch64-linux-gnu/libgssdp-1.2.so.0.104.0
camera-st 9052         umdloop  mem       REG              259,1   218984 13917386 /usr/lib/aarch64-linux-gnu/libgupnp-1.2.so.1.104.3
camera-st 9052         umdloop  mem       REG              259,1    34664 13922252 /usr/lib/aarch64-linux-gnu/libgupnp-igd-1.0.so.4.2.1
camera-st 9052         umdloop  mem       REG              259,1    81216 13908046 /usr/lib/aarch64-linux-gnu/libgstapp-1.0.so.0.2001.0
camera-st 9052         umdloop  mem       REG              259,1   319752 13921702 /usr/lib/aarch64-linux-gnu/libnice.so.10.11.0
camera-st 9052         umdloop  mem       REG              259,1    10168 13921814 /usr/lib/aarch64-linux-gnu/libgstsctp-1.0.so.0.2003.0
camera-st 9052         umdloop  mem       REG              259,1   227552 13930179 /usr/lib/aarch64-linux-gnu/gstreamer-1.0/libgstwebrtc.so
camera-st 9052         umdloop  mem       REG              259,1   624320 13922974 /usr/lib/aarch64-linux-gnu/gstreamer-1.0/libgstrtp.so
camera-st 9052         umdloop  mem       REG              259,1   466424 13918230 /usr/lib/aarch64-linux-gnu/libgstcodecparsers-1.0.so.0.2003.0
camera-st 9052         umdloop  mem       REG              259,1   260600 13930165 /usr/lib/aarch64-linux-gnu/gstreamer-1.0/libgstvideoparsersbad.so
camera-st 9052         umdloop  mem       REG              259,1    10104 13908261 /usr/lib/aarch64-linux-gnu/nvidia/libgstnvdsseimeta.so.1.0.0
camera-st 9052         umdloop  mem       REG              259,1     9888 13908260 /usr/lib/aarch64-linux-gnu/nvidia/libgstnvcustomhelper.so.1.0.0
camera-st 9052         umdloop  mem       REG              259,1    10264 13915227 /usr/lib/aarch64-linux-gnu/nvidia/libv4l2_nvvideocodec.so
camera-st 9052         umdloop  mem       REG              259,1   328880 13908250 /usr/lib/aarch64-linux-gnu/gstreamer-1.0/libgstnvvideo4linux2.so
camera-st 9052         umdloop  mem       REG              259,1    10184 13918256 /usr/lib/aarch64-linux-gnu/libxshmfence.so.1.0.0
camera-st 9052         umdloop  mem       REG              259,1    26624 13916480 /usr/lib/aarch64-linux-gnu/libxcb-sync.so.1.0.0
camera-st 9052         umdloop  mem       REG              259,1    10216 13918332 /usr/lib/aarch64-linux-gnu/libxcb-present.so.0.0.0
camera-st 9052         umdloop  mem       REG              259,1    14336 13922544 /usr/lib/aarch64-linux-gnu/libxcb-dri3.so.0.0.0
camera-st 9052         umdloop  mem       REG              259,1    30696 13919837 /usr/lib/aarch64-linux-gnu/libxcb-xfixes.so.0.0.0
camera-st 9052         umdloop  mem       REG              259,1    18408 13915043 /usr/lib/aarch64-linux-gnu/libxcb-dri2.so.0.0.0
camera-st 9052         umdloop  mem       REG              259,1     5776 13922504 /usr/lib/aarch64-linux-gnu/libX11-xcb.so.1.0.0
camera-st 9052         umdloop  mem       REG              259,1   305280 13917117 /usr/lib/aarch64-linux-gnu/libglapi.so.0.0.0
camera-st 9052         umdloop  mem       REG              259,1   287952 13921831 /usr/lib/aarch64-linux-gnu/libEGL_mesa.so.0.0.0
camera-st 9052         umdloop  mem       REG              259,1    68888 13915273 /usr/lib/aarch64-linux-gnu/nvidia/libwayland-client.so.0.22.0
camera-st 9052         umdloop  mem       REG              259,1    64800 13915120 /usr/lib/aarch64-linux-gnu/nvidia/libnvidia-egl-wayland.so.1.1.11
camera-st 9052         umdloop  mem       REG              259,1    20400 13915247 /usr/lib/aarch64-linux-gnu/nvidia/libnvimp.so
camera-st 9052         umdloop  mem       REG              259,1    59512 13915226 /usr/lib/aarch64-linux-gnu/nvidia/libnvdc.so
camera-st 9052         umdloop  mem       REG              259,1    43128 13916561 /usr/lib/aarch64-linux-gnu/libmd.so.0.0.5
camera-st 9052         umdloop  mem       REG              259,1    80696 13920645 /usr/lib/aarch64-linux-gnu/libbsd.so.0.11.5
camera-st 9052         umdloop  mem       REG              259,1    22472 13921835 /usr/lib/aarch64-linux-gnu/libXdmcp.so.6.0.0
camera-st 9052         umdloop  mem       REG              259,1    14392 13915656 /usr/lib/aarch64-linux-gnu/libXau.so.6.0.0
camera-st 9052         umdloop  mem       REG              259,1   162168 13917561 /usr/lib/aarch64-linux-gnu/libxcb.so.1.1.0
camera-st 9052         umdloop  mem       REG              259,1    63472 13916234 /usr/lib/aarch64-linux-gnu/libxcb-randr.so.0.1.0
camera-st 9052         umdloop  mem       REG                0,9              8320 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG              259,1   170072 13907934 /usr/lib/aarch64-linux-gnu/libexpat.so.1.8.7
camera-st 9052         umdloop  mem       REG              259,1   134664 13915301 /usr/lib/aarch64-linux-gnu/nvidia/libwayland-server.so.0.22.0
camera-st 9052         umdloop  mem       REG                0,9              8319 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG              259,1    60288 13918473 /usr/lib/aarch64-linux-gnu/libgbm.so.1.0.0
camera-st 9052         umdloop  mem       REG              259,1    84464 13919003 /usr/lib/aarch64-linux-gnu/libdrm.so.2.4.0
camera-st 9052         umdloop  mem       REG              259,1    22784 13915139 /usr/lib/aarch64-linux-gnu/nvidia/libnvidia-egl-gbm.so.1.1.0
camera-st 9052         umdloop  mem       REG              259,1   273672 13915293 /usr/lib/aarch64-linux-gnu/nvidia/libnvidia-rmapi-tegra.so.540.5.0
camera-st 9052         umdloop  mem       REG              259,1   550128 13915219 /usr/lib/aarch64-linux-gnu/nvidia/libnvidia-glsi.so.540.5.0
camera-st 9052         umdloop  mem       REG              259,1  1263792 13917643 /usr/lib/aarch64-linux-gnu/tegra-egl/libEGL_nvidia.so.0
camera-st 9052         umdloop  mem       REG              259,1    13752 13907542 /usr/lib/aarch64-linux-gnu/libpthread.so.0
camera-st 9052         umdloop  mem       REG              259,1     6240 13907544 /usr/lib/aarch64-linux-gnu/librt.so.1
camera-st 9052         umdloop  mem       REG                0,9              8332 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG              259,1     6152 13907528 /usr/lib/aarch64-linux-gnu/libdl.so.2
camera-st 9052         umdloop  mem       REG                0,9              8330 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG              259,1    96512 13915318 /usr/lib/aarch64-linux-gnu/nvidia/libnvcolorutil.so
camera-st 9052         umdloop  mem       REG              259,1    34920 13915280 /usr/lib/aarch64-linux-gnu/nvidia/libnvrm_stream.so
camera-st 9052         umdloop  mem       REG              259,1    10072 13915150 /usr/lib/aarch64-linux-gnu/nvidia/libnvtegrahv.so
camera-st 9052         umdloop  mem       REG                0,9              8329 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG              259,1  1517784 13917429 /usr/lib/aarch64-linux-gnu/libGLdispatch.so.0.0.0
camera-st 9052         umdloop  mem       REG              259,1    26832 13915161 /usr/lib/aarch64-linux-gnu/nvidia/libnvrm_sync.so
camera-st 9052         umdloop  mem       REG              259,1    14472 13915125 /usr/lib/aarch64-linux-gnu/nvidia/libnvsocsys.so
camera-st 9052         umdloop  mem       REG                0,9              8314 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG              259,1   112928 13915157 /usr/lib/aarch64-linux-gnu/nvidia/libnvsciipc.so
camera-st 9052         umdloop  mem       REG              259,1   116968 13915261 /usr/lib/aarch64-linux-gnu/nvidia/libnvvic.so
camera-st 9052         umdloop  mem       REG              259,1    75880 13915268 /usr/lib/aarch64-linux-gnu/nvidia/libnvrm_host1x.so
camera-st 9052         umdloop  mem       REG                0,9              8313 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG              259,1   399880 13915263 /usr/lib/aarch64-linux-gnu/nvidia/libnvrm_gpu.so
camera-st 9052         umdloop  mem       REG              259,1    10112 13915123 /usr/lib/aarch64-linux-gnu/nvidia/libnvbuf_fdmap.so.1.0.0
camera-st 9052         umdloop  mem       REG                0,9              8309 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG              259,1    68016 13915257 /usr/lib/aarch64-linux-gnu/nvidia/libnvos.so
camera-st 9052         umdloop  mem       REG                0,9              8307 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG              259,1    68040 13922717 /usr/lib/aarch64-linux-gnu/libEGL.so.1.1.0
camera-st 9052         umdloop  mem       REG              259,1    14520 13915142 /usr/lib/aarch64-linux-gnu/nvidia/libnvrm_chip.so
camera-st 9052         umdloop  mem       REG                0,9              8306 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG              259,1   166144 13915229 /usr/lib/aarch64-linux-gnu/nvidia/libnvrm_surface.so
camera-st 9052         umdloop  mem       REG              259,1 24064976 13915147 /usr/lib/aarch64-linux-gnu/nvidia/libnvbufsurftransform.so.1.0.0
camera-st 9052         umdloop  mem       REG              259,1   774488 13915223 /usr/lib/aarch64-linux-gnu/nvidia/libnvbufsurface.so.1.0.0
camera-st 9052         umdloop  mem       REG                0,9              8284 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG              259,1    34960 13915278 /usr/lib/aarch64-linux-gnu/nvidia/libnvrm_mem.so
camera-st 9052         umdloop  mem       REG                0,9              8282 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG              259,1   778576 13908249 /usr/lib/aarch64-linux-gnu/gstreamer-1.0/libgstnvvidconv.so
camera-st 9052         umdloop  mem       REG                0,9              8272 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG              259,1    27520 13930237 /usr/lib/aarch64-linux-gnu/gstreamer-1.0/libgstvideoconvert.so
camera-st 9052         umdloop  mem       REG              259,1   301792 13921837 /usr/lib/aarch64-linux-gnu/libjpeg.so.8.2.2
camera-st 9052         umdloop  mem       REG                0,9              8271 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG              259,1    48296 13930239 /usr/lib/aarch64-linux-gnu/gstreamer-1.0/libgstvideorate.so
camera-st 9052         umdloop  mem       REG              259,1   150024 13915282 /usr/lib/aarch64-linux-gnu/nvidia/libnvv4lconvert.so
camera-st 9052         umdloop  mem       REG                0,9              8281 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG              259,1   162152 13917639 /usr/lib/aarch64-linux-gnu/libudev.so.1.7.2
camera-st 9052         umdloop  mem       REG              259,1  1072016 13915245 /usr/lib/aarch64-linux-gnu/nvidia/libnvv4l2.so
camera-st 9052         umdloop  mem       REG                0,9              8266 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG              259,1    46952 13917455 /usr/lib/aarch64-linux-gnu/libgudev-1.0.so.0.3.0
camera-st 9052         umdloop  mem       REG              259,1   321256 13922955 /usr/lib/aarch64-linux-gnu/gstreamer-1.0/libgstvideo4linux2.so
camera-st 9052         umdloop  mem       REG              259,1   147968 13916585 /usr/lib/aarch64-linux-gnu/gstreamer-1.0/libgstdecklink.so
camera-st 9052         umdloop  mem       REG              259,1   141304 13917576 /usr/lib/aarch64-linux-gnu/libgpg-error.so.0.32.1
camera-st 9052         umdloop  mem       REG                0,9              8261 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG              259,1   893312 13917539 /usr/lib/aarch64-linux-gnu/libgcrypt.so.20.3.4
camera-st 9052         umdloop  mem       REG              259,1   112632 13922835 /usr/lib/aarch64-linux-gnu/liblz4.so.1.9.3
camera-st 9052         umdloop  mem       REG              259,1   817008 13918472 /usr/lib/aarch64-linux-gnu/libsystemd.so.0.32.0
camera-st 9052         umdloop  mem       REG                0,9              8265 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8182 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG              259,1    48560 13922966 /usr/lib/aarch64-linux-gnu/gstreamer-1.0/libgstjpeg.so
camera-st 9052         umdloop  mem       REG              259,1    14352 13921734 /usr/lib/aarch64-linux-gnu/spa-0.2/support/libspa-journal.so
camera-st 9052         umdloop  mem       REG              259,1  6039648 13906886 /usr/lib/locale/locale-archive
camera-st 9052         umdloop  mem       REG              259,1   854712 13918191 /usr/lib/aarch64-linux-gnu/libpipewire-0.3.so.0.348.0
camera-st 9052         umdloop  mem       REG                0,9              8259 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG              259,1   108632 13921732 /usr/lib/aarch64-linux-gnu/spa-0.2/support/libspa-support.so
camera-st 9052         umdloop  mem       REG              259,1   116712 13922908 /usr/lib/aarch64-linux-gnu/gstreamer-1.0/libgstpipewire.so
camera-st 9052         umdloop  mem       REG              259,1    60104 13907543 /usr/lib/aarch64-linux-gnu/libresolv.so.2
camera-st 9052         umdloop  mem       REG              259,1    18280 13919960 /usr/lib/aarch64-linux-gnu/libkeyutils.so.1.9
camera-st 9052         umdloop  mem       REG                0,9              8258 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG              259,1   133232 13921842 /usr/lib/aarch64-linux-gnu/libbrotlicommon.so.1.0.9
camera-st 9052         umdloop  mem       REG              259,1   101120 13922685 /usr/lib/aarch64-linux-gnu/libsasl2.so.2.0.25
camera-st 9052         umdloop  mem       REG              259,1    47712 13916258 /usr/lib/aarch64-linux-gnu/libkrb5support.so.0.1
camera-st 9052         umdloop  mem       REG              259,1    14184 13921549 /usr/lib/aarch64-linux-gnu/libcom_err.so.2.1
camera-st 9052         umdloop  mem       REG                0,9              8236 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG              259,1   174424 13918239 /usr/lib/aarch64-linux-gnu/libk5crypto.so.3.1
camera-st 9052         umdloop  mem       REG              259,1   798536 13920167 /usr/lib/aarch64-linux-gnu/libkrb5.so.3.3
camera-st 9052         umdloop  mem       REG                0,9              8234 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG              259,1    83896 13903414 /usr/lib/aarch64-linux-gnu/libtasn1.so.6.6.2
camera-st 9052         umdloop  mem       REG              259,1  1285520 13922234 /usr/lib/aarch64-linux-gnu/libp11-kit.so.0.3.0
camera-st 9052         umdloop  mem       REG              259,1   485688 13916229 /usr/lib/aarch64-linux-gnu/libgmp.so.10.4.1
camera-st 9052         umdloop  mem       REG                0,9              8233 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG              259,1   285496 13916580 /usr/lib/aarch64-linux-gnu/libhogweed.so.6.4
camera-st 9052         umdloop  mem       REG              259,1  1710008 13921833 /usr/lib/aarch64-linux-gnu/libunistring.so.2.2.0
camera-st 9052         umdloop  mem       REG                0,9              8218 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG              259,1    43088 13918380 /usr/lib/aarch64-linux-gnu/libbrotlidec.so.1.0.9
camera-st 9052         umdloop  mem       REG              259,1   730992 13919968 /usr/lib/aarch64-linux-gnu/libzstd.so.1.4.8
camera-st 9052         umdloop  mem       REG              259,1    63696 13899163 /usr/lib/aarch64-linux-gnu/liblber-2.5.so.0.1.15
camera-st 9052         umdloop  mem       REG                0,9              8181 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG              259,1   367984 13899164 /usr/lib/aarch64-linux-gnu/libldap-2.5.so.0.1.15
camera-st 9052         umdloop  mem       REG              259,1   313784 13919609 /usr/lib/aarch64-linux-gnu/libgssapi_krb5.so.2.2
camera-st 9052         umdloop  mem       REG              259,1  2053128 13908130 /usr/lib/aarch64-linux-gnu/libgnutls.so.30.31.0
camera-st 9052         umdloop  mem       REG                0,9              8217 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG              259,1   264304 13922872 /usr/lib/aarch64-linux-gnu/libnettle.so.8.4
camera-st 9052         umdloop  mem       REG                0,9              8334 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8333 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG              259,1    71448 13916581 /usr/lib/aarch64-linux-gnu/libpsl.so.5.3.2
camera-st 9052         umdloop  mem       REG                0,9              8213 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG              259,1   425112 13922209 /usr/lib/aarch64-linux-gnu/libssh.so.4.8.7
camera-st 9052         umdloop  mem       REG                0,9              8211 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG              259,1   113440 13917411 /usr/lib/aarch64-linux-gnu/librtmp.so.1
camera-st 9052         umdloop  mem       REG                0,9              8324 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG              259,1   120680 13917183 /usr/lib/aarch64-linux-gnu/libidn2.so.0.3.7
camera-st 9052         umdloop  mem       REG              259,1   153712 13919980 /usr/lib/aarch64-linux-gnu/libnghttp2.so.14.20.1
camera-st 9052         umdloop  mem       REG                0,9              8331 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG              259,1   603680 13916676 /usr/lib/aarch64-linux-gnu/libcurl-gnutls.so.4.7.0
camera-st 9052         umdloop  mem       REG                0,9              8328 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8311 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8210 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG              259,1    23016 13921521 /usr/lib/aarch64-linux-gnu/libdebuginfod-0.186.so
camera-st 9052         umdloop  mem       REG                0,9              8325 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG              259,1   530880 13916659 /usr/lib/aarch64-linux-gnu/libpcre2-8.so.0.10.4
camera-st 9052         umdloop  mem       REG                0,9              8327 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8323 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8194 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG              259,1   215888 13920737 /usr/lib/aarch64-linux-gnu/libblkid.so.1.1.0
camera-st 9052         umdloop  mem       REG                0,9              8310 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8192 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG              259,1   528104 13918353 /usr/lib/aarch64-linux-gnu/liborc-0.4.so.0.32.0
camera-st 9052         umdloop  mem       REG                0,9              8322 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8286 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8285 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG              259,1    70504 13915760 /usr/lib/aarch64-linux-gnu/libbz2.so.1.0.4
camera-st 9052         umdloop  mem       REG                0,9              8321 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8308 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8283 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8276 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8191 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG              259,1   117176 13916700 /usr/lib/aarch64-linux-gnu/libelf-0.186.so
camera-st 9052         umdloop  mem       REG                0,9              8280 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8277 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG              259,1   157936 13917265 /usr/lib/aarch64-linux-gnu/liblzma.so.5.2.5
camera-st 9052         umdloop  mem       REG                0,9              8279 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG              259,1   161936 13917172 /usr/lib/aarch64-linux-gnu/libselinux.so.1
camera-st 9052         umdloop  mem       REG                0,9              8228 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG              259,1   272896 13917541 /usr/lib/aarch64-linux-gnu/libmount.so.1.1.0
camera-st 9052         umdloop  mem       REG                0,9              8275 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8274 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8263 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8176 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG              259,1   246624 13908062 /usr/lib/aarch64-linux-gnu/libgsttag-1.0.so.0.2001.0
camera-st 9052         umdloop  mem       REG                0,9              8273 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8262 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG              259,1   476808 13908048 /usr/lib/aarch64-linux-gnu/libgstaudio-1.0.so.0.2001.0
camera-st 9052         umdloop  mem       REG                0,9              8238 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG              259,1   751848 13908064 /usr/lib/aarch64-linux-gnu/libgstvideo-1.0.so.0.2001.0
camera-st 9052         umdloop  mem       REG                0,9              8175 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG              259,1   509152 13920169 /usr/lib/aarch64-linux-gnu/libgstbase-1.0.so.0.2003.0
camera-st 9052         umdloop  mem       REG                0,9              8260 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8237 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG              259,1   104608 13916202 /usr/lib/aarch64-linux-gnu/libz.so.1.2.11
camera-st 9052         umdloop  mem       REG                0,9              8235 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8229 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8226 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG              259,1    34712 13917919 /usr/lib/aarch64-linux-gnu/libcap.so.2.44
camera-st 9052         umdloop  mem       REG                0,9              8232 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8225 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8215 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG              259,1   190368 13916281 /usr/lib/aarch64-linux-gnu/libuv.so.1.0.0
camera-st 9052         umdloop  mem       REG                0,9              8231 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG              259,1    59168 13908093 /usr/lib/aarch64-linux-gnu/libev.so.4.0.0
camera-st 9052         umdloop  mem       REG                0,9              8227 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG              259,1  4053144 13908021 /usr/lib/aarch64-linux-gnu/libcrypto.so.3
camera-st 9052         umdloop  mem       REG                0,9              8214 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8170 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG              259,1   630720 13908022 /usr/lib/aarch64-linux-gnu/libssl.so.3
camera-st 9052         umdloop  mem       REG                0,9              8196 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8195 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG              259,1   415632 13922208 /usr/lib/aarch64-linux-gnu/libpcre.so.3.13.3
camera-st 9052         umdloop  mem       REG                0,9              8212 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8193 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG              259,1    39272 13916332 /usr/lib/aarch64-linux-gnu/libffi.so.8.1.0
camera-st 9052         umdloop  mem       REG                0,9              8187 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8186 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG              259,1   667904 13916828 /usr/lib/aarch64-linux-gnu/libdw-0.186.so
camera-st 9052         umdloop  mem       REG                0,9              8184 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8172 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8168 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG              259,1    55560 13917507 /usr/lib/aarch64-linux-gnu/libunwind.so.8.0.1
camera-st 9052         umdloop  mem       REG                0,9              8190 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG              259,1   551064 13907531 /usr/lib/aarch64-linux-gnu/libm.so.6
camera-st 9052         umdloop  mem       REG                0,9              8189 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG              259,1    14328 13908811 /usr/lib/aarch64-linux-gnu/libgmodule-2.0.so.0.7200.4
camera-st 9052         umdloop  mem       REG                0,9              8185 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8171 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8167 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG              259,1  1990048 13908809 /usr/lib/aarch64-linux-gnu/libgio-2.0.so.0.7200.4
camera-st 9052         umdloop  mem       REG              259,1   263760 13908052 /usr/lib/aarch64-linux-gnu/libgstpbutils-1.0.so.0.2001.0
camera-st 9052         umdloop  mem       REG                0,9              8183 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8169 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8135 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8134 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8132 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8131 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8130 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8129 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8126 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8124 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG              259,1   192408 13908056 /usr/lib/aarch64-linux-gnu/libgstrtp-1.0.so.0.2001.0
camera-st 9052         umdloop  mem       REG                0,9              8127 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG              259,1  1661968 13907521 /usr/lib/aarch64-linux-gnu/libc.so.6
camera-st 9052         umdloop  mem       REG                0,9              8125 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG              259,1    84296 13922640 /usr/lib/aarch64-linux-gnu/libgcc_s.so.1
camera-st 9052         umdloop  mem       REG                0,9              8122 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8121 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8120 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8119 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8117 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8116 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8114 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG              259,1  2198944 13921553 /usr/lib/aarch64-linux-gnu/libstdc++.so.6.0.30
camera-st 9052         umdloop  mem       REG                0,9              8115 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8112 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8111 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG              259,1   391576 13908095 /usr/lib/aarch64-linux-gnu/libwebsockets.so.16
camera-st 9052         umdloop  mem       REG                0,9              8110 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8109 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8107 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              7988 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG              259,1  1294016 13908810 /usr/lib/aarch64-linux-gnu/libglib-2.0.so.0.7200.4
camera-st 9052         umdloop  mem       REG                0,9              8106 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8105 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG              259,1   405360 13908812 /usr/lib/aarch64-linux-gnu/libgobject-2.0.so.0.7200.4
camera-st 9052         umdloop  mem       REG                0,9              8104 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8101 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              7986 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG              259,1  1395528 13922692 /usr/lib/aarch64-linux-gnu/libgstreamer-1.0.so.0.2003.0
camera-st 9052         umdloop  mem       REG                0,9              8102 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8100 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG              259,1   101200 13908060 /usr/lib/aarch64-linux-gnu/libgstsdp-1.0.so.0.2001.0
camera-st 9052         umdloop  mem       REG                0,9              8099 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8093 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              7990 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG              259,1    55968 13922503 /usr/lib/aarch64-linux-gnu/libgstwebrtc-1.0.so.0.2003.0
camera-st 9052         umdloop  mem       REG                0,9              8094 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              7989 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              8092 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              7987 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       REG                0,9              7985 /dmabuf: (stat: No such file or directory)
camera-st 9052         umdloop  mem       CHR             505,14               253 /dev/nvgpu/igpu0/ctrl
camera-st 9052         umdloop  mem       REG              259,1    18728 13908044 /usr/lib/aarch64-linux-gnu/libgstallocators-1.0.so.0.2001.0
camera-st 9052         umdloop  mem       REG              259,1    27004 13907877 /usr/lib/aarch64-linux-gnu/gconv/gconv-modules.cache
camera-st 9052         umdloop  mem       REG              259,1   187776 13907514 /usr/lib/aarch64-linux-gnu/ld-linux-aarch64.so.1
camera-st 9052         umdloop    0u      CHR              136,1      0t0        4 /dev/pts/1
camera-st 9052         umdloop    1u      CHR              136,1      0t0        4 /dev/pts/1
camera-st 9052         umdloop    2u      CHR              136,1      0t0        4 /dev/pts/1
camera-st 9052         umdloop    3r      CHR                1,9      0t0       11 /dev/urandom
camera-st 9052         umdloop    4u  a_inode               0,13        0     7945 [eventfd]
camera-st 9052         umdloop    5u     unix 0xffff00008f5eaa80      0t0   228204 type=STREAM
camera-st 9052         umdloop    6u     unix 0xffff00008f5eea40      0t0   228205 type=STREAM
camera-st 9052         umdloop    7u     unix 0xffff00008f5eaec0      0t0   228206 type=STREAM
camera-st 9052         umdloop    8u     unix 0xffff0000d5930440      0t0   228207 type=STREAM
camera-st 9052         umdloop    9u     unix 0xffff00016170aec0      0t0   227082 type=STREAM
camera-st 9052         umdloop   10u  a_inode               0,13        0     7945 [eventfd]
camera-st 9052         umdloop   11u     unix 0xffff00016170cc80      0t0   227083 type=STREAM
camera-st 9052         umdloop   12u     IPv6             228209      0t0      TCP *:8081 (LISTEN)
camera-st 9052         umdloop   13u     IPv6             227091      0t0      TCP 192.168.88.90:8081->192.168.88.10:37512 (ESTABLISHED)
camera-st 9052         umdloop   14u      CHR             10,124      0t0      234 /dev/nvmap
camera-st 9052         umdloop   15u      CHR             505,14      0t0      253 /dev/nvgpu/igpu0/ctrl
camera-st 9052         umdloop   16u      CHR            226,128      0t0      325 /dev/dri/renderD128
camera-st 9052         umdloop   17u  a_inode               0,13        0     7945 nvhost-ga10b-fd17
camera-st 9052         umdloop   18u  a_inode               0,13        0     7945 nvhost-ga10b-fd18
camera-st 9052         umdloop   19u  a_inode               0,13        0     7945 [eventfd]
camera-st 9052         umdloop   20u      CHR            226,128      0t0      325 /dev/dri/renderD128
camera-st 9052         umdloop   21u  a_inode               0,13        0     7945 [eventfd]
camera-st 9052         umdloop   22u     unix 0xffff00016170ee80      0t0   227101 type=STREAM
camera-st 9052         umdloop   23u     unix 0xffff00016170b300      0t0   227102 type=STREAM
camera-st 9052         umdloop   24u  a_inode               0,13        0     7945 [eventfd]
camera-st 9052         umdloop   25u      CHR                1,3      0t0      478 /dev/v4l2-nvenc
camera-st 9052         umdloop   26u      CHR               81,0      0t0      635 /dev/video0
camera-st 9052         umdloop   27u      CHR               81,0      0t0      635 /dev/video0
camera-st 9052         umdloop   28u     unix 0xffff0000da602200      0t0   229660 type=STREAM
camera-st 9052         umdloop   29u     unix 0xffff0000da6050c0      0t0   229661 type=STREAM
camera-st 9052         umdloop   30u     unix 0xffff0000da606e80      0t0   229662 type=STREAM
camera-st 9052         umdloop   31u     unix 0xffff0000da602a80      0t0   229663 type=STREAM
camera-st 9052         umdloop   32u  a_inode               0,13        0     7945 [eventfd]
camera-st 9052         umdloop   33u     unix 0xffff00016170fb40      0t0   227105 type=STREAM
camera-st 9052         umdloop   34u     unix 0xffff000161709980      0t0   227106 type=STREAM
camera-st 9052         umdloop   35u  a_inode               0,13        0     7945 [eventfd]
camera-st 9052         umdloop   36u      CHR                1,3      0t0      478 /dev/v4l2-nvenc
camera-st 9052         umdloop   37u      CHR               81,6      0t0      665 /dev/video6
camera-st 9052         umdloop   38u      CHR             505,14      0t0      253 /dev/nvgpu/igpu0/ctrl
camera-st 9052         umdloop   39u      CHR            226,128      0t0      325 /dev/dri/renderD128
camera-st 9052         umdloop   40u  a_inode               0,13        0     7945 nvhost-ga10b-fd40
camera-st 9052         umdloop   41u     unix 0xffff0000d5934c80      0t0   228210 type=STREAM
camera-st 9052         umdloop   42u     unix 0xffff00008f5efb40      0t0   228211 type=STREAM
camera-st 9052         umdloop   43u     unix 0xffff00008f5e8880      0t0   228212 type=STREAM
camera-st 9052         umdloop   44u     unix 0xffff000085a62200      0t0   228213 type=STREAM
camera-st 9052         umdloop   45u     unix 0xffff000085a61540      0t0   228214 type=STREAM
camera-st 9052         umdloop   46u      CHR            226,128      0t0      325 /dev/dri/renderD128
camera-st 9052         umdloop   47u     unix 0xffff000085a65d80      0t0   228215 type=STREAM
camera-st 9052         umdloop   48u     0000                0,9   389120     7975 /dmabuf:
camera-st 9052         umdloop   49u     0000                0,9   389120     7976 /dmabuf:
camera-st 9052         umdloop   50u     0000                0,9   389120     7977 /dmabuf:
camera-st 9052         umdloop   51u     0000                0,9   389120     7978 /dmabuf:
camera-st 9052         umdloop   52u     0000                0,9   389120     7979 /dmabuf:
camera-st 9052         umdloop   53u     0000                0,9   389120     7980 /dmabuf:
camera-st 9052         umdloop   54u     unix 0xffff00016170bfc0      0t0   230421 type=STREAM
camera-st 9052         umdloop   55u     unix 0xffff00016170c400      0t0   230422 type=STREAM
camera-st 9052         umdloop   56u     unix 0xffff000085a6f2c0      0t0   228226 type=STREAM
camera-st 9052         umdloop   57u     unix 0xffff000085a6e600      0t0   228227 type=STREAM
camera-st 9052         umdloop   58u     unix 0xffff00008fbb6600      0t0   228228 type=STREAM
camera-st 9052         umdloop   59u     unix 0xffff0000b6fcea40      0t0   228229 type=STREAM
camera-st 9052         umdloop   60u  a_inode               0,13        0     7945 [eventfd]
camera-st 9052         umdloop   61u     unix 0xffff0000da603b80      0t0   229675 type=STREAM
camera-st 9052         umdloop   62u     unix 0xffff0000da603740      0t0   229676 type=STREAM
camera-st 9052         umdloop   63u  a_inode               0,13        0     7945 [eventfd]
camera-st 9052         umdloop   64u      CHR                1,3      0t0      478 /dev/v4l2-nvenc
camera-st 9052         umdloop   65u      CHR               81,4      0t0      661 /dev/video4
camera-st 9052         umdloop   66u     unix 0xffff0000da600cc0      0t0   229677 type=STREAM
camera-st 9052         umdloop   67u     unix 0xffff0000da601dc0      0t0   229678 type=STREAM
camera-st 9052         umdloop   68u     unix 0xffff0000da603300      0t0   229679 type=STREAM
camera-st 9052         umdloop   69u     unix 0xffff0000da607b40      0t0   229680 type=STREAM
camera-st 9052         umdloop   70u  a_inode               0,13        0     7945 [eventfd]
camera-st 9052         umdloop   71u  a_inode               0,13        0     7945 [eventfd]
camera-st 9052         umdloop   72u  a_inode               0,13        0     7945 [eventfd]
camera-st 9052         umdloop   73u  a_inode               0,13        0     7945 [eventfd]
camera-st 9052         umdloop   74u  a_inode               0,13        0     7945 [eventfd]
camera-st 9052         umdloop   75u     sock                0,8      0t0   228233 protocol: UDP
camera-st 9052         umdloop   76u  netlink                         0t0   228234 ROUTE
camera-st 9052         umdloop   77u     sock                0,8      0t0   228928 protocol: UDP
camera-st 9052         umdloop   78u  a_inode               0,13        0     7945 [eventfd]
camera-st 9052         umdloop   79u  netlink                         0t0   228929 ROUTE
camera-st 9052         umdloop   80u     IPv4             227108      0t0      UDP 127.0.0.1:1900 
camera-st 9052         umdloop   81u     IPv4             228237      0t0      UDP 192.168.88.90:60930 
camera-st 9052         umdloop   82u     IPv4             228932      0t0      UDP 192.168.88.90:52048 
camera-st 9052         umdloop   83u     IPv4             228240      0t0      TCP 192.168.88.90:59177 (LISTEN)
camera-st 9052         umdloop   84u     IPv4             227109      0t0      UDP 239.255.255.250:1900 
camera-st 9052         umdloop   85u     IPv4             229687      0t0      UDP 127.0.0.1:1900 
camera-st 9052         umdloop   86u     IPv4             227111      0t0      UDP 127.0.0.1:39502 
camera-st 9052         umdloop   87u     IPv4             229688      0t0      UDP 239.255.255.250:1900 
camera-st 9052         umdloop   88u     IPv4             228935      0t0      TCP 192.168.88.90:39505 (LISTEN)
camera-st 9052         umdloop   89u     IPv4             229690      0t0      UDP 127.0.0.1:35685 
camera-st 9052         umdloop   90u     IPv4             229692      0t0      UDP 192.168.88.90:1900 
camera-st 9052         umdloop   91u     IPv4             229693      0t0      UDP 239.255.255.250:1900 
camera-st 9052         umdloop   92u     IPv4             229695      0t0      UDP 192.168.88.90:35983 
camera-st 9052         umdloop   93u     IPv4             229702      0t0      UDP 239.255.255.250:1900 
camera-st 9052         umdloop   94u     IPv4             229701      0t0      UDP 192.168.88.90:1900 
camera-st 9052         umdloop   95u     IPv4             229704      0t0      UDP 192.168.88.90:34395 
camera-st 9052         umdloop   96u  a_inode               0,13        0     7945 [eventfd]
camera-st 9052         umdloop   97u  a_inode               0,13        0     7945 [eventfd]
camera-st 9052         umdloop   98u  a_inode               0,13        0     7945 [eventfd]
camera-st 9052         umdloop   99u  a_inode               0,13        0     7945 [eventfd]
camera-st 9052         umdloop  100u     sock                0,8      0t0   227119 protocol: UDP
camera-st 9052         umdloop  101u  netlink                         0t0   227120 ROUTE
camera-st 9052         umdloop  102u     unix 0xffff0000b6fce600      0t0   228241 type=STREAM
camera-st 9052         umdloop  103u     unix 0xffff0000b6fcb300      0t0   228242 type=STREAM
camera-st 9052         umdloop  104u     IPv4             227123      0t0      UDP 192.168.88.90:56560 
camera-st 9052         umdloop  105u     IPv4             228937      0t0      UDP 127.0.0.1:1900 
camera-st 9052         umdloop  106u     IPv4             228938      0t0      UDP 239.255.255.250:1900 
camera-st 9052         umdloop  107u     IPv4             228940      0t0      UDP 127.0.0.1:35837 
camera-st 9052         umdloop  108u     0000                0,9   655360     7981 /dmabuf:
camera-st 9052         umdloop  109u     IPv4             227126      0t0      TCP 192.168.88.90:34721 (LISTEN)
camera-st 9052         umdloop  110u     0000                0,9   655360     7982 /dmabuf:
camera-st 9052         umdloop  111u     0000                0,9   655360     7983 /dmabuf:
camera-st 9052         umdloop  112u     0000                0,9   655360     7984 /dmabuf:
camera-st 9052         umdloop  113u     IPv4             228944      0t0      UDP 192.168.88.90:1900 
camera-st 9052         umdloop  114u      CHR            226,128      0t0      325 /dev/dri/renderD128
camera-st 9052         umdloop  115u      CHR            226,128      0t0      325 /dev/dri/renderD128
camera-st 9052         umdloop  116u     IPv4             228947      0t0      UDP 192.168.88.90:45778 
camera-st 9052         umdloop  117u     IPv4             228945      0t0      UDP 239.255.255.250:1900 
camera-st 9052         umdloop  118u  a_inode               0,13        0     7945 [eventfd]
camera-st 9052         umdloop  119u  a_inode               0,13        0     7945 [eventfd]
camera-st 9052         umdloop  120u      CHR               81,2      0t0     1601 /dev/video2
camera-st 9052         umdloop  121u  a_inode               0,13        0     7945 nvgpu-ga10b-tsg121
camera-st 9052         umdloop  122u      CHR                1,3      0t0      478 /dev/v4l2-nvenc
camera-st 9052         umdloop  123u  a_inode               0,13        0     7945 nvhost-17000000.gpu-fd123
camera-st 9052         umdloop  124u  a_inode               0,13        0     7945 nvhost-17000000.gpu-fd124
camera-st 9052         umdloop  125u  a_inode               0,13        0     7945 nvhost-17000000.gpu-fd125
camera-st 9052         umdloop  126u  a_inode               0,13        0     7945 nvhost-17000000.gpu-fd126
camera-st 9052         umdloop  127u  a_inode               0,13        0     7945 nvhost-17000000.gpu-fd127
camera-st 9052         umdloop  128u  a_inode               0,13        0     7945 nvhost-17000000.gpu-fd128
camera-st 9052         umdloop  129u  a_inode               0,13        0     7945 nvhost-17000000.gpu-fd129
camera-st 9052         umdloop  130u  a_inode               0,13        0     7945 nvhost-17000000.gpu-fd130
camera-st 9052         umdloop  131u  a_inode               0,13        0     7945 nvhost-17000000.gpu-fd131
camera-st 9052         umdloop  132u  a_inode               0,13        0     7945 nvgpu-ga10b-tsg132
camera-st 9052         umdloop  133r  a_inode               0,13        0     7945 host1x_pollfd
camera-st 9052         umdloop  134u  a_inode               0,13        0     7945 nvhost-17000000.gpu-fd134
camera-st 9052         umdloop  135u     unix 0xffff0000da602ec0      0t0   229734 type=STREAM
camera-st 9052         umdloop  136u     unix 0xffff0000da6072c0      0t0   229735 type=STREAM
camera-st 9052         umdloop  137u     unix 0xffff0000da602640      0t0   229736 type=STREAM
camera-st 9052         umdloop  138u     unix 0xffff0000da604c80      0t0   229737 type=STREAM
camera-st 9052         umdloop  139u  a_inode               0,13        0     7945 nvhost-17000000.gpu-fd139
camera-st 9052         umdloop  140u  a_inode               0,13        0     7945 nvhost-17000000.gpu-fd140
camera-st 9052         umdloop  141u  a_inode               0,13        0     7945 nvhost-17000000.gpu-fd141
camera-st 9052         umdloop  142u  a_inode               0,13        0     7945 nvgpu-ga10b-tsg142
camera-st 9052         umdloop  143r  a_inode               0,13        0     7945 host1x_pollfd
camera-st 9052         umdloop  144u  a_inode               0,13        0     7945 nvhost-17000000.gpu-fd144
camera-st 9052         umdloop  145u  a_inode               0,13        0     7945 nvhost-17000000.gpu-fd145
camera-st 9052         umdloop  146u  a_inode               0,13        0     7945 nvhost-17000000.gpu-fd146
camera-st 9052         umdloop  147u  a_inode               0,13        0     7945 [eventfd]
camera-st 9052         umdloop  148r  a_inode               0,13        0     7945 host1x_pollfd
camera-st 9052         umdloop  149u     unix 0xffff0000da604840      0t0   229738 type=STREAM
camera-st 9052         umdloop  150u     unix 0xffff0000da606600      0t0   229739 type=STREAM
camera-st 9052         umdloop  151u      CHR            226,128      0t0      325 /dev/dri/renderD128
camera-st 9052         umdloop  152u     0000                0,9   884736     8155 /dmabuf:
camera-st 9052         umdloop  153u     0000                0,9   884736     8156 /dmabuf:
camera-st 9052         umdloop  154u     0000                0,9   884736     8157 /dmabuf:
camera-st 9052         umdloop  155u     0000                0,9   884736     8158 /dmabuf:
camera-st 9052         umdloop  156u     0000                0,9   884736     8159 /dmabuf:
camera-st 9052         umdloop  157u     0000                0,9   884736     8160 /dmabuf:
camera-st 9052         umdloop  158u     unix 0xffff0000da607700      0t0   229763 type=STREAM
camera-st 9052         umdloop  159u     unix 0xffff0000da605d80      0t0   229764 type=STREAM
camera-st 9052         umdloop  160u  a_inode               0,13        0     7945 nvgpu-event1-fd160
camera-st 9052         umdloop  161u  a_inode               0,13        0     7945 nvgpu-event4-fd161
camera-st 9052         umdloop  162u  a_inode               0,13        0     7945 nvgpu-event3-fd162
camera-st 9052         umdloop  163u  a_inode               0,13        0     7945 nvgpu-event0-fd163
camera-st 9052         umdloop  164r     FIFO               0,12      0t0   227294 pipe
camera-st 9052         umdloop  165w     FIFO               0,12      0t0   227294 pipe
camera-st 9052         umdloop  166u     0000                0,9   655360     8174 /dmabuf:
camera-st 9052         umdloop  167u      CHR            226,128      0t0      325 /dev/dri/renderD128
camera-st 9052         umdloop  168u      CHR            226,128      0t0      325 /dev/dri/renderD128
camera-st 9052         umdloop  169u     0000                0,9  1179648     8206 /dmabuf:
camera-st 9052         umdloop  170u      CHR            226,128      0t0      325 /dev/dri/renderD128
camera-st 9052         umdloop  171u      CHR            226,128      0t0      325 /dev/dri/renderD128
camera-st 9052         umdloop  172u      CHR            226,128      0t0      325 /dev/dri/renderD128
camera-st 9052         umdloop  173u      CHR            226,128      0t0      325 /dev/dri/renderD128
camera-st 9052         umdloop  174u     0000                0,9  1179648     8207 /dmabuf:
camera-st 9052         umdloop  175u     0000                0,9  1179648     8208 /dmabuf:
camera-st 9052         umdloop  176u     0000                0,9  1179648     8209 /dmabuf:
camera-st 9052         umdloop  177u     unix 0xffff0000b6fc8880      0t0   228272 type=STREAM
camera-st 9052         umdloop  178u      CHR            226,128      0t0      325 /dev/dri/renderD128
camera-st 9052         umdloop  179u      CHR            226,128      0t0      325 /dev/dri/renderD128
camera-st 9052         umdloop  180u      CHR            226,128      0t0      325 /dev/dri/renderD128
camera-st 9052         umdloop  181u      CHR            226,128      0t0      325 /dev/dri/renderD128
camera-st 9052         umdloop  182u      CHR            226,128      0t0      325 /dev/dri/renderD128
camera-st 9052         umdloop  183u     unix 0xffff0000b6fcd0c0      0t0   228273 type=STREAM
camera-st 9052         umdloop  184u     unix 0xffff0000b6fc8000      0t0   228274 type=STREAM
camera-st 9052         umdloop  185u     unix 0xffff0000b6fcc840      0t0   228275 type=STREAM
camera-st 9052         umdloop  186u  a_inode               0,13        0     7945 [eventfd]
camera-st 9052         umdloop  187u      CHR            226,128      0t0      325 /dev/dri/renderD128
camera-st 9052         umdloop  188u  a_inode               0,13        0     7945 [eventfd]
camera-st 9052         umdloop  189u  a_inode               0,13        0     7945 [eventfd]
camera-st 9052         umdloop  190u     sock                0,8      0t0   228282 protocol: UDP
camera-st 9052         umdloop  191u  netlink                         0t0   228283 ROUTE
camera-st 9052         umdloop  192u     IPv4             228972      0t0      UDP 127.0.0.1:1900 
camera-st 9052         umdloop  193u     IPv4             228286      0t0      UDP 192.168.88.90:46171 
camera-st 9052         umdloop  194u     IPv4             228289      0t0      TCP 192.168.88.90:34693 (LISTEN)
camera-st 9052         umdloop  195u     IPv4             228973      0t0      UDP 239.255.255.250:1900 
camera-st 9052         umdloop  196u     IPv4             228975      0t0      UDP 127.0.0.1:56002 
camera-st 9052         umdloop  197u     IPv4             228982      0t0      UDP 192.168.88.90:1900 
camera-st 9052         umdloop  198u     IPv4             228983      0t0      UDP 239.255.255.250:1900 
camera-st 9052         umdloop  199u     unix 0xffff00016170ea40      0t0   230417 type=STREAM
camera-st 9052         umdloop  200u     IPv4             228985      0t0      UDP 192.168.88.90:55383 
camera-st 9052         umdloop  201u     unix 0xffff0000da600880      0t0   229765 type=STREAM
camera-st 9052         umdloop  202u     unix 0xffff000161708440      0t0   230418 type=STREAM
camera-st 9052         umdloop  203u     unix 0xffff0000da606a40      0t0   229766 type=STREAM
camera-st 9052         umdloop  204u     unix 0xffff0000da601100      0t0   229767 type=STREAM
camera-st 9052         umdloop  205u      CHR            226,128      0t0      325 /dev/dri/renderD128
camera-st 9052         umdloop  206u     unix 0xffff0000da603fc0      0t0   229768 type=STREAM
camera-st 9052         umdloop  207u     0000                0,9   356352     8248 /dmabuf:
camera-st 9052         umdloop  208u     0000                0,9   356352     8249 /dmabuf:
camera-st 9052         umdloop  209u     0000                0,9   356352     8250 /dmabuf:
camera-st 9052         umdloop  210u     0000                0,9   356352     8251 /dmabuf:
camera-st 9052         umdloop  211u     0000                0,9   356352     8252 /dmabuf:
camera-st 9052         umdloop  212u     0000                0,9   356352     8253 /dmabuf:
camera-st 9052         umdloop  213u     unix 0xffff0000a0063b80      0t0   228333 type=STREAM
camera-st 9052         umdloop  214u     unix 0xffff0000a0061980      0t0   228334 type=STREAM
camera-st 9052         umdloop  215u     0000                0,9   655360     8254 /dmabuf:
camera-st 9052         umdloop  216u     0000                0,9   655360     8255 /dmabuf:
camera-st 9052         umdloop  217u     0000                0,9   655360     8256 /dmabuf:
camera-st 9052         umdloop  218u     0000                0,9   655360     8257 /dmabuf:
camera-st 9052         umdloop  219u     unix 0xffff0000da07f700      0t0   229015 type=STREAM
camera-st 9052         umdloop  220u      CHR            226,128      0t0      325 /dev/dri/renderD128
camera-st 9052         umdloop  221u      CHR            226,128      0t0      325 /dev/dri/renderD128
camera-st 9052         umdloop  222u      CHR            226,128      0t0      325 /dev/dri/renderD128
camera-st 9052         umdloop  223u      CHR            226,128      0t0      325 /dev/dri/renderD128
camera-st 9052         umdloop  224u      CHR            226,128      0t0      325 /dev/dri/renderD128
camera-st 9052         umdloop  225u      CHR            226,128      0t0      325 /dev/dri/renderD128
camera-st 9052         umdloop  226u     unix 0xffff0000da07f2c0      0t0   229016 type=STREAM
camera-st 9052         umdloop  227u     unix 0xffff0000ec64aa80      0t0   228335 type=STREAM
camera-st 9052         umdloop  228u     unix 0xffff0000ec64a640      0t0   228336 type=STREAM
camera-st 9052         umdloop  229u     unix 0xffff0000ec64b740      0t0   228337 type=STREAM
camera-st 9052         umdloop  230u      CHR            226,128      0t0      325 /dev/dri/renderD128
camera-st 9052         umdloop  231u     unix 0xffff0000ec64d940      0t0   228338 type=STREAM
camera-st 9052         umdloop  232u     0000                0,9   356352     8296 /dmabuf:
camera-st 9052         umdloop  233u     0000                0,9   356352     8297 /dmabuf:
camera-st 9052         umdloop  234u     0000                0,9   356352     8298 /dmabuf:
camera-st 9052         umdloop  235u     0000                0,9   356352     8299 /dmabuf:
camera-st 9052         umdloop  236u     0000                0,9   356352     8300 /dmabuf:
camera-st 9052         umdloop  237u     0000                0,9   356352     8301 /dmabuf:
camera-st 9052         umdloop  240u     0000                0,9   655360     8302 /dmabuf:
camera-st 9052         umdloop  241u     0000                0,9   655360     8303 /dmabuf:
camera-st 9052         umdloop  242u     0000                0,9   655360     8304 /dmabuf:
camera-st 9052         umdloop  243u     0000                0,9   655360     8305 /dmabuf:
camera-st 9052         umdloop  244u      CHR            226,128      0t0      325 /dev/dri/renderD128
camera-st 9052         umdloop  245u      CHR            226,128      0t0      325 /dev/dri/renderD128
camera-st 9052         umdloop  246u      CHR            226,128      0t0      325 /dev/dri/renderD128
camera-st 9052         umdloop  247u      CHR            226,128      0t0      325 /dev/dri/renderD128
camera-st 9052         umdloop  248u      CHR            226,128      0t0      325 /dev/dri/renderD128
camera-st 9052         umdloop  249u     unix 0xffff00016170a640      0t0   230494 type=STREAM
camera-st 9052         umdloop  250u      CHR            226,128      0t0      325 /dev/dri/renderD128
camera-st 9052         umdloop  251u     unix 0xffff00016170e600      0t0   230495 type=STREAM
```

## SDP candidates seen on WS (open GUI + view camera NOW; 20s window)
```
```

## ip route get GUI
```
192.168.88.10 dev enP8p1s0 src 192.168.88.90 uid 1000 
    cache 
```

## ip -4 addr
```
1: lo    inet 127.0.0.1/8 scope host lo\       valid_lft forever preferred_lft forever
3: enP8p1s0    inet 192.168.88.90/24 scope global enP8p1s0\       valid_lft forever preferred_lft forever
```
