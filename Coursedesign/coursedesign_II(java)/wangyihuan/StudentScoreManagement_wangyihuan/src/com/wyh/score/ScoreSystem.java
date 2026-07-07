package com.wyh.score;

import com.wyh.Instance;

import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class ScoreSystem {
    private static final Map<String,Map<String,Integer>> FailedStudents = new HashMap<>();//过滤不及格学生及其不及格的课程

    static {
        for (Student student : Instance.students) {
            Map<String, Integer> courses = student.getCourses();
            for (Map.Entry<String, Integer> course : courses.entrySet()) {
                if (course.getValue() < 60) {
                    if (FailedStudents.containsKey(student.getName())) {
                        FailedStudents.get(student.getName()).put(course.getKey(), course.getValue());
                    } else {
                        HashMap<String, Integer> FailedCourseMap = new HashMap<>();
                        FailedCourseMap.put(course.getKey(), course.getValue());
                        FailedStudents.put(student.getName(), FailedCourseMap);
                    }
                }
            }
        }
    }

    public void printUI() {
        System.out.println("  Student Score Management ");
        System.out.println("============================");
        System.out.println("| 1.Enquire Failed Student |");
        System.out.println("| 2.Discrete Math Average  |");
        System.out.println("| 3.Student Average        |");
        System.out.println("| 4.Average Failing Course |");
        System.out.println("============================");
    }

    public int KeyChoose() {
        Scanner scanner = new Scanner(System.in);
        return scanner.nextInt();
    }

    public void FindFailingScore() {
        System.out.println("----------------");
        System.out.println("|Failed Student|");
        System.out.println("----------------");
        System.out.println("------------------------------------");
        for (Map.Entry<String, Map<String,Integer>> student : FailedStudents.entrySet()) {
            System.out.println("|name: "+student.getKey());
            for (Map.Entry<String,Integer> course : student.getValue().entrySet()) {
                System.out.println("|course:"+course.getKey()+" score: "+course.getValue());
            }
            System.out.println("------------------------------------");
        }
        System.out.println();
    }

    public void DiscreteMathAverage() {
        int totalScore = 0;
        for (Student student : Instance.students) {
            Map<String, Integer> courses = student.getCourses();
            Integer discreteMathScore = courses.get("Discrete Math");
            totalScore += discreteMathScore;
        }
        if (totalScore != 0) {
            System.out.println("---------------------------");
            System.out.println("|Discrete Math Average: "+totalScore/Instance.students.size()+"|");
            System.out.println("---------------------------");
        }
        System.out.println();
    }

    public void StudentAverage() {
        System.out.println("-----------------");
        System.out.println("|Student Average|");
        System.out.println("-----------------");
        for (Student student : Instance.students) {
            int PersonalTotalScores = 0;
            Map<String, Integer> courses = student.getCourses();
            for (Map.Entry<String, Integer> course : courses.entrySet()) {
                Integer courseScore = course.getValue();
                PersonalTotalScores += courseScore;
            }
            if (PersonalTotalScores != 0) {
                System.out.println("--------------------");
                System.out.println("|"+student.getName()+"'s Average: "+PersonalTotalScores/courses.size()+"|");
                System.out.println("--------------------");
            }
        }
        System.out.println();
    }

    public void AverageFailingCourse() {
        int totalFailedCourseNum = 0;
        for (Map.Entry<String, Map<String,Integer>> student : FailedStudents.entrySet()) {
            int FailedCourseSize = student.getValue().entrySet().size();
            totalFailedCourseNum += FailedCourseSize;
        }
        if (totalFailedCourseNum != 0) {
            System.out.println("---------------------------");
            System.out.println("|Average Failing Course: "+totalFailedCourseNum/FailedStudents.size()+"|");
            System.out.println("---------------------------");
        }
        System.out.println();
    }
}
