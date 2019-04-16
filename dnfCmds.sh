#Display info about an installed/not installed package 
dnf info vim-enhanced 

#List packages (all available and installed)
dnf list   
#Just installed 
dnf list installed
#Just available
dnf list available

#Check for updates
dnf check-update

#Update a single package 
dnf update bash

#Update / upgrade all packages
dnf update 
dnf upgrade 

#Sync packages to current Fedora version
dnf distro-sync

#Download package 
dnf download vim

#Reinstall packages 
dnf reinstall vim

#==================== GROUPS ====================

#List all available groups
dnf grouplist

#Install group
dnf groupinstall "Development Tools"
dnf groupupdate "Development Tools"

#==================== REPOSITORIES ==============
dnf config-manager --add-repo repository_url
dnf config-manager --set-enabled <repo-id>
dnf repolist

#==================== RELATIONS =================

#Which package provides a specific bin or command
dnf provides *ifconfig
dnf provides /usr/bin/ls

#==================== HISTORY ==================
dnf history 
dnf history list ID
dnf history info ID

#Undo a transaction from history
dnf history undo ID

#Remove orphaned / unwanted packages
dnf autoremove

#Create cache for quicker transactions 
dnf makecache
#Remove all cache packages
dnf clean all 

