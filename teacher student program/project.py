import re
import sys
import csv


def main():
    while True:
        option1 = input("hello and welcome choose what do you want to do:\n1-log in\n2-create a new account\n3-leave\nenter a number:")
        if option1 =="1" or option1 =="2" or option1 =="3":
            break
    choice(option1)


def choice(option):
    if option == "1":
        user = {}
        while True:
            account = input("\033[1m"+ "\033[91m" + "enter your account or you can exit by typing exit\n" + "\033[0m" +"account: ")
            if account == "exit":
                sys.exit("goodbye have a nice day")
            password = input("password: ")
            if (user:=check_user(account,password)) != "user does not exist":
                break
            print("\033[91m" + "wrong account or password" + "\033[0m")
        print("\033[1m" + f"\nwelcome back {user['username']}" + "\033[0m")
        choice2(user)

    elif option == "2":
        category = ""
        user = {"account":"", "password":"", "username":"", "category":""}
        while True:
            account = input("\033[1m"+ "\033[91m" + "enter your account or you can exit by typing exit\n" + "\033[0m" + "account: ")
            if account == "exit":
                sys.exit("goodbye have a nice day")
            if (category := check_account(account)) != "unsupported account" and check_infos(account, 0) != "unavailable":
                break
            if check_account(account) == "unsupported account":
                print("\033[91m" + "this program does not support your account" + "\033[0m")
            elif check_infos(account, 0) == "unavailable":
                print("\033[91m" + "this account is already used" + "\033[0m")
        user["account"] = account
        user["category"] = category
        while True:
            password = input("\033[1m" + "your password must contain letters and at least 3 numbers\nits length must be at least 9\n" + "\033[0m" + "password: ")
            if check_password(password) != "unavailable password":
                user["password"] = password
                break
            print("\033[91m" + "this password is unavailable try another one" + "\033[0m")
        while True:
            username = input("username: ").lower()
            if check_infos(username, 2) != "unavailable":
                user["username"] = username
                break
            print("\033[91m" + "this username is unavailable try another one" + "\033[0m")

        addUser(user)
        print(f"\nwelcome {user['username']}")
        choice2(user)

    else:
        sys.exit("goodbye have a nice day")



def check_user(account, password):
    try:
        with open("users.csv","r") as file:
            reader = csv.reader(file)
            for email, passwordd, username, category in reader:
                if email == account and passwordd == password:
                    return {"account":email,"password":passwordd,"username":username,"category":category}
            return "user does not exist"

    except FileNotFoundError:
        return "user does not exist"


def check_account(account):
    if re.search(r"^(\w){5,}@teacher.edu$",account):
        return "teacher"

    elif re.search(r"^(\w){5,}@student.edu$",account):
        return "student"

    else:
        return "unsupported account"


def choice2(user):
    if user["category"] == "teacher":
        while True:
            option = input("what do you want to do:\n1-make a quiz\n2-leave\nenter a number:")
            if option == "1":
                print("\033[91m" + "\033[1m" + "enter 3 questions from these patterns (x+y OR x-y OR x*y OR x/y) you can write spaces between the numbers and the mathmetical signs" + "\033[0m")
                questions = {"question 1":"", "question 2":"", "question 3":""}
                for i in range(3):
                    while True:
                        question = input(f"question {i+1}: ")
                        if check_question(question) != "wrong question":
                            questions[f"question {i+1}"] = question
                            break
                        print("\033[91m" + "unsupported question" + "\033[0m")

                save_questions(questions)
                print()
            elif option == "2":
                sys.exit("goodbye have a nice day")

    elif user["category"] == "student":
        while True:
            option = input("what do you want to do:\n1-solve a quiz\n2-leave\nenter a number:")
            if option == "1":
                quizNumbers = count_quizzes()
                print(f"\nWe have {quizNumbers} quizzes choose which one do you want to solve")
                quiz = {}
                while True:
                    number = input("quiz number: ")
                    if (quiz := find_quiz(number)) != {}:
                        break
                    print("\033[91m" + f"it not a number in the quizzes range from (1-{quizNumbers})" + "\033[0m")
                right_answers = 0
                quiz["question 3"] = quiz["question 3"].rstrip("\n")
                student_answers = {"answer 1":"","answer 2":"","answer 3":""}
                actual_answers = {"answer 1":"","answer 2":"","answer 3":""}
                for i in range(3):
                    result = check_question(quiz[f"question {i+1}"])
                    answer = input(f"{quiz[f'question {i+1}']} = ")
                    student_answers[f"answer {i+1}"] = answer
                    actual_answers[f"answer {i+1}"] = result
                    try:
                        if result == int(answer):
                            right_answers+=1
                    except ValueError:
                        continue
                print("your mark is: " + "\033[1m" + f"{int((right_answers/3)*100)}%" + "\033[0m")
                while True:
                    checking = input("do you want too see the actual answers and your answers(yes/no)?")
                    if checking == "no":
                        break
                    elif checking == "yes":
                        with open("result.txt", "w") as file:
                            file.write(f"question 1: {quiz['question 1']}\nyour answer: {student_answers['answer 1']}\nthe acual answer: {actual_answers['answer 1']}\n")
                            file.write(f"question 2: {quiz['question 2']}\nyour answer: {student_answers['answer 2']}\nthe acual answer: {actual_answers['answer 2']}\n")
                            file.write(f"question 3: {quiz['question 3']}\nyour answer: {student_answers['answer 3']}\nthe acual answer: {actual_answers['answer 3']}\n")
                            print("you can see it in the file called result.txt")
                            break
                    else:
                        print("\033[91m" + "the answer is (yes) or (no)!!" + "\033[0m")
                print()
            elif option == "2":
                sys.exit("goodbye have a nice day")


def check_infos(username, index):
    try:
        with open("users.csv", "r") as file:
            for line in file:
                if line != "":
                    user = line.rstrip().split(",")
                    if username == user[index]:
                        return "unavailable" 
        return "available"
    except FileNotFoundError:
        return "available" 
        

def check_password(password):
    numbers = [num for num in range(10)]
    small_letters = [chr(i) for i in range(97, 123)]    
    capital_letters = [chr(i) for i in range(65, 91)]
    numbersCounter = 0
    if len(password)<=8:
        return "unavailable password"
    for char in password:
        try:
            int(char)
        except ValueError:
            if char not in small_letters and char not in capital_letters:
                return "unavailable password"

    for char in password:
        try:
            if int(char) in numbers:
                numbersCounter +=1 
        except ValueError:
            continue
    
    if numbersCounter < 3:
        return "unavailable password"
    return "available password" 


def addUser(user):
    with open("users.csv", "a", newline="") as file:
        writer = csv.DictWriter(file, fieldnames=["account","password","username","category"])
        writer.writerow({"account":user["account"],"password": user["password"],"username": user["username"],"category": user["category"]})


def check_question(question):
    first = ""
    second = ""
    try:
        first, second = question.split("+")
        return int(first.strip()) + int(second.strip()) 
    except ValueError:
        try:
            first, second = question.split("*")
            return int(first.strip()) * int(second.strip()) 
        except ValueError:
            try:
                first, second = question.split("-")
                return int(first.strip()) - int(second.strip()) 
            except ValueError:
                try:
                    first, second = question.split("/")
                    return int(first.strip()) / int(second.strip()) 
                except (ValueError, ZeroDivisionError):
                    return "wrong question"
                

def save_questions(questions):
    list = []
    for i in range(3):
        if "+" in questions[f"question {i+1}"]:
            list = questions[f"question {i+1}"].split("+")
            questions[f"question {i+1}"] = list[0].strip() + " + " + list[1].strip()
        elif "-" in questions[f"question {i+1}"]:
            list = questions[f"question {i+1}"].split("-")
            questions[f"question {i+1}"] = list[0].strip() + " - " + list[1].strip()
        elif "/" in questions[f"question {i+1}"]:
            list = questions[f"question {i+1}"].split("/")
            questions[f"question {i+1}"] = list[0].strip()+" / "+list[1].strip()
        elif "*" in questions[f"question {i+1}"]:
            list = questions[f"question {i+1}"].split("*")
            questions[f"question {i+1}"] = list[0].strip()+" * "+list[1].strip()
    with open("quizzes.csv", "a", newline="") as file:
        writer = csv.DictWriter(file, fieldnames=["question 1","question 2","question 3"])
        writer.writerow({"question 1":questions["question 1"],"question 2": questions["question 2"],"question 3":questions["question 3"]})


def count_quizzes():
    with open("quizzes.csv","r") as file:
        counter = 0
        for _ in file:
            counter+=1
        return counter


def find_quiz(number):
    try:
        num = int(number)
        count = 1
        questions = {"question 1":"","question 2":"","question 3":""}
        with open("quizzes.csv","r") as file:
            for line in file:
                if num == count:
                    list = line.split(",")
                    questions["question 1"] = list[0]
                    questions["question 2"] = list[1]
                    questions["question 3"] = list[2]
                    return questions
                count+=1
        return {}
    except ValueError:
        return {}


if __name__ == "__main__":
    main()



"""
tests

from project import check_question, check_password, check_account
import pytest


def test_check_question():
    assert check_question("5 + 4") == 9
    assert check_question("5 *-3") == -15
    assert check_question("5 -  4") == 1
    assert check_question("16  /4") == 4
    assert check_question("cat") == "wrong question"
    assert check_question("cat + 4") == "wrong question"
    assert check_question("4+5-7") == "wrong question"
    assert check_question("cat * dog") == "wrong question"
    assert check_question("43 & 32") == "wrong question"


def test_check_password():
    assert check_password("abcdre") == "unavailable password"
    assert check_password("abcd 1234") == "unavailable password"
    assert check_password("malekk12") == "unavailable password"
    assert check_password("malekk123") == "available password"
    assert check_password("1mal2ek34") == "available password"


def test_check_account():
        assert check_account("ma@student.edu") == "unsupported account"
        assert check_account("malek@student.com") == "unsupported account"
        assert check_account("malek@gmail.edu") == "unsupported account"
        assert check_account("malek ahmad@student.edu") == "unsupported account"
        assert check_account("malek_ahmad02@student.edu") == "student"
        assert check_account("malek_ahmad@teacher.edu") == "teacher"

"""