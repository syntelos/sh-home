
misc backups

 bin                   ${HOME}/bin

                       adds, mods, & orps work on svn and git on linux and windles/sh

 etc                   /etc/

 etc/init/ipnat.conf

                       Ubuntu upstart configuration, http://upstart.ubuntu.com/

 etc/network/ipnat

                       Simple NAT for linux kernel 3.2 (2.6+),
                       iproute2, and iptables.

                       Replacement for 'ip route add nat'.

                       Map an inside host address on one local
                       interface to a virtual ipaddr on another local
                       interface

                       Requires /etc/network/ipnat.conf
                         #
                         #in-ipaddr in-dev ex-ipaddr ex-dev
                         192.168.0.5 eth0 12.34.56.78 eth1
                         192.168.0.6 eth0 12.34.56.79 eth1
                         192.168.0.7 eth0 12.34.56.80 eth1
