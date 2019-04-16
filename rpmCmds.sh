
#Install rpm file 
rpm ‑i  gcc‑gfortran‑4.9.2‑6.fc21.x86_64.rpm

#Check which package owns a file 
rpm -qf `which vim` 
rpm -qf `locate file.so`

#Check dependencies of a file/package
rpm -qR packageName 
rpm -qR vim-enhanced

#List all installed packages 
rpm -qa 

#Remove package without dependencies 
rpm -e vim-enhanced --nodeps

#Update a package 
rpm -U packageName.rpm

#Display files in package 
rpm -ql "name of the package like in rpm -qa "

#Check which package provides a file 
rpm -q --whatprovides libxml2.so.2

#Check the integrity of a packages rpm 
rpm ‑vK vim‑enhanced‑7.4.475‑2.fc21.x86_64.rpm

#Download package to use it offline 
dnf download vim-enhanced

#Unpacking a rpm package 
pm2cpio ../gcc‑gfortran‑4.9.2‑6.fc21.x86_64.rpm | cpio ‑idvn


This should be the output :
./usr/lib/gcc
./usr/lib/gcc/x86_64‑redhat‑linux
./usr/lib/gcc/x86_64‑redhat‑linux/4.9.2
./usr/lib/gcc/x86_64‑redhat‑linux/4.9.2/32
./usr/lib/gcc/x86_64‑redhat‑linux/4.9.2/32/libcaf_single.a
