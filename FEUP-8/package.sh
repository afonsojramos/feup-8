mkdir -p release
cd bin
cp tic80 libfeup8.so
cp ../assets/FEUP-8.desktop .
cp ../assets/conf.ini .
cp ../assets/readme.txt .
zip -r feup8_release.zip libfeup8.so FEUP-8.desktop conf.ini readme.txt
rm libfeup8.so
rm FEUP-8.desktop
rm conf.ini
rm readme.txt
mv feup8_release.zip ../release
