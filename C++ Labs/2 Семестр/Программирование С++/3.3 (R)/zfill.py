import pyautogui
import random
import time

# Примерный список ФИО (можно заменить на ваш)
full_names = [
    "John Ivanovich Smith", "Peter Petrovich Johnson", "Nikolai Sidorovich Kuznetsov",
    "Alexey Fedorovich Smirnov", "Fedor Sergeyevich Morozov", "Sergey Andreevich Solovyov",
    "Andrey Viktorovich Popov", "Victor Artemovich Lebedev", "Igor Denisovich Grigoryev",
    "Denis Vasilyevich Kovalev", "Vasily Romanovich Semenov", "Roman Dmitrievich Tikhonov",
    "Dmitry Alexeyevich Zaytsev", "Alexey Vladislavovich Kuzmin", "Vladislav Nikolayevich Sergeyev",
    "Nikolai Mikhailovich Sidorov", "Anna Ivanovna Sidorova", "Maria Petrovna Petrova",
    "Ekaterina Olegovna Ivanova", "Olga Viktorovna Smirnova", "Darya Nikolayevna Kuznetsova",
    "Victoria Sergeyevna Lebedeva", "Natalia Fedorovna Fedorova",
    "Maxim Alexandrovich Orlov", "Artem Sergeyevich Egorov", "Oleg Dmitrievich Novikov",
    "Yuri Ivanovich Frolov", "Leonid Petrovich Sokolov", "Viktor Alekseevich Makarov",
    "Semyon Vladimirovich Baranov", "Mikhail Andreevich Kolesnikov", "Igor Sergeyevich Tarasov",
    "Anastasia Ivanovna Volkova", "Svetlana Petrovna Morozova", "Elena Alexandrovna Semyonova",
    "Tatiana Viktorovna Nikitina", "Irina Dmitrievna Pavlova", "Marina Sergeyevna Fedorova",
    "Yulia Vladimirovna Sokolova", "Ekaterina Ivanovna Stepanova", "Daria Olegovna Kuzmina",
    "Olga Sergeyevna Ivanova", "Natalia Dmitrievna Popova", "Maria Andreevna Mikhailova",
    "Sofia Viktorovna Egorova", "Alina Petrovna Frolova", "Ksenia Alexandrovna Morozova",
    "Valentina Ivanovna Lebedeva", "Lyudmila Sergeyevna Baranova", "Nina Dmitrievna Tarasova"
]

# Функция для генерации случайных данных студентов
def generate_random_student_data():
    name = random.choice(full_names)
    gender = 'M' if 'ovich' in name else 'F'  # Определяем пол по окончанию отчества
    course = random.randint(1, 5)
    age = random.randint(18, 25)
    grade = round(random.uniform(2.0, 10.0), 1)  # Оценки от 2.0 до 10.0
    return name, gender, course, age, grade

# Функция для эмуляции ввода данных
def fill_student_data(num_students):

    pyautogui.hotkey('ctrl', 'tab')
    pyautogui.write("./better.out")
    pyautogui.press('enter')
    pyautogui.write(str(num_students))
    pyautogui.press('enter')



    for _ in range(num_students):  # Заполнение указанного количества студентов
        name, gender, course, age, grade = generate_random_student_data()

        # Ввод полного имени
        pyautogui.write(name)
        pyautogui.press('enter')

        # Ввод возраста
        pyautogui.write(str(age))
        pyautogui.press('enter')

        # Ввод курса
        pyautogui.write(str(course))
        pyautogui.press('enter')

        # Ввод пола
        pyautogui.write(gender)
        pyautogui.press('enter')

        # Ввод оценки
        pyautogui.write(str(grade))
        pyautogui.press('enter')

if __name__ == "__main__":
    while True:
        try:
            num_students = int(input("Введите количество студентов для генерации: ").strip())
            if num_students <= 0:
                print("Пожалуйста, введите положительное число.")
                continue
            break
        except ValueError:
            print("Ошибка: пожалуйста, введите корректное целое число.")

    fill_student_data(num_students)
