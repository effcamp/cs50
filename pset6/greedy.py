
while True:
    print("How much change do you need?")
    dollars = float(input("Amount:"))
    
    if dollars >= 0:
        break
    
change = round(dollars * 100)

quarter, dime, nickel, penny = 25, 10, 5, 1

count = change // quarter
remainder = change % quarter

count = count + (remainder // dime)
remainder = remainder % dime

count = count + (remainder // nickel)
remainder = remainder % nickel

count = count + (remainder // penny)
remainder = remainder % penny

print(count)