import dis

def nested(num):

    if num % 3 == 0:

        print ("Fizz")

    elif num % 5 == 0:
        print ("Buzz")

    else:
        print (num)



def flat(num):

    if num % 3 == 0:

        print ("Fizz")

    else:
        if num % 5 == 0:

            print ("Buzz")

        else:

            print (num)

dis.dis(nested)
dis.dis(flat)



