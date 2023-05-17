#!/bin/bash

TRUE_TEST=0
FALSE_TEST=0
FILE_1="f1.txt"
FILE_2="f2.txt"
FILE_3="f4.txt"
FILE_4="f5.txt"
TEMPLATE_1="A"
TEMPLATE_2="Myau"
COMMAND_1="grep"
COMMAND_2="./s21_grep"
RES_1="grep_res.txt"
RES_2="s21_grep_res.txt"

# 1 флаг, 1 слово, 1 файл
for flag in -i -v -c -l -n -h -s -o
do
    for file in $FILE_1 $FILE_2 $FILE_3
    do
        TEST_1="$flag $TEMPLATE_1 $file"
        echo "$TEST_1"
        $COMMAND_1 $TEST_1 > $RES_1
        $COMMAND_2 $TEST_1 > $RES_2
        DIFF=$(diff $RES_1 $RES_1) 
        if [ "$DIFF" = "" ] 
        then
            let "TRUE_TEST+=1"
        else
            echo "Error"
            let "FALSE_TEST+=1"
        fi
        
    done
done


# 1 флаг, 2 слова, 1 файл
for flag in -i -v -c -l -n -h -s -o
do
    for file in $FILE_1 $FILE_2 $FILE_3
    do
        TEST_1="$flag -e $TEMPLATE_1 $file -e $TEMPLATE_2"
        echo "$TEST_1"
        $COMMAND_1 $TEST_1 > $RES_1
        $COMMAND_2 $TEST_1 > $RES_2
        DIFF=$(diff $RES_1 $RES_1) 
        if [ "$DIFF" = "" ] 
        then
            let "TRUE_TEST+=1"
        else
            echo "Error"
            let "FALSE_TEST+=1"
        fi
        
    done
done


# 1 флаг, 2 слова, 2 файла
for flag in -i -v -c -l -n -h -s -o
do
    for file1 in $FILE_1 $FILE_2 $FILE_3
    do
        for file2 in $FILE_1 $FILE_2 $FILE_3
        do
            TEST_1="$flag -e $TEMPLATE_1 $file1 -e $TEMPLATE_2 $file2"
            echo "$TEST_1"
            $COMMAND_1 $TEST_1 > $RES_1
            $COMMAND_2 $TEST_1 > $RES_2
            DIFF=$(diff $RES_1 $RES_1) 
            if [ "$DIFF" = "" ] 
            then
                let "TRUE_TEST+=1"
            else
                echo "Error"
                let "FALSE_TEST+=1"
            fi
            
        done
    done
done


# 2 флага, 1 слово, 1 файл
for flag1 in -i -v -c -l -n -h -s -o
do
    for flag2 in -i -v -c -l -n -h -s -o
    do
        if [ "$flag1" !=  "$flag2" ]
        then
            for file in $FILE_1 $FILE_2 $FILE_3
            do
                TEST_1="$flag1 $TEMPLATE_1 $file $flag2"
                echo "$TEST_1"
                $COMMAND_1 $TEST_1 > $RES_1
                $COMMAND_2 $TEST_1 > $RES_2
                DIFF=$(diff $RES_1 $RES_1) 
                if [ "$DIFF" = "" ] 
                then
                    let "TRUE_TEST+=1"
                else
                    echo "Error"
                    let "FALSE_TEST+=1"
                fi
            done
        fi
    done
done


# 2 флага, 2 слова, 1 файл
for flag1 in -i -v -c -l -n -h -s -o
do
    for flag2 in -i -v -c -l -n -h -s -o
    do
        if [ "$flag1" !=  "$flag2" ]
        then
            for file in $FILE_1 $FILE_2 $FILE_3
            do
                TEST_1="$flag1 -e $TEMPLATE_1 $file -e $TEMPLATE_2  $flag2"
                echo "$TEST_1"
                $COMMAND_1 $TEST_1 > $RES_1
                $COMMAND_2 $TEST_1 > $RES_2
                DIFF=$(diff $RES_1 $RES_1) 
                if [ "$DIFF" = "" ] 
                then
                    let "TRUE_TEST+=1"
                else
                    echo "Error"
                    let "FALSE_TEST+=1"
                fi
            done
        fi
    done
done


# 2 флага, 2 слова, 2 файла
for flag1 in -i -v -c -l -n -h -s -o
do
    for flag2 in -i -v -c -l -n -h -s -o
    do
        if [ "$flag1" !=  "$flag2" ]
        then
            TEST_1="$flag1 -e $TEMPLATE_1 $FILE_2 $FILE_3 -e $TEMPLATE_2  $flag2"
            echo "$TEST_1"
            $COMMAND_1 $TEST_1 > $RES_1
            $COMMAND_2 $TEST_1 > $RES_2
            DIFF=$(diff $RES_1 $RES_1) 
            if [ "$DIFF" = "" ] 
            then
                let "TRUE_TEST+=1"
            else
                echo "Error"
                let "FALSE_TEST+=1"
            fi
        fi
    done
done


for flag1 in i v c l n h s o
do
    for flag2 in i v c l n h s o
    do
        if [ "$flag1" !=  "$flag2" ]
        then
            TEST_1="-$flag1$flag2 -e $TEMPLATE_1 $FILE_1 $FILE_3 -e $TEMPLATE_2"
            echo "$TEST_1"
            $COMMAND_1 $TEST_1 > $RES_1
            $COMMAND_2 $TEST_1 > $RES_2
            DIFF=$(diff $RES_1 $RES_1) 
            if [ "$DIFF" = "" ] 
            then
                let "TRUE_TEST+=1"
            else
                echo "Error"
                let "FALSE_TEST+=1"
            fi
        fi
    done
done

# -o + 1 флаг, 1 слово, 2 файла
for flag in -i -v -c -l -n -h -s
do
    for file in $FILE_1 $FILE_2 $FILE_3
    do
        TEST_1="$flag Cat -o $file $FILE_4"
        echo "$TEST_1"
        $COMMAND_1 $TEST_1 > $RES_1
        $COMMAND_2 $TEST_1 > $RES_2
        DIFF=$(diff $RES_1 $RES_1) 
        if [ "$DIFF" = "" ] 
        then
            let "TRUE_TEST+=1"
        else
            echo "Error"
            let "FALSE_TEST+=1"
        fi
        
    done
done


rm $RES_1 $RES_2
echo "SUCCESFUL: $TRUE_TEST"
echo "FAILED: $FALSE_TEST"