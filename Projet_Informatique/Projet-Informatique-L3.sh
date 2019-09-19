nom=Projet-Informatique-L3
echo " "
echo $nom :
if test -d $nom
    then
        none=`ls`
    else
        git clone git@github.com:LicorneMagique/$nom.git
fi

if test `cat .gitignore | grep $nom | wc -l` = 0
    then
        echo $nom >> .gitignore
fi
