# TP6

```shell
sudo adduser lurong
whoami
su lurong
whoami
exit
cat /etc/passwd
cat /etc/passwd | grep lurong
sudo cat /etc/shadow
cat /etc/passwd | grep lurong | cut -d : -f 3
cat /etc/passwd | grep lurong | cut -d : -f 4
su lurong
TOTO=tutu
echo "$TOTO"
TOTO = tutu
bash
echo "$TOTO"
exit
echo "$TOTO"
export TOTO
bash
echo "$TOTO"
exit
env
env | grep TOTO
echo $PATH
PATH="$HOME"/test1:"$PATH":"$HOME"/test2
echo $PATH
cd ../lurong/
mkdir test1 test2
echo '#!/bin/sh' > test1/less
echo 'echo "Je suis test1"' >> test1/less
echo '#!/bin/sh' > test2/less
echo 'echo "Je suis test2"' >> test1/less
command -v less
chmod +x "$HOME"/test1/less "$HOME"/test2/less
command -v less
less
```

> ça marche plus

```shell
su lurong
mv .bashrc .bashrc.save
mv .profile .profile.save
echo 'echo "chargement de .bashrc"' > .bashrc
echo 'echo "chargement de .profile"' > .profile
ssh lurong@localhost
```

> c'est le .profile

```shell
bash
```

> c'est le .bashrc

```shell
ssh lurong@localhost
```

> ça charge .profile et .bashrc

```shell
bash
```

> ça charge .bashrc

```shell
mv test1/less bin/
ssh lurong@localhost
less
```

> ça exécute test1/less

```shell
PS1="Bonjour maitre, que dois-je faire ? "
PS1="\h:\w\\\$ "
PS1="\[\e[31m\]rouge\[\e[m\] \[\e[32m\]vert\[\e[m\] "
PS1="\[\033]0;\u@\h:\w\007\]\[\033[01;32m\]\u@\h\[\033[01;34m\] \w \$\[\033[00m\] "
echo 'export PS1="\[\033]0;\u@\h:\w\007\]\[\033[01;32m\]\u@\h\[\033[01;34m\] \w \$\[\033[00m\] "' > .bashrc
git com[TAB] --ame[TAB]
alias
1
```

> 1 : commande introuvable

```shell
l
```

> l : commande introuvable

```shell
alias l="ls -l --color=auto"
l
```

> total 24  
drwxrwxr-x 2 lurong lurong 4096 mars  24 11:07 bin  
-rw-r--r-- 1 lurong lurong 8980 mars  24 09:57 examples.desktop  
drwxrwxr-x 2 lurong lurong 4096 mars  24 11:07 test1  
drwxrwxr-x 2 lurong lurong 4096 mars  24 10:34 test2  

```shell
alias
```

> alias l='ls -l --color=auto'

```shell
whoami
whoami
pwd
pwd
ls -l poi
nano poi
ls ../julien/poi -l
nano ../julien/poi
```

> ça marche pas

```shell
chmod go+w poi
nano ../julien/poi
```

> là ça a marché pas

```shell
chmod go-w poi
ls ../julien/poi -l
chmod go-r
chmod 644
chmod go+rw poi.
users
apt list --installed | grep installé | wc -l
sudo apt update
sudo apt full-upgrade
apt list --installed | grep nginx | wc -l
apt search nginx | grep nginx/
```

> nginx/bionic-updates,bionic-updates,bionic-security,bionic-security **1.14.0**-0ubuntu1.7 all

```shell
sudo apt install nginx
ls /etc/nginx/
ls /var/log/nginx/
```
