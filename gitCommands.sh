
#Stash changes into local db 
git stash save "NameOfTheStash"

#Unstash last stash 
git stash pop

#List the stack 
git stash list

#Unstash a specific stash
git stash pop "NameOfTheStash"

#pop commands is a combination of : 
#Apply last stash 
git stash apply
#Destroy last stash 
git stash drop 
