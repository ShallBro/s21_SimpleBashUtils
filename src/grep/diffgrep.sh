filename1=test.txt;
filename2=grep.c;
filename3=test1.txt;
echo ----------------------------------------------*GREP 1
diff <(grep int "$filename2" "$filename1") <(./s21_grep int "$filename2" "$filename1") -s -q
echo ----------------------------------------------*GREP 2
diff <(grep -e int "$filename2" "$filename1") <(./s21_grep -e int "$filename2" "$filename1") -s -q
echo ----------------------------------------------*GREP 3
diff <(grep -i int "$filename1") <(./s21_grep -i int "$filename1") -s -q
echo ----------------------------------------------*GREP 4
diff <(grep -v int "$filename1") <(./s21_grep -v int "$filename1") -s -q
echo ----------------------------------------------*GREP 5
diff <(grep -c int "$filename1") <(./s21_grep -c int "$filename1") -s -q
echo ----------------------------------------------*GREP 6
diff <(grep -l int "$filename2" "$filename3" "$filename1") <(./s21_grep -l int "$filename2" "$filename3" "$filename1") -s -q
echo ----------------------------------------------*GREP 7
diff <(grep -n int "$filename1") <(./s21_grep -n int "$filename1") -s -q
echo ----------------------------------------------*TEST ENDED