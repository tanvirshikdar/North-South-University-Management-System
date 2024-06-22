/**
 * @file university_management.h
 * @brief Header file for the North South University Management System
 *
 * This file contains the data structures and algorithms used for managing
 * the student, faculty, and course records in the university system.
 *
 * @version 1.6
 * @date 2024-06-15
 */

#ifndef UNIVERSITY_MANAGEMENT_H
#define UNIVERSITY_MANAGEMENT_H

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <memory>
#include <mutex>
#include <shared_mutex>
#include <stdexcept>

/**
 * @brief Structure to represent a student.
 */
struct Student {
    int student_id;        ///< Unique identifier for the student
    std::string name;      ///< Name of the student
    std::unordered_set<int> courses; ///< Set of course IDs the student is enrolled in
};

/**
 * @brief Structure to represent a faculty member.
 */
struct Faculty {
    int faculty_id;        ///< Unique identifier for the faculty member
    std::string name;      ///< Name of the faculty member
    std::unordered_set<int> courses; ///< Set of course IDs the faculty member is teaching
};

/**
 * @brief Structure to represent a course.
 */
struct Course {
    int course_id;         ///< Unique identifier for the course
    std::string name;      ///< Name of the course
    int faculty_id;        ///< Faculty member ID who teaches the course
    std::unordered_set<int> students; ///< Set of student IDs enrolled in the course
};

/**
 * @brief Class to manage student records.
 *
 * Uses std::unordered_map for efficient concurrent storage and retrieval of student records.
 * std::unordered_map provides average O(1) complexity for insertions, deletions, and look-ups.
 */
class StudentManager {
public:
    /**
     * @brief Add a new student to the system.
     * @param student_id The unique identifier for the student.
     * @param name The name of the student.
     */
    void addStudent(int student_id, const std::string &name);

    /**
     * @brief Enroll a student in a course.
     * @param student_id The unique identifier for the student.
     * @param course_id The unique identifier for the course.
     * @throws std::runtime_error if the course does not exist.
     */
    void enrollInCourse(int student_id, int course_id);

    /**
     * @brief Get the list of courses a student is enrolled in.
     * @param student_id The unique identifier for the student.
     * @return A set of course IDs.
     */
    std::unordered_set<int> getStudentCourses(int student_id) const;

private:
    std::unordered_map<int, std::shared_ptr<Student>> student_records; ///< Hash table for student records
    mutable std::shared_mutex mtx; ///< Shared mutex for thread safety
};

/**
 * @brief Class to manage faculty records.
 *
 * Uses std::unordered_map for efficient concurrent storage and retrieval of faculty records.
 * std::unordered_map provides average O(1) complexity for insertions, deletions, and look-ups.
 */
class FacultyManager {
public:
    /**
     * @brief Add a new faculty member to the system.
     * @param faculty_id The unique identifier for the faculty member.
     * @param name The name of the faculty member.
     */
    void addFaculty(int faculty_id, const std::string &name);

    /**
     * @brief Assign a faculty member to teach a course.
     * @param faculty_id The unique identifier for the faculty member.
     * @param course_id The unique identifier for the course.
     * @throws std::runtime_error if the course does not exist.
     */
    void assignCourse(int faculty_id, int course_id);

    /**
     * @brief Get the list of courses a faculty member is teaching.
     * @param faculty_id The unique identifier for the faculty member.
     * @return A set of course IDs.
     */
    std::unordered_set<int> getFacultyCourses(int faculty_id) const;

private:
    std::unordered_map<int, std::shared_ptr<Faculty>> faculty_records; ///< Hash table for faculty records
    mutable std::shared_mutex mtx; ///< Shared mutex for thread safety
};

/**
 * @brief Class to manage course records.
 *
 * Uses std::unordered_map for efficient concurrent storage and retrieval of course records.
 * std::unordered_map provides average O(1) complexity for insertions, deletions, and look-ups.
 */
class CourseManager {
public:
    /**
     * @brief Add a new course to the system.
     * @param course_id The unique identifier for the course.
     * @param name The name of the course.
     * @param faculty_id The unique identifier for the faculty member teaching the course.
     */
    void addCourse(int course_id, const std::string &name, int faculty_id);

    /**
     * @brief Enroll a student in a course.
     * @param course_id The unique identifier for the course.
     * @param student_id The unique identifier for the student.
     * @throws std::runtime_error if the student does not exist.
     */
    void enrollStudent(int course_id, int student_id);

    /**
     * @brief Get the list of students enrolled in a course.
     * @param course_id The unique identifier for the course.
     * @return A set of student IDs.
     */
    std::unordered_set<int> getCourseStudents(int course_id) const;

private:
    std::unordered_map<int, std::shared_ptr<Course>> course_records; ///< Hash table for course records
    mutable std::shared_mutex mtx; ///< Shared mutex for thread safety
};

/**
 * @brief Class to manage the entire university system.
 *
 * Provides an interface to manage students, faculty, and courses.
 */
class UniversityManager {
public:
    /**
     * @brief Add a new student to the system.
     * @param student_id The unique identifier for the student.
     * @param name The name of the student.
     */
    void addStudent(int student_id, const std::string &name);

    /**
     * @brief Enroll a student in a course.
     * @param student_id The unique identifier for the student.
     * @param course_id The unique identifier for the course.
     */
    void enrollInCourse(int student_id, int course_id);

    /**
     * @brief Get the list of courses a student is enrolled in.
     * @param student_id The unique identifier for the student.
     * @return A set of course IDs.
     */
    std::unordered_set<int> getStudentCourses(int student_id) const;

    /**
     * @brief Add a new faculty member to the system.
     * @param faculty_id The unique identifier for the faculty member.
     * @param name The name of the faculty member.
     */
    void addFaculty(int faculty_id, const std::string &name);

    /**
     * @brief Assign a faculty member to teach a course.
     * @param faculty_id The unique identifier for the faculty member.
     * @param course_id The unique identifier for the course.
     */
    void assignCourse(int faculty_id, int course_id);

    /**
     * @brief Get the list of courses a faculty member is teaching.
     * @param faculty_id The unique identifier for the faculty member.
     * @return A set of course IDs.
     */
    std::unordered_set<int> getFacultyCourses(int faculty_id) const;

    /**
     * @brief Add a new course to the system.
     * @param course_id The unique identifier for the course.
     * @param name The name of the course.
     * @param faculty_id The unique identifier for the faculty member teaching the course.
     */
    void addCourse(int course_id, const std::string &name, int faculty_id);

    /**
     * @brief Get the list of students enrolled in a course.
     * @param course_id The unique identifier for the course.
     * @return A set of student IDs.
     */
    std::unordered_set<int> getCourseStudents(int course_id) const;

private:
    StudentManager student_manager; ///< Manager for student records
    FacultyManager faculty_manager; ///< Manager for faculty records
    CourseManager course_manager;   ///< Manager for course records
};

#endif // UNIVERSITY_MANAGEMENT_H