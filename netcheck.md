# Offline network sanity
Generated: Sat May 16 12:08:03 AM EDT 2026

## rp_filter (look for any = 1 on enP8p1s0 or all)
```
/proc/sys/net/ipv4/conf/all/rp_filter = 2
/proc/sys/net/ipv4/conf/can0/rp_filter = 2
/proc/sys/net/ipv4/conf/can1/rp_filter = 2
/proc/sys/net/ipv4/conf/default/rp_filter = 2
/proc/sys/net/ipv4/conf/docker0/rp_filter = 2
/proc/sys/net/ipv4/conf/enP8p1s0/rp_filter = 2
/proc/sys/net/ipv4/conf/l4tbr0/rp_filter = 2
/proc/sys/net/ipv4/conf/lo/rp_filter = 2
/proc/sys/net/ipv4/conf/usb0/rp_filter = 2
/proc/sys/net/ipv4/conf/usb1/rp_filter = 2
/proc/sys/net/ipv4/conf/wlP1p1s0/rp_filter = 2
```

## iptables filter
```
Chain INPUT (policy ACCEPT 495K packets, 198M bytes)
 pkts bytes target     prot opt in     out     source               destination         

Chain FORWARD (policy ACCEPT 0 packets, 0 bytes)
 pkts bytes target     prot opt in     out     source               destination         
    0     0 DOCKER-USER  all  --  *      *       0.0.0.0/0            0.0.0.0/0           
    0     0 DOCKER-FORWARD  all  --  *      *       0.0.0.0/0            0.0.0.0/0           

Chain OUTPUT (policy ACCEPT 514K packets, 201M bytes)
 pkts bytes target     prot opt in     out     source               destination         

Chain DOCKER (1 references)
 pkts bytes target     prot opt in     out     source               destination         
    0     0 DROP       all  --  !docker0 docker0  0.0.0.0/0            0.0.0.0/0           

Chain DOCKER-BRIDGE (1 references)
 pkts bytes target     prot opt in     out     source               destination         
    0     0 DOCKER     all  --  *      docker0  0.0.0.0/0            0.0.0.0/0           

Chain DOCKER-CT (1 references)
 pkts bytes target     prot opt in     out     source               destination         
    0     0 ACCEPT     all  --  *      docker0  0.0.0.0/0            0.0.0.0/0            ctstate RELATED,ESTABLISHED

Chain DOCKER-FORWARD (1 references)
 pkts bytes target     prot opt in     out     source               destination         
    0     0 DOCKER-CT  all  --  *      *       0.0.0.0/0            0.0.0.0/0           
    0     0 DOCKER-INTERNAL  all  --  *      *       0.0.0.0/0            0.0.0.0/0           
    0     0 DOCKER-BRIDGE  all  --  *      *       0.0.0.0/0            0.0.0.0/0           
    0     0 ACCEPT     all  --  docker0 *       0.0.0.0/0            0.0.0.0/0           

Chain DOCKER-INTERNAL (1 references)
 pkts bytes target     prot opt in     out     source               destination         

Chain DOCKER-USER (1 references)
 pkts bytes target     prot opt in     out     source               destination         
```

## iptables nat
```
Chain PREROUTING (policy ACCEPT 5168 packets, 2100K bytes)
 pkts bytes target     prot opt in     out     source               destination         
 5152 2097K DOCKER     all  --  *      *       0.0.0.0/0            0.0.0.0/0            ADDRTYPE match dst-type LOCAL

Chain INPUT (policy ACCEPT 5168 packets, 2100K bytes)
 pkts bytes target     prot opt in     out     source               destination         

Chain OUTPUT (policy ACCEPT 46401 packets, 18M bytes)
 pkts bytes target     prot opt in     out     source               destination         
23228 9118K DOCKER     all  --  *      *       0.0.0.0/0           !127.0.0.0/8          ADDRTYPE match dst-type LOCAL

Chain POSTROUTING (policy ACCEPT 46401 packets, 18M bytes)
 pkts bytes target     prot opt in     out     source               destination         
    0     0 MASQUERADE  all  --  *      !docker0  172.17.0.0/16        0.0.0.0/0           

Chain DOCKER (2 references)
 pkts bytes target     prot opt in     out     source               destination         
```

## nftables
```
```

## ip rule
```
0:	from all lookup local
32766:	from all lookup main
32767:	from all lookup default
```

## ping GUI
```
PING 192.168.88.10 (192.168.88.10) 56(84) bytes of data.
64 bytes from 192.168.88.10: icmp_seq=1 ttl=64 time=0.629 ms
64 bytes from 192.168.88.10: icmp_seq=2 ttl=64 time=0.643 ms
64 bytes from 192.168.88.10: icmp_seq=3 ttl=64 time=0.884 ms

--- 192.168.88.10 ping statistics ---
3 packets transmitted, 3 received, 0% packet loss, time 2029ms
rtt min/avg/max/mdev = 0.629/0.718/0.884/0.117 ms
```

## ARP for GUI
```
192.168.88.10 dev enP8p1s0 lladdr 84:47:09:64:ac:04 REACHABLE
```
