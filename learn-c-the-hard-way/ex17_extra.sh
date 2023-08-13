#!/bin/bash
set -e

MAX_ROWS=10
MAX_DATA=255
DB_FILE="db.dat"
LINE="-------------------------------"

echo "Remove existing ex17_extra executable"
rm -rf ex17_extra
echo $LINE
echo

echo "Remove database $DB_FILE"
rm -rf $DB_FILE
echo $LINE
echo

echo "Create ex17_extra executable"
make ex17_extra
echo $LINE
echo

echo "Creating database $DB_FILE with max rows $MAX_ROWS and max data $MAX_DATA"
./ex17_extra $DB_FILE c $MAX_ROWS $MAX_DATA
echo $LINE
echo

# Store some dummy data
declare -a f_names=(Valentino Raven Stephani Rouvin Homere Matty Yorke Waldemar Abey Hector)
declare -a l_names=(Bunten Hildrew Rosenauer Allott Dukesbury Habert Pouton Gammack Foulks Allridge)
declare -a emails=(vbunten0@dropbox.com rhildrew1@netscape.com srosenauer2@salon.com rallott3@bloomberg.com hdukesbury4@elegantthemes.com mhabert5@w3.org ypouton6@hibu.com wgammack7@indiatimes.com afoulks8@cdbaby.com hallridge9@freewebs.com)
declare -a phones=(3165562522 2012228764 6819596900 8549089240 7819857355 4123237848 5845658163 9508560605 8205125908 2523814320)
declare -a heights=(179 196 127 133 162 132 171 145 166 128)
declare -a weights=(90 129 45 49 62 118 56 67 91 116)

echo "Add 10 records to the database:"
echo $LINE
for i in {0..9}
do
  id=$i
  fName=${f_names[$id]}
  lName=${l_names[$id]}
  email=${emails[$id]}
  phone=${phones[$id]}
  height=${heights[$id]}
  weight=${weights[$id]}

  echo "Adding $id $fName $lName $email $phone $height $weight"
  ./ex17_extra db.dat s $id $fName $lName $email $phone $height $weight;
done
echo $LINE
echo

echo "List out the records"
echo $LINE
./ex17_extra db.dat l
echo $LINE
echo

echo "Delete the record by id 5"
./ex17_extra db.dat d 5
echo $LINE
echo

echo "List out the records again"
echo $LINE
./ex17_extra db.dat l
echo $LINE
echo

echo "Get a records by id 7"
./ex17_extra db.dat g 7
echo $LINE
echo

echo "Find the first record by first_name"
./ex17_extra db.dat f f ${f_names[2]}
echo $LINE
echo

echo "Find the first record by last_name"
./ex17_extra db.dat f l ${l_names[3]}
echo $LINE
echo

echo "Find the first record by email"
./ex17_extra db.dat f e ${emails[7]}
echo $LINE
echo

echo "Find the first record by phone"
./ex17_extra db.dat f p ${phones[8]}
echo $LINE
echo

echo "Find the first record by height"
./ex17_extra db.dat f h ${heights[9]}
echo $LINE
echo

echo "Find the first record by weight"
./ex17_extra db.dat f w ${weights[0]}
echo $LINE
