git pull
git add --all
echo Entrez le motif du commit :
read motif
git commit -a -m "$motif"
git push
echo Terminé.
