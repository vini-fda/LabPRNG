# Task 1: Generate Encryption Key in a Wrong Way

Just modify `listing1.c`. Run the code above, and describe your observations. Then, comment out
Line 1, run the program again, and describe your observations. Use the observations in both cases to
explain the purpose of the srand() and time() functions in the code.

srand() is used for seeding the random number generator. If the seed is not set, the generator will always generate the same sequence of numbers. time() is used to get the current time, which is used as the seed for the random number generator.
