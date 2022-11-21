if [ $# -eq 0 ]; then
  echo "no arguements"
  exit 1
fi

if [ $# -eq 0 ]; then
  echo "not enough arguements"
  exit 1
fi

filedir=$1
searchstr=$2

if ! [ -d "$filedir" ]; then
  echo "$filedir does not exist"
  exit 1
fi



numFiles=$(ls ${filedir}| wc -l)
numString=$(grep -wr ${searchstr} ${filedir} | wc -l)

echo "The number of files are ${numFiles} and the number of matching lines are ${numString}"



