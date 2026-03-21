# DO NOT CHANGE THE NAMES OF THE FILE, CLASS or METHOD
class Students:
    def get_students_taking_at_least_one_course(self, students_courses,target_courses):
        total = set()

        for student, course in students_courses:
            if any(course == target for target in target_courses):
                total.add(student)

        return sorted(total)

