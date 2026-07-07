package com.wyh.score;

import java.util.HashMap;
import java.util.Map;
import java.util.Random;

public class Student {
    private final String name;
    private final Map<String,Integer> courses = new HashMap<>();//存放课程信息

    public Student(String name) {
        this.name = name;
        //在创建学生实例的同时，随机初始化了该学生的课程信息
        courses.put("Discrete Math",new Random().nextInt(50) + 51);
        courses.put("System Programming",new Random().nextInt(50) + 51);
        courses.put("English",new Random().nextInt(50) + 51);
        courses.put("Data Structure",new Random().nextInt(50) + 51);
        courses.put("Computer NetWork",new Random().nextInt(50) + 51);
        courses.put("Arts",new Random().nextInt(50) + 51);
    }

    public String getName() {
        return name;
    }

    public Map<String,Integer> getCourses() {
        return courses;
    }
}
