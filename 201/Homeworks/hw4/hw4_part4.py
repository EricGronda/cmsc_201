# File: hw4_part4.py
# Author: Eric Gronda
# Date: 10/3/17
# Section: 06
# E-mail: gt32930@umbc.edu
# Description: Prompts user for number of tests, then asks for grades

def main():


    numTests = int(input("Enter number of tests taken: "))
    count = 0

    while(count < numTests):
        count += 1
        print("\nFor test #" , count , "was extra credit allowed?")
        extraCredit = input("Please enter 'yes' or 'no': ")    
        
        grade = int(input("Please enter your grade for the test: "))
        gradeMax = grade
        validGrade = False
        
        while(validGrade == False):
            validGrade = True

            if(grade < 0):
                print("Test grade cannot be negative.")
                grade = int(input("Please enter your grade for the test: "))
                validGrade = False
            elif(grade > 100 and extraCredit == "no"):
                print("Test grade must be between 0 and 100.")
                grade = int(input("Please enter your grade for the test: "))
                validGrade = False

            if(gradeMax > grade and validGrade == True):
                gradeMax = grade
        
    print("The highest grade received was" , gradeMax)


main()

