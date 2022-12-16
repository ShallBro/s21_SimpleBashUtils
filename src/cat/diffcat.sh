filename=test_1_cat.txt;
filename1=test_2_cat.txt; # this is binary file
echo ----------------------------------------------*CAT 1
diff <(cat -b "$filename") <(./s21_cat -b "$filename") -s
echo ----------------------------------------------*CAT 2
diff <(cat -e "$filename") <(./s21_cat -e "$filename") -s
echo ----------------------------------------------*CAT 3
diff <(cat -n "$filename") <(./s21_cat -n "$filename") -s
echo ----------------------------------------------*CAT 4
diff <(cat "$filename" -n) <(./s21_cat "$filename" -n) -s
echo ----------------------------------------------*CAT 5
diff <(cat -s "$filename") <(./s21_cat -s "$filename") -s
echo ----------------------------------------------*CAT 6
diff <(cat -t "$filename") <(./s21_cat -t "$filename") -s
echo ----------------------------------------------*CAT 7
diff <(cat "$filename") <(./s21_cat "$filename") -s
echo ----------------*BINARY TESTS*----------------------
echo ----------------------------------------------*CAT 8
diff <(cat -v "$filename1") <(./s21_cat -v "$filename1") -s
echo ----------------------------------------------*CAT 9
diff <(cat -e "$filename1") <(./s21_cat -e "$filename1") -s
echo ----------------------------------------------*CAT 10
diff <(cat -t "$filename1") <(./s21_cat -t "$filename1") -s
echo -----------------*TESTS ENDED*-----------------------