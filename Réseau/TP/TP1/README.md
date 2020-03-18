# TP1

```shell
# Configuration
ip link set up dev eth0
ip address add 192.0.0.2/24 dev eth0

# Vérification
mii-tool
```

Permettre de ping le broadcast
```shell
/proc/sys/met/ipv4/
```

```mii-tool``` donne les infos sur les connexions  
Switch -> FD  
Hub -> HD

```ip route``` donne la carte de rootage

Modification du fichier /etc/hosts

> 192.0.0.1 bernard
> 192.0.0.3 josezfine

```ip  route  get  <adresse>``` pour  savoir  quelle  interface  est utilisée

