mkdir -p release
cd bin
cp tic80 libfeup8.so
cp ../docs/FEUP-8.desktop .
zip -r feup8_release.zip libfeup8.so FEUP-8.desktop
rm libfeup8.so
rm FEUP-8.desktop
mv feup8_release.zip ../release
