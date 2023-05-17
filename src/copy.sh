#!/bin/bash

scp /home/gitlab-runner/builds/KyrbPE9y/0/students/DO6_CICD.ID_356283/swindell_student.21_school.ru/DO6_CICD-0/src/cat/s21_cat swindell@10.10.0.20:/usr/local/bin/
scp /home/gitlab-runner/builds/KyrbPE9y/0/students/DO6_CICD.ID_356283/swindell_student.21_school.ru/DO6_CICD-0/src/grep/s21_grep swindell@10.10.0.20:/usr/local/bin/
ssh swindell@10.10.0.20 ls -lah /usr/local/bin
