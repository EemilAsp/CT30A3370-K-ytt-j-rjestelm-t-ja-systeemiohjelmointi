

def main():
    a = 15
    b = 20
    print("MOI")
    c = bittisumma(a, b)
    print("%d", c)
    return

def bittisumma(a, b):

    while (b != 0):
        x = a & b
        x = a ^ b
        b = x << 1
        # toteuta biteillä laskettu summauksen logiikka tähän
    summa = b
    return summa