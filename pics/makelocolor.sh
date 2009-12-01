 #!/bin/bash

HERE=`pwd`

rm ${HERE}/locolor/*.png

cd ${HERE}/hicolor

for FILE in `ls *.png`
do
	NEWNAME=`echo $FILE | sed -e 's/hi/lo/g'`
	convert ${FILE} -colors 256 ${HERE}/locolor/${NEWNAME}
done