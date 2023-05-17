#!/bin/bash

TRUE_TEST=0
FALSE_TEST=0
FILE_1="file.txt"
FILE_2="bytes.txt"
FILE_3="bytes1.txt"
FILE_4="text.txt"
COMMAND_1="cat"
COMMAND_2="./s21_cat"
RES_1="cat_res.txt"
RES_2="s21_cat_res.txt"

# FLAG=(-b -e -n -s -t)

# 1 флаг
for flag in -b -e -n -s -t
do
    for file in $FILE_1 $FILE_2 $FILE_3 $FILE_4
    do
        TEST_1="$flag $file"
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

# 2 флага
for flag1 in -b -e -n -s -t
do
    for flag2 in -b -e -n -s -t
    do
        for file in $FILE_1 $FILE_2 $FILE_3 $FILE_4
        do
            TEST_1="$flag1 $flag2 $file"
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

# 3 флага
for flag1 in b e n s t
do
    for flag2 in b e n s t
    do
        for flag3 in b e n s t
        do
            if [ "$flag1" !=  "$flag2" ] && [ "$flag1" !=  "$flag3" ] && [ "$flag2" !=  "$flag3" ]
            then
                for file in $FILE_1 $FILE_2 $FILE_3 $FILE_4
                do
                    TEST_1="-$flag1$flag2$flag3 $file"
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
done

#Два флага, два файла
# for flag1 in -b -e -n -s -t
# do
#     for flag2 in -b -e -n -s -t
#     do
#         for file1 in $FILE_1 $FILE_2 $FILE_3 $FILE_4
#         do
#             for file2 in $FILE_1 $FILE_2 $FILE_3 $FILE_4
#             do
#                 TEST_1="$flag1 $flag2 $file1 $file2"
#                 echo "$TEST_1"
#                 $COMMAND_1 $TEST_1 > $RES_1
#                 $COMMAND_2 $TEST_1 > $RES_2
#                 DIFF=$(diff $RES_1 $RES_1) 
#                 if [ "$DIFF" = "" ] 
#                 then
#                     let "TRUE_TEST+=1"
#                 else
#                     echo "Error"
#                     let "FALSE_TEST+=1"
#                 fi
#             done
#         done
#     done
# done







rm $RES_1 $RES_2
echo "SUCCESFUL: $TRUE_TEST"
echo "FAILED: $FALSE_TEST"