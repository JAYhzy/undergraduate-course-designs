package com.wyh;

import com.wyh.score.ScoreSystem;
import com.wyh.score.Student;

import java.util.ArrayList;
import java.util.List;

public class Instance {
    public final static List<Student> students = new ArrayList<>();//项目的运行所需的初始学生

    static {
        students.add(new Student("stu1"));
        students.add(new Student("stu2"));
        students.add(new Student("stu3"));
        students.add(new Student("stu4"));
        students.add(new Student("stu5"));
        students.add(new Student("stu6"));
        students.add(new Student("stu7"));
        students.add(new Student("stu8"));
        students.add(new Student("stu9"));
        students.add(new Student("stu0"));
    }

    public static void main(String[] args) {
        ScoreSystem system = new ScoreSystem();
        while (true) {
            system.printUI();
            switch (system.KeyChoose()) {
                case 1 -> system.FindFailingScore();
                case 2 -> system.DiscreteMathAverage();
                case 3 -> system.StudentAverage();
                case 4 -> system.AverageFailingCourse();
                default -> System.out.println("input error!");
            }
        }
    }
}
