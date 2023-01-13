import decimal

decimal.getcontext().prec = 1000
T = int(input())
for _ in range(T) :
    num = input()
    dec = decimal.Decimal(num + ".0000000000")
    
    if dec == 0e-10 :
        print("0.0000000000")
        continue
    
    power = decimal.Decimal('1') / decimal.Decimal('3')
    dec = decimal.Decimal(dec ** power)
    dec = round(dec, 500)
    dec = decimal.Decimal(dec).quantize(decimal.Decimal(".0000000001"), rounding=decimal.ROUND_DOWN)
    print(dec)